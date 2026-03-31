# 基于Reactor模型的C++高性能即时通讯系统 

一个即时通讯系统，演示 TCP 网络编程、协议设计、多连接管理技术。

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
- 结构化日志系统
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
├── 核心程序
│   ├── server_im.cpp            # 完整 IM 服务器入口文件
│   └── client_send.cpp          # 命令行客户端测试程序
└── 脚本/文档
    └── build.sh                 # 自动化编译脚本
```

---

## 🚀 场景一：完整通讯系统演示

### 启动服务器
```bash
./server_im 9999
```

输出示例：
```text
[Server] IM Server started on 0.0.0.0:9999
```

### 启动客户端 #1 (Alice)
```bash
./im_client 127.0.0.1 9999
```
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

### 启动客户端 #2 (Bob) - 另一个终端
```bash
./im_client 127.0.0.1 9999
```
互动效果：

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

## 🚀 场景二：自动化测试

测试协议编码
```bash
./test_codec
```

输出：
```text
decoded #1 type=2 body={"text":"hello"}
decoded #2 type=2 body={"text":"world"}
```

## 🚀 场景三：群组聊天功能测试

```bash
# 终端 1: 启动服务器
./server_im 9999

# 终端 2: 运行群组聊天测试
python3 test_group_chat.py
```
测试包括：
- 多用户同时连接
- 创建群组
- 成员加入/离开团体
- 实时群组消息广播
- 群体信息查询

请参阅 `GROUP_CHAT_FEATURES.md`

---

## 📖 协议说明

### 协议格式
```text
[Magic: 4 bytes][Type: 2 bytes][Body Length: 4 bytes][Body: Variable]
```
- **魔法 (Magic)**：`0x494D3031` (“IM01”)
- **消息类型 (Type)**：2字节大端序
  - `1` = 心跳
  - `2` = 单聊 (CHAT)
  - `3` = 注册
  - `4` = 登录
  - `5` = 登出
  - `6` = 获取在线用户
- **正文 (Body)**：变长 JSON 格式

### 消息示例

**登录请求** / **登录响应** / **单聊消息** (遵循上述 Type 映射与 JSON 规则)。

---

## 💡 使用示例 (Python 快速接入)

示例 1：自动化方式(Python脚本示例)

```python
import socket
import json
import time
import struct

def send_message(sock, msg_type, body):
    magic = 0x494D3031
    body_bytes = json.dumps(body).encode('utf-8')
    header = struct.pack('<IHI', magic, msg_type, len(body_bytes))
    sock.send(header + body_bytes)

sock = socket.socket(socket.AF_INET, socket.socket.SOCK_STREAM)
sock.connect(('127.0.0.1', 9999))

# 登录
send_message(sock, 4, {"username": "alice", "password": "123"})
print(sock.recv(1024).decode(errors='ignore'))
sock.close()
```

---

## 🧪 测试验证状态

| 功能 | 状态 | 验证方式 |
| :--- | :--- | :--- |
| 协议编码 | ✅ | test_codec（粘包+半包）|
| 用户注册/登录 | ✅ | im_client |
| 单聊消息 | ✅ | im_client 互相通信 |
| 心跳保活 | ✅ | im_client heartbeat 命令 |
| 异常/错误处理 | ✅ | 离线用户提示、认证失败 |

---

## 🔍 调试技巧

**查看服务器日志**
启用转储日志到文件
```bash
./server_im 9999 > /tmp/im_server.log 2>&1 &
```
然后查看：
```bash
tail -f /tmp/im_server.log
```
使用 `netstat` 查看网络连接情况
```bash
netstat -an | grep 9999
```

---

## 📝 常见问题与核心文件

**Q1: 为什么消息没收到？**
检查目标用户是否在线、是否登录成功。

**📚 核心源码文件说明**
- `im_protocol.hpp` / `cpp` - 协议层（处理粘包、半包解码）
- `event_loop.hpp` / `cpp` - 基于 Epoll 的事件循环
- `server.hpp` / `cpp` - 服务器端口监听与 Accept
- `conn.hpp` / `cpp` - I/O 的收发缓冲封装
- `user_manager.hpp` / `connection_manager.hpp` - 映射管理
- `message_handler.hpp` - 解析 JSON 并路由命令

> 📞 **如果有问题请务必检查**：编译是否确保开启了 C++17 特性支持！
> **最后更新：2026年3月31日**
