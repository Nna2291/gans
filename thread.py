import socket

host = "192.168.10.3"
port = 2000
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))
s.sendall(b'd')
