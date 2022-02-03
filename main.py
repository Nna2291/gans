import socket
from flask import Flask, render_template, jsonify

app = Flask(__name__)


@app.route("/")
def main():
    return render_template("home.html")


# @app.route("/data-deg", methods=["GET"])
# def deg():
#     j = s.recv(1024)
#     l = len(j.decode("utf-8"))
#     data = j.decode("utf-8")[1:l - 1].split(',')
#     return jsonify({'message': data[0]})
#
#
@app.route("/on/<hype>", methods=["POST", "GET"])
def on(hype):
    data = b'd' + bytes(hype, 'utf-8')
    host = "192.168.10.3"
    port = 2000
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    s.sendall(data)
    s.close()
    return "<p>ON</p>"


@app.route("/off", methods=["POST"])
def off():
    host = "192.168.10.3"
    port = 2000
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    s.sendall(b's')
    s.close()
    return "<p>OFF</p>"


if __name__ == "__main__":
    app.run(host='0.0.0.0', debug=True)
