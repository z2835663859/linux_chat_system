# 🚀 基于 Reactor 模型的高性能 C++ 即时通讯系统 (IM System)

> 💡 **在线体验 / Live Demo** 
> **服务器 IP**: `146.190.81.211`
> **端口**: `9999`
> **测试账号**: `alice` / `alice123` | `bob` / `bob123` | `charlie` / `charlie123`

## 📖 项目简介

这是一个基于 **C++17** 开发的跨平台的高性能即时通讯（IM）系统。项目涵盖了**服务端**与**客户端**的完整实现。服务端采用基于 `epoll` 的 **Reactor 事件驱动模型**，能够高效处理高并发的网络连接任务。客户端提供了轻量级的命令行版本（CLI）以及基于 **Qt6** 的跨平台图形界面版本（GUI）。

项目对底层网络通信、协议设计（解决 TCP 粘包/半包问题）、多线程并发控制作了深度的定制化设计与实现，非常适合作为 C++ 后端开发、网络编程的实战演示。

## ✨ 核心特性

- **高效网络架构**：服务端采用单线程/多线程 **Reactor** 模式，结合 `epoll` I/O 多路复用，实现非阻塞的并发网络事件处理，强悍的底层承载能力。
- **自定义应用层协议**：自主设计 **TLV (Type-Length-Value)** 格式的网络协议，结合自定义的 Codec 解码器，完美解决 TCP 字节流传输中经典的**粘包**与**拆包**问题。
- **完整业务闭环**：
  - **单聊/群聊**：支持跨客户端的实时 P2P 单聊和最高支持多人的群聊室机制。
  - **离线消息机制**：用户离线时，发往该用户的消息将被服务端暂存，并在用户下次登录时自动双向同步投递。
  - **心跳保活**：客户端与服务端自带 Ping/Pong 心跳机制，能够精准识别并剔除断网和僵死连接（Dead Connections），释放服务器资源。
- **现代 C++ 规范**：全量使用 C++17 特性。运用 `std::shared_ptr` / `std::unique_ptr` 进行内存生命周期管理（RAII），运用 Lambda 表达式进行事件回调的解耦。
- **跨平台多端支持**：包含轻量级的命令行客户端，同时提供基于 Qt6 / CMake 构建的现代桌面 GUI 客户端，支持信号与槽界面的数据分离。

## 🛠️ 技术栈

* **编程语言**: C++17
* **核心网络**: Sockets API (TCP), I/O 多路复用 (`epoll` Linux / `kqueue` BSD)
* **并发控制**: `std::thread`, `std::mutex`, `std::condition_variable`
* **构建工具**: `CMake`, `Makefile` (Shell Scripts)
* **桌面端 UI**: Qt 6.x (信号与槽机制，事件驱动模型)
* **服务器环境**: Ubuntu Linux

## 🚀 快速启动

### 1. 编译系统
```bash
# 在 Linux 环境下编译服务端组件与 CLI 客户端
./build.sh all
```

### 2. 运行服务端
```bash
# 启动并监听 9999 端口
./server_im 9999
```

### 3. 运行客户端跑通 Demo
**命令行客户端：**
```bash
# 语法: ./im_client [用户名] [密码] [服务器IP]
./im_client alice alice123 127.0.0.1
```

**Qt 界面客户端：**
依赖 `Qt6` 环境，请进入 `qt_client` 目录下查看 `COMPILATION_GUIDE.md` 进行 CMake 图形界面的构建，构建完成后填入 `146.190.81.211:9999` 即可连入公网服务端。

## 📁 目录结构

```text
├── server_im.cpp           # 服务端主入口程序
├── im_client.cpp           # 命令行客户端主入口
├── event_loop_epoll.hpp    # Reactor 模式底层 epoll 封装
├── im_protocol.cpp/hpp     # 自定义 TLV 协议与序列化/反序列化逻辑
├── message_handler.cpp     # 消息路由、信令处理机制
├── message_storage.cpp     # 离线消息库、消息持久化
├── group_manager.cpp       # 群组房间业务逻辑分发
├── qt_client/              # 基于 Qt6 的图形化跨平台客户端
└── build.sh                # 快速构建脚本
```

## 📜 许可证

本项目基于 MIT License 开源。
