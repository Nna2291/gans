import requests
from flask import Flask, render_template, jsonify, request

app = Flask(__name__)
host = '192.168.1.3:80'

# status = {'temp': 0, 'elek': 0, 'density': 0, 'coord': (0, 0), 'orient': ('you', 'are', 'gay')}


@app.route("/")
def main():
    return render_template("home.html")


@app.route("/data", methods=["GET"])
def deg():
    req = requests.get(f"http://{host}/")
    js = req.text.rstrip()
    print(js)
    return js


@app.route("/engine", methods=["POST", "GET"])
def engine():
    requests.post(f'http://{host}/', data=request.get_json()['task'])
    return '1'


if __name__ == "__main__":
    app.run(host='0.0.0.0', debug=True)
