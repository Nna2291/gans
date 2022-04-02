import requests
from flask import Flask, render_template, jsonify, request

app = Flask(__name__)

# status = {'temp': 0, 'elek': 0, 'density': 0, 'coord': (0, 0), 'orient': ('you', 'are', 'gay')}


@app.route("/")
def main():
    return render_template("home.html")


@app.route("/data", methods=["GET"])
def deg():
    req = requests.get("http://192.168.10.3:80/")
    js = req.json()
    print(js)
    return js


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
