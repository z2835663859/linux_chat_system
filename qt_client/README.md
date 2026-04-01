# qt_client

基于 C++ Qt6 框架编写的跨平台即时通讯图形化客户端。

## 文件说明

* `src/main.cpp`：Qt 客户端启动入口与 QApplication 初始化
* `src/models/chat_model.hpp` / `chat_model.cpp`：维护本地聊天历史、联系人列表，与 UI 进行数据绑定
* `src/network/im_client_network.hpp` / `im_client_network.cpp`：Socket TCP 长连接处理，包含对报文的封包与解包
* `src/ui/main_window.hpp` / `main_window.cpp`：主聊天登录与消息收发界面逻辑
* `CMakeLists.txt` / `build.sh`：客户端的跨平台编译配置脚本
* `fix_newline.py`：自动修复 Windows 和 Linux 文件换行符结尾系统的工具

## 跨平台编译
下载代码后：
1. 安装 Qt6 以及 CMake。
2. 使用 Qt Creator 打开 `CMakeLists.txt` 构建运行。
3. 也可以在当前目录直接 `./build.sh`（要求带有依赖库）。

## 使用
登录界面输入：
IP：`146.190.81.211` 或 `www.zshdo.me`
端口：`9999`
