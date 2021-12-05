import socket

import requests as requests

while True:
    host = "192.168.10.3"
    port = 2000
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    data = s.recv(1024)
    huh = int.from_bytes(data, "big")
    print(huh)
    requests.post(f'http://192.168.10.101:5000/data-deg/?len={huh}')

'''
02:02:02:02:02:02:02:02:02:02:02:02:02:02:02:02
02:02:02:02:03:04:00:00:05:20:2B:2B:2B:2B:2B:2B
2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B
2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B
2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:2B:
'''