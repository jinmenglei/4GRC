import socket
import time

# 你的ip 地址，大网的
HOST = '11.22.33.44'
PORT = 5678
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)      # 定义socket类型，网络通信，TCP
s.connect((HOST, PORT))       # 要连接的IP与端口
cnt = 0
while True:
    cnt += 1
    if cnt > 255:
        cnt = 0
    s.send(bytes([0xAA, 0xBB, 0xCC, 0xDD, cnt]))
    time.sleep(0.02)


