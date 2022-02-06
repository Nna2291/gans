import requests

req = requests.get("http://192.168.10.3:80")
data = req.json()

print(data['value'])