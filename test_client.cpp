// 测试客户端：连接服务器并发送消息
// 编译: clang++ -std=c++17 -o test_client im_protocol.cpp test_client.cpp

#include "im_protocol.hpp"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstring>
#include <thread>
#include <chrono>

using namespace im;

int main(int argc, char* argv[]) {
  int id = 1;
  if (argc > 1) {
    id = atoi(argv[1]);
  }

  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    perror("socket");
    return 1;
  }

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9000);
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

  if (connect(fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("connect");
    return 1;
  }

  printf("[Client %d] Connected to server\n", id);

  // 设置非阻塞，用于接收回包
  fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0) | O_NONBLOCK);

  ByteBuffer buf;

  // 发送多条消息
  for (int i = 0; i < 3; i++) {
    char msg[256];
    snprintf(msg, sizeof(msg), "Hello from client %d message %d", id, i + 1);

    Packet pkt;
    pkt.type = (uint16_t)MsgType::CHAT;
    pkt.body = msg;

    auto bytes = Codec::encode(pkt);
    ssize_t n = send(fd, bytes.data(), bytes.size(), 0);

    printf("[Client %d] Sent message %d (%zu bytes)\n", id, i + 1, bytes.size());

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // 尝试接收回包
    uint8_t tmp[4096];
    while (true) {
      ssize_t rn = read(fd, tmp, sizeof(tmp));
      if (rn > 0) {
        buf.append(tmp, (size_t)rn);
        Packet resp;
        while (Codec::try_decode(buf, resp)) {
          printf("[Client %d] Received: %s\n", id, resp.body.c_str());
        }
      } else if (rn < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
        perror("read");
        break;
      } else {
        break;
      }
    }
  }

  printf("[Client %d] Waiting for more messages...\n", id);
  std::this_thread::sleep_for(std::chrono::seconds(2));

  close(fd);
  printf("[Client %d] Disconnected\n", id);

  return 0;
}
