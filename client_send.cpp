// IM 客户端程序：演示 TCP 粘包与拆包问题
// 功能：连接到服务器，发送多个消息包，测试粘包和拆包处理，并尝试接收响应

#include "im_protocol.hpp"
#include <arpa/inet.h>      // inet_pton() 函数
#include <netinet/in.h>     // sockaddr_in 结构体
#include <sys/socket.h>     // socket() 相关 API
#include <unistd.h>         // close() 函数
#include <cstdio>           // perror() 函数
#include <cstdlib>          // atoi() 函数
#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char* argv[]) {
  const char* ip = "127.0.0.1";
  int port = 9999;
  
  if (argc >= 3) {
      ip = argv[1];
      port = std::atoi(argv[2]);
  }

  // 创建 TCP 套接字（IPv4, 流式传输）
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
      perror("socket");
      return 1;
  }

  // macOS 下忽略 SIGPIPE 信号，防止服务端断开时 send 导致客户端崩溃
#ifdef SO_NOSIGPIPE
  int set = 1;
  setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));
#endif

  // 初始化服务器地址结构
  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  inet_pton(AF_INET, ip, &addr.sin_addr);

  // 连接到服务器
  if (connect(fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
    perror("connect");
    close(fd); // 修复：连接失败时防止文件描述符泄漏
    return 1;
  }
  std::cout << "已连接到服务器 " << ip << ":" << port << std::endl;

  // 构造聊天消息包
  im::Packet a{ (uint16_t)im::MsgType::CHAT, R"({"text":"hello"})" };
  im::Packet b{ (uint16_t)im::MsgType::CHAT, R"({"text":"world"})" };
  im::Packet c{ (uint16_t)im::MsgType::CHAT, R"({"text":"this is a test for splitting packets"})" };

  // 将消息包编码为字节序列
  auto ba = im::Codec::encode(a);
  auto bb = im::Codec::encode(b);
  auto bc = im::Codec::encode(c);

  // ===== 1. 测试 TCP 粘包 =====
  std::cout << "测试 1: 发送粘包数据 (hello + world)..." << std::endl;
  std::vector<uint8_t> glued_packets = ba;
  glued_packets.insert(glued_packets.end(), bb.begin(), bb.end());
  
  ssize_t sent = send(fd, glued_packets.data(), glued_packets.size(), 0);
  if (sent < 0) perror("send glued packets");

  // ===== 2. 测试 TCP 拆包/半包 =====
  std::cout << "测试 2: 发送拆包数据 (每次发送几个字节模拟延迟)..." << std::endl;
  for (size_t i = 0; i < bc.size(); ++i) {
      if (send(fd, &bc[i], 1, 0) < 0) {
          perror("send split packet");
          break;
      }
      // 稍微延迟一下，模拟网络发送半包的情况
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  std::cout << "发送完毕。" << std::endl;

  // ===== 3. 读取服务端响应（如果有的话） =====
  std::cout << "等待服务端响应..." << std::endl;
  char recv_buf[1024];
  // 简单阻塞读取一次作为演示
  ssize_t n = recv(fd, recv_buf, sizeof(recv_buf) - 1, 0);
  if (n > 0) {
      recv_buf[n] = '\0';
      std::cout << "收到服务器数据 (" << n << " 字节)" << std::endl;
  } else if (n == 0) {
      std::cout << "服务器已断开连接。" << std::endl;
  } else {
      perror("recv");
  }

  // 关闭套接字连接
  close(fd);
  return 0;
}