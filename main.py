from math import acos, degrees

import requests
from flask import Flask, render_template, request

app = Flask(__name__)
host = '192.168.10.3:80'
Vcc = 5.0
Vccm = 3.3
Ka = 1000.0
Kb = -5.0
Kt = 0.02
Kp = 0.5
Kf = 0.85
T = 25.0


@app.route("/")
def main():
    return render_template("home.html")


@app.route("/data", methods=["GET"])
def deg():
    try:
        req = requests.get(f"http://{host}/", timeout=0.5)
    except (requests.exceptions.ReadTimeout, requests.exceptions.ConnectTimeout,
            requests.exceptions.ConnectionError) as e:
        js = {'temp': 0, 'elek': 0, 'density': 0,
              'orient_z': 0, 'valid': False}
        return js
    if req.status_code != 200:
        js = {'temp': 0, 'elek': 0, 'density': 0,
              'orient_z': 0, 'valid': False}
        return js
    temp, volt, z = req.text.rstrip().split(';')
    Vm = float(volt) * Vcc / 1023
    S = Ka * pow((Vccm - Kf * Vm) / 2, Kb)
    EC = S / (1 + Kt * (float(temp) - T))
    TDS = EC * Kp
    z = float(z) / 16384
    if z < 0:
        angle = 90 - degrees(acos(z))
    else:
        angle = degrees(acos(-z)) - 90
    js = {'temp': temp, 'elek': round(S, 2), 'density': round(TDS, 2), 'orient_z': round(angle, 0),
          'valid': True}
    return js


@app.route("/engine", methods=["POST", "GET"])
def engine():
    requests.post(f'http://{host}/', data=request.get_json()['task'])
    return '1'


if __name__ == "__main__":
    app.run(host='0.0.0.0', debug=True)
