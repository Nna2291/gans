import socket
from flask import Flask, render_template, jsonify

app = Flask(__name__)


@app.route("/")
def main():
    return render_template("home.html")


@app.route("/data-deg", methods=["GET"])
def deg():
    j = s.recv(1024)
    l = len(j.decode("utf-8"))
    data = j.decode("utf-8")[1:l - 1].split(',')
    return jsonify({'message': data[0]})


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
