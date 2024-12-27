from flask import Flask, jsonify

app = Flask(__name__)

@app.route('/flask')
def hello():
    return "Hello!"

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
