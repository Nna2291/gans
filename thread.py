import socket
host = "192.168.10.3"
port = 2000
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))
while True:
    j = s.recv(1024)
    l = len(j.decode("utf-8"))
    print(j.decode("utf-8")[1:l-1].split(','))

