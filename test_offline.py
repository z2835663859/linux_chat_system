#!/usr/bin/env python3
"""
离线消息功能测试脚本
测试场景：
1. alice 登录
2. alice 登出
3. bob 发送消息给离线的alice
4. alice 重新登录
5. alice 应该收到bob的离线消息
"""

import socket
import json
import struct
import time
import sys

# 协议常数
MAGIC = b"IM01"
MSG_TYPE_HEARTBEAT = 1
MSG_TYPE_CHAT = 2
MSG_TYPE_LOGIN = 3
MSG_TYPE_LOGOUT = 4
MSG_TYPE_CHAT_TO = 5
MSG_TYPE_NOTIFY = 6

def send_message(sock, msg_type, body):
    """发送消息到服务器"""
    body_bytes = body.encode('utf-8') if isinstance(body, str) else body
    body_len = len(body_bytes)
    
    # 构造包: magic(4) + type(2) + body_len(4) + body
    packet = MAGIC + struct.pack('>HI', msg_type, body_len) + body_bytes
    sock.sendall(packet)
    print(f"[发送] 类型={msg_type}, 内容={body}")

def receive_message(sock):
    """接收消息"""
    try:
        # 接收头
        header = sock.recv(10)
        if len(header) < 10:
            return None, None
        
        magic = header[0:4]
        msg_type = struct.unpack('>H', header[4:6])[0]
        body_len = struct.unpack('>I', header[6:10])[0]
        
        # 接收body
        body = b''
        while len(body) < body_len:
            chunk = sock.recv(body_len - len(body))
            if not chunk:
                break
            body += chunk
        
        body_str = body.decode('utf-8')
        print(f"[接收] 类型={msg_type}, 长度={body_len}, 内容={body_str}")
        
        return msg_type, body_str
    except socket.timeout:
        print("[接收] 超时")
        return None, None
    except Exception as e:
        print(f"[接收] 错误: {e}")
        return None, None

def test_offline_messages():
    """测试离线消息"""
    
    print("\n========== 离线消息功能测试 ==========\n")
    
    try:
        # 测试1：alice 登录
        print("[测试1] alice 登录")
        sock1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock1.settimeout(2)
        sock1.connect(('localhost', 9999))
        
        send_message(sock1, MSG_TYPE_LOGIN, '{"username":"alice","password":"alice123"}')
        msg_type, body = receive_message(sock1)
        if msg_type == MSG_TYPE_NOTIFY and '"ok"' in body:
            print("✓ alice 登录成功\n")
        else:
            print("✗ alice 登录失败\n")
            return False
        
        # 测试2：alice 登出
        print("[测试2] alice 登出")
        send_message(sock1, MSG_TYPE_LOGOUT, '{}')
        msg_type, body = receive_message(sock1)
        sock1.close()
        print("✓ alice 已断开连接\n")
        
        # 测试3：bob 登录并发送消息给离线的alice
        print("[测试3] bob 登录并发送离线消息给alice")
        sock2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock2.settimeout(2)
        sock2.connect(('localhost', 9999))
        
        send_message(sock2, MSG_TYPE_LOGIN, '{"username":"bob","password":"bob123"}')
        msg_type, body = receive_message(sock2)
        print("✓ bob 登录成功")
        
        # 发送离线消息
        send_message(sock2, MSG_TYPE_CHAT_TO, '{"to_user_id":1,"text":"Hi alice, this is offline message from bob"}')
        msg_type, body = receive_message(sock2)
        print("✓ 离线消息已发送\n")
        
        sock2.close()
        
        time.sleep(1)
        
        # 测试4：alice 重新登录
        print("[测试4] alice 重新登录接收离线消息")
        sock3 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock3.settimeout(2)
        sock3.connect(('localhost', 9999))
        
        send_message(sock3, MSG_TYPE_LOGIN, '{"username":"alice","password":"alice123"}')
        
        # alice应该收到登录回复
        msg_type, body = receive_message(sock3)
        print("✓ alice 登录成功")
        
        # alice应该収到离线消息
        print("等待离线消息...")
        msg_type, body = receive_message(sock3)
        if msg_type == MSG_TYPE_CHAT_TO and "offline" in body:
            print("✓ 成功接收离线消息！")
            print(f"  消息内容: {body}\n")
            return True
        else:
            print("✗ 未收到离线消息\n")
            return False
        
    except Exception as e:
        print(f"\n✗ 测试失败: {e}\n")
        return False
    finally:
        try:
            sock1.close()
        except:
            pass
        try:
            sock2.close()
        except:
            pass
        try:
            sock3.close()
        except:
            pass

if __name__ == '__main__':
    success = test_offline_messages()
    sys.exit(0 if success else 1)
