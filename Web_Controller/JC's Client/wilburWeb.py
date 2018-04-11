from flask import Flask, render_template, request
import random, socket, threading, struct

#tcp server
TCP_IP = '10.22.0.11'
TCP_PORT = 23
BUFFER_SIZE = 1024

#create socket variable
s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)

def pack_the_struct(direction):
	values = (chr(183),chr(direction),chr(0),chr(10),chr(237))
	packet=struct.Struct('ccccc')
	data = packet.pack(*values)
	return data

def launch_packet():
	s.connect((TCP_IP, TCP_PORT))

def disconnect_socket():
	s.close()

def send_the_packet(data):
	s.send(data)


#Flask app
app = Flask(__name__)

#Home Page
@app.route('/', methods=['GET', 'POST'])
def index():
	if request.method == 'POST':
		if request.form['submit'] == "forward":
			direction = 1
			x = pack_the_struct(direction)
			print("attempting to send packet")
			s.send(x)
		elif request.form['submit'] == "Backward":
			direction = 2
			pack_the_struct(direction)
		elif request.form['submit'] == "Left":
			direction = 3
			pack_the_struct(direction)
		elif request.form['submit'] == "Right":
			direction = 4
			pack_the_struct(direction)

	if request.method == 'GET':
		print("getting website")
		return render_template("test.html")

#Open thread
t = threading.Thread(target=launchServer)
t.daemon = True
t.start()

#Run flask app
if __name__=="__main__":
	app.run(debug=True, threaded=True, use_reloader=False)
