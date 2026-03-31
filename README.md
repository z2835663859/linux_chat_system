# 基于Reactor模型的C++高性能即时通讯系统 (Linux Epoll 版本)

一个成熟的即时通讯后端系统，演示 TCP 网络编程、协议设计、多连接管理、用户认证等核心技术。

> 💡 **在线体验 / Live Demo** 
> **服务器 IP**: `146.190.81.211`
> **端口**: `9999`
> **测试账号**: `alice` / `123456` | `bob` / `123456`

---

## 📋 项目概述

### 功能特性

✅ **网络层**
- TCP 多连接管理（非阻塞 IO）
- 自定义应用层协议（长度前缀 TLV）
- 粘包/半包自动处理
- 部分写缓冲机制

✅ **业务层** (P1)
- 用户注册/登录
- 心跳保活（连接活性检测）
- 单聊消息路由
- 在线状态管理

✅ **高级特性** (P2)
- 离线消息存储与推送
- 结构化日志系统输出
- 连接超时检测与定期清理
- 群组管理与实时消息广播

✅ **架构**
- Reactor 模式（事件驱动）
- 连接管理器（fd <-> user_id 映射）
- 消息处理器（业务逻辑解耦）
- 用户管理器（认证 + 状态）

---

## 🏗️ 文件结构

```text
linux_chat_system/
├── 协议层
│   ├── im_protocol.hpp          # 协议定义、编解码器
│   └── im_protocol.cpp
│
├── 网络层 (Reactor)
│   ├── event_loop.hpp           # 事件循环（使用 epoll）
│   ├── event_loop.cpp
│   ├── conn.hpp                 # 连接类（收发、缓冲）
│   ├── conn.cpp
│   ├── server.hpp               # 服务器（监听、accept）
│   └── server.cpp
│
├── 业务层
│   ├── user_manager.hpp         # 用户管理（注册登录认证）
│   ├── user_manager.cpp
│   ├── connection_manager.hpp   # 连接-用户映射
│   ├── connection_manager.cpp
│   ├── message_handler.hpp      # 消息分发处理
│   └── message_handler.cpp
│
├── P2 高级特性
│   ├── message_storage.hpp      # 离线消息存储
│   ├── message_storage.cpp      # （基于文本文件的持久化）
│   ├── logger.hpp               # 结构化日志系统
│   ├── logger.cpp
│   ├── connection_monitor.hpp   # 连接超时监控
│   ├── connection_monitor.cpp
│   ├── group_manager.hpp        # 分组管理
│   └── group_manager.cpp
│
├── 服务端程序
│   ├── server_im.cpp            # 完整 IM 服务器（包含P2特性）
│   ├── server_simple.cpp        # 简化版（select + echo）
│   ├── server_min.cpp           # 最小版（两客户端 demo）
│   └── server_im                # 编译产物
│
├── 客户端程序
│   ├── im_client.cpp            # 交互式命令行客户端
│   ├── test_client.cpp          # 自动化测试客户端
│   └── qt_client/               # 跨平台 图形界面 GUI 客户端
│
└── 脚本/文档
    ├── build.sh                 # 自动化编译脚本
```

---

## 🔧 编译说明

### 系统要求
- **平台**：Ubuntu / Linux (底层依赖 epoll)
- Clang/GCC C++17
- 无额外第三方依赖，开箱即用

### 编译命令

#### 1️⃣ 一键自动编译（推荐）
```bash
# 赋予执行权限并构建所有目标
chmod +x build.sh
./build.sh all
```
*或者只构建服务端：`./build.sh server`*

#### 2️⃣ 手动编译完整 IM 服务器
```bash
g++ -std=c++17 -Wall -Wextra -o server_im \
  im_protocol.cpp event_loop.cpp conn.cpp server.cpp \
  user_manager.cpp connection_manager.cpp message_handler.cpp \
  message_storage.cpp logger.cpp connection_monitor.cpp group_manager.cpp \
  server_im.cpp -pthread
```

#### 3️⃣ 编译交互式客户端
```bash
g++ -std=c++17 -Wall -Wextra -o im_client \
  im_protocol.cpp im_client.cpp -pthread
```

---

## 🚀 快速开始

### 场景 1：部署完整通讯系统

#### 启动服务器
```bash
./server_im 9999
```

输出示例：
```text
[INFO] [2026-03-31 16:30:00] [Server] IM Server started on 0.0.0.0:9999
[INFO] [2026-03-31 16:30:00] [EventLoop] epoll init success, waiting for events...
```

### 场景 2：客户端互通测试 (本地双开终端模拟)

#### 启动客户端 #1 (Alice)
```bash
./im_client 127.0.0.1 9999
```
*(如果挂载在云服务器，请把 127.0.0.1 换成服务器公网IP)*

交互示例：
```text
> register alice 123456
Register OK, your user ID is: 1

> login alice 123456
Login OK

> send 2 Hello Bob!
Message sent to user 2

> heartbeat
Pong

> quit
Goodbye
```

#### 启动客户端 #2 (Bob)
```bash
./im_client 127.0.0.1 9999
```

互动示例：
```text
> register bob 123456
Register OK, your user ID is: 2

> login bob 123456
Login OK

> [Incoming message from user 1]: Hello Bob!
> send 1 Hi Alice!
Message sent to user 1

> quit
```
