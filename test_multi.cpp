// 多客户端演示：测试 Reactor + 多连接
// 编译: clang++ -std=c++17 -o test_multi im_protocol.cpp event_loop.cpp conn.cpp server.cpp test_multi.cpp

#include "server.hpp"
#include "event_loop.hpp"
#include "im_protocol.hpp"
#include <thread>
#include <chrono>
#include <cstdio>

using namespace im;

// 在线的客户端连接状态
struct ClientState {
  uint32_t user_id = 0;
  std::string username;
};

int main() {
  auto loop = std::make_shared<EventLoop>();
  auto server = std::make_shared<Server>(loop, "127.0.0.1", 9000);

  // 所有连接的在线用户
  std::map<std::shared_ptr<Conn>, ClientState> clients;

  // 连接建立回调
  server->set_connection_callback([&](auto conn) {
    printf("[OnConnect] fd=%d\n", conn->get_fd());
    clients[conn] = ClientState();
  });

  // 消息回调
  server->set_message_callback([&](auto conn, const Packet& pkt) {
    printf("[OnMessage] fd=%d type=%u body=%s\n",
           conn->get_fd(), pkt.type, pkt.body.c_str());

    // 简单echo：把消息回送给所有连接（演示广播）
    if (pkt.type == (uint16_t)MsgType::CHAT) {
      // 构造响应
      Packet resp;
      resp.type = (uint16_t)MsgType::CHAT;
      resp.body = std::string("Echo: ") + pkt.body;

      // 回给发送者
      conn->send(resp);

      // 也广播给其他连接
      for (auto& [other_conn, _] : clients) {
        if (other_conn.get() != conn.get()) {
          other_conn->send(resp);
        }
      }
    }
  });

  // 连接关闭回调
  server->set_close_callback([&](auto conn) {
    printf("[OnClose] fd=%d\n", conn->get_fd());
    clients.erase(conn);
  });

  if (!server->start()) {
    printf("Failed to start server\n");
    return 1;
  }

  // 在后台启动事件循环
  std::thread loop_thread([loop]() {
    loop->run();
  });

  // 给事件循环一些时间
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  printf("\n=== Server running. Accepting connections... ===\n"
         "Connect multiple clients and send messages.\n"
         "Press Ctrl+C to stop.\n\n");

  // 主线程保持运行
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    printf("[Stats] Active connections: %zu\n", clients.size());
  }

  return 0;
}
