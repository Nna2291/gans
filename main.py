import socket
from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/")
def main():
    return render_template("home.html")


@app.route("/data-deg", methods=["POST"])
def deg():
    print(request)


@app.route("/on", methods=["POST"])
def on():
    print('on')
    host = "192.168.10.3"
    port = 2000
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    s.sendall(b'd')
    data = s.recv(1024)
    s.close()
    return "<p>ON</p>"


@app.route("/off", methods=["POST"])
def off():
    host = "192.168.10.3"
    port = 2000
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    s.sendall(b's')
    data = s.recv(1024)
    s.close()
    return "<p>OFF</p>"


if __name__ == "__main__":
    app.run(host="0.0.0.0", port="5000", debug=True)
