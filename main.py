import requests
import serial
from flask import Flask, render_template, jsonify, request

app = Flask(__name__)


@app.route("/")
def main():
    return render_template("home.html")


@app.route("/data-deg", methods=["GET"])
def deg():
    req = requests.get("http://192.168.10.3:80")
    data = req.json()
    return jsonify({'message': data['value']})


@app.route("/on", methods=["POST", "GET"])
def on():
    data = request.get_json()
    requests.post('http://192.168.10.3:80/', json=data)
    return "<p>ON</p>"


@app.route("/off", methods=["POST", "GET"])
def off():
    data = request.get_json()
    requests.post('http://192.168.10.3:80/', json=data)
    return "<p>ON</p>"


if __name__ == "__main__":
    app.run(host='0.0.0.0', debug=True)
