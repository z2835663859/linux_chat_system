#!/usr/bin/env python3
"""
群组聊天功能测试脚本

演示：
1. 创建群组
2. 多用户加入消息类型定义
3. 群组消息广播
"""

import socket
import struct
import json
import time
import sys
import threading

# 消息类型定义
MSG_TYPES = {
    "HEARTBEAT": 1,
    "CHAT": 2,
    "LOGIN": 3,
    "LOGOUT": 4,
    "CHAT_TO": 5,
    "NOTIFY": 6,
    "CREATE_GROUP": 7,
    "JOIN_GROUP": 8,
    "LEAVE_GROUP": 9,
    "CHAT_GROUP": 10,
    "LIST_GROUPS": 11,
    "GROUP_MEMBERS": 12,
}

kMagic = 0x494D3031

def encode_packet(msg_type, body):
    """编码消息包"""
    body_bytes = body.encode() if isinstance(body, str) else body
    body_len = len(body_bytes)
    
    # 构建消息头: magic(4) + type(2) + length(4)
    header = struct.pack("!I", kMagic)
    header += struct.pack("!H", msg_type)
    header += struct.pack("!I", body_len)
    
    return header + body_bytes

def decode_packet(data):
    """解码消息包"""
    if len(data) < 10:
        return None
    
    magic = struct.unpack("!I", data[0:4])[0]
    if magic != kMagic:
        return None
    
    msg_type = struct.unpack("!H", data[4:6])[0]
    body_len = struct.unpack("!I", data[6:10])[0]
    
    if len(data) < 10 + body_len:
        return None
    
    body = data[10:10 + body_len].decode()
    return (msg_type, body)

def send_and_recv(sock, msg_type, body, timeout=2):
    """发送消息并接收回复"""
    packet = encode_packet(msg_type, body)
    sock.sendall(packet)
    
    sock.settimeout(timeout)
    try:
        # 接收10字节头
        header = sock.recv(10)
        if len(header) < 10:
            return None
        
        msg_type_recv = struct.unpack("!H", header[4:6])[0]
        body_len = struct.unpack("!I", header[6:10])[0]
        
        # 接收body
        body_data = b""
        while len(body_data) < body_len:
            chunk = sock.recv(body_len - len(body_data))
            if not chunk:
                break
            body_data += chunk
        
        return (msg_type_recv, body_data.decode())
    finally:
        sock.settimeout(None)

def login(sock, username, password):
    """登录"""
    body = json.dumps({"username": username, "password": password}, separators=(',', ':'))
    print(f"[DEBUG] {username} 发送登陆请求体: {body}")
    msg_type, response = send_and_recv(sock, MSG_TYPES["LOGIN"], body)
    print(f"[{username}] LOGIN response: {response}")
    return response

def create_group(sock, group_name, description=""):
    """创建群组"""
    body = json.dumps({"group_name": group_name, "description": description}, separators=(',', ':'))
    msg_type, response = send_and_recv(sock, MSG_TYPES["CREATE_GROUP"], body)
    print(f"[CREATE_GROUP] response: {response}")
    
    try:
        data = json.loads(response)
        if data.get("status") == "ok":
            return data.get("group_id")
    except:
        pass
    
    return None

def join_group(sock, username, group_id):
    """加入群组"""
    body = json.dumps({"group_id": group_id}, separators=(',', ':'))
    msg_type, response = send_and_recv(sock, MSG_TYPES["JOIN_GROUP"], body)
    print(f"[{username}] JOIN_GROUP {group_id} response: {response}")
    return response

def list_groups(sock, username):
    """列出用户的群组"""
    body = "{}"
    msg_type, response = send_and_recv(sock, MSG_TYPES["LIST_GROUPS"], body)
    print(f"[{username}] LIST_GROUPS response: {response}")
    return response

def get_group_members(sock, group_id):
    """获取群组成员"""
    body = json.dumps({"group_id": group_id}, separators=(',', ':'))
    msg_type, response = send_and_recv(sock, MSG_TYPES["GROUP_MEMBERS"], body)
    print(f"[GROUP_MEMBERS] {group_id} response: {response}")
    return response

def send_group_message(sock, username, group_id, text):
    """发送群组消息"""
    body = json.dumps({"group_id": group_id, "text": text}, separators=(',', ':'))
    msg_type, response = send_and_recv(sock, MSG_TYPES["CHAT_GROUP"], body)
    print(f"[{username}] CHAT_GROUP {group_id}: {text}")
    print(f"         response: {response}")

def recv_messages(sock, username, duration=5):
    """接收消息（后台线程）"""
    sock.settimeout(1)
    end_time = time.time() + duration
    
    while time.time() < end_time:
        try:
            header = sock.recv(10)
            if len(header) < 10:
                continue
            
            msg_type = struct.unpack("!H", header[4:6])[0]
            body_len = struct.unpack("!I", header[6:10])[0]
            
            body_data = b""
            while len(body_data) < body_len:
                chunk = sock.recv(body_len - len(body_data))
                if not chunk:
                    break
                body_data += chunk
            
            body = body_data.decode()
            
            if msg_type == MSG_TYPES["CHAT_GROUP"]:
                print(f"[{username}] ✅ 收到群组消息: {body}")
            elif msg_type == MSG_TYPES["NOTIFY"]:
                print(f"[{username}] 收到通知: {body}")
            else:
                print(f"[{username}] 收到消息类型{msg_type}: {body}")
                
        except socket.timeout:
            continue
        except Exception as e:
            print(f"[{username}] 接收错误: {e}")
            break
    
    sock.settimeout(None)

def main():
    print("=" * 70)
    print("群组聊天功能测试")
    print("=" * 70)
    
    server_addr = ("127.0.0.1", 9999)
    
    # 1. 创建三个客户端连接
    print("\n[1] 创建三个客户端连接...")
    try:
        alice_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        alice_sock.connect(server_addr)
        print("✓ Alice 连接成功")
        
        bob_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        bob_sock.connect(server_addr)
        print("✓ Bob 连接成功")
        
        charlie_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        charlie_sock.connect(server_addr)
        print("✓ Charlie 连接成功")
    except Exception as e:
        print(f"✗ 连接失败: {e}")
        return
    
    # 2. 登录
    print("\n[2] 三个用户登录...")
    login(alice_sock, "alice", "alice123")
    login(bob_sock, "bob", "bob123")
    login(charlie_sock, "charlie", "charlie123")
    
    time.sleep(0.5)
    
    # 3. Alice 创建群组
    print("\n[3] Alice 创建群组 'Programming Club'...")
    group_id = create_group(alice_sock, "Programming Club", "We code together")
    if not group_id:
        print("✗ 创建群组失败")
        return
    
    print(f"✓ 群组创建成功，群组ID: {group_id}")
    
    time.sleep(0.5)
    
    # 4. Bob 和 Charlie 加入群组
    print("\n[4] Bob 和 Charlie 加入群组...")
    join_group(bob_sock, "bob", group_id)
    join_group(charlie_sock, "charlie", group_id)
    
    time.sleep(0.5)
    
    # 5. 查询群组成员
    print("\n[5] 查询群组成员...")
    get_group_members(alice_sock, group_id)
    
    # 6. 列出用户的群组
    print("\n[6] 列出用户的群组...")
    list_groups(alice_sock, "alice")
    list_groups(bob_sock, "bob")
    
    time.sleep(0.5)
    
    # 7. 启动消息接收线程
    print("\n[7] 启动后台消息接收...")
    recv_time = 8
    
    t1 = threading.Thread(target=recv_messages, args=(alice_sock, "alice", recv_time), daemon=False)
    t2 = threading.Thread(target=recv_messages, args=(bob_sock, "bob", recv_time), daemon=False)
    t3 = threading.Thread(target=recv_messages, args=(charlie_sock, "charlie", recv_time), daemon=False)
    
    t1.start()
    t2.start()
    t3.start()
    
    time.sleep(0.5)
    
    # 8. 发送群组消息
    print("\n[8] 群组成员发送消息...")
    send_group_message(alice_sock, "alice", group_id, "大家好，欢迎加入编程俱乐部！")
    
    time.sleep(1.5)
    
    send_group_message(bob_sock, "bob", group_id, "Hello everyone! 很高兴认识你们")
    
    time.sleep(1.5)
    
    send_group_message(charlie_sock, "charlie", group_id, "Hi team! Let's build something awesome together")
    
    time.sleep(2)
    
    # 等待后台线程完成
    t1.join(timeout=1)
    t2.join(timeout=1)
    t3.join(timeout=1)
    
    print("\n" + "=" * 70)
    print("✅ 群组聊天测试完成！")
    print("=" * 70)
    
    alice_sock.close()
    bob_sock.close()
    charlie_sock.close()

if __name__ == "__main__":
    main()
