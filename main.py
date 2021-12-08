import random
import socket
from flask import Flask, render_template, request, jsonify

app = Flask(__name__)


@app.route("/")
def main():
    return render_template("home.html")


@app.route("/data-deg", methods=["GET"])
def deg():
    data = s.recv(1024)
    return jsonify({'message': int.from_bytes(data, 'big')})


@app.route("/on", methods=["POST"])
def on():
    print('on')
    s.sendall(b'd')
    return "<p>ON</p>"


@app.route("/off", methods=["POST"])
def off():
    s.sendall(b's')
    return "<p>OFF</p>"


if __name__ == "__main__":
    host = "192.168.10.3"
    port = 2000
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))
    app.run(host="0.0.0.0", port=5000, debug=True)
    s.close()
