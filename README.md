# linux_chat_system

基于 C++17 和 Reactor 模型的即时通讯系统。

在线体验 IP：`146.190.81.211:9999`
测试账号名密码：`alice` / `alice123` | `bob` / `bob123`

## 文件目录说明

### 服务器核心通信与网络层
* `event_loop.hpp` / `event_loop.cpp`：基于 epoll 的事件循环系统
* `event_loop_epoll.hpp` / `event_loop_linux.cpp`：Linux 专属的 epoll 实现逻辑
* `conn.hpp` / `conn.cpp`：客户端网络连接管理与缓冲区读写
* `server.hpp` / `server.cpp`：服务端主监听与连接建立（Accept）入口
* `im_protocol.hpp` / `im_protocol.cpp`：长连接应用层协议编解码（处理粘包/半包）
* `server_im.cpp`：基础通讯服务器 Main 入口起点
* `server_min.cpp`：核心最小化服务器 Main 入口起点
* `server_simple.cpp`：简单调试版服务器 Main 入口起点

### 业务功能系统
* `user_manager.hpp` / `user_manager.cpp`：用户账号认证与黑名单注册逻辑
* `connection_manager.hpp` / `connection_manager.cpp`：网络 Socket 标识与对应的登录用户 UID 之间的映射
* `connection_monitor.hpp` / `connection_monitor.cpp`：超时死连接与心跳包检查系统
* `message_handler.hpp` / `message_handler.cpp`：接收聊天内容后的路由解析器
* `message_storage.hpp` / `message_storage.cpp`：离线聊天内容与消息落盘存储
* `group_manager.hpp` / `group_manager.cpp`：多人群聊与房间分发机制

### 其他与客户端
* `logger.hpp` / `logger.cpp`：系统运行状态与日志文件输出系统
* `client_send.cpp`：测试连接服务端发送报文的调试端
* `im_client.cpp`：标准命令行测试聊天客户端
* `test_client.cpp` / `test_codec.cpp` / `test_multi.cpp`：部分单元测试模块
* `build.sh` / `start.sh`：服务器编译与运行脚本
* `qt_client/`：跨平台拥有图形化界面的 Qt 聊天客户端源码项目

## 编译客户端与运行
```bash
./build.sh all
./server_im 9999
./im_client alice alice123 127.0.0.1
```
