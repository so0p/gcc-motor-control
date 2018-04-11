import socket

TCP_IP = '10.22.0.11'
TCP_PORT = 23
BUFFER_SIZE = 1024

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect((TCP_IP, TCP_PORT))

while True:
	data = s.recv(BUFFER_SIZE)
	if not data: 
		print("No data being received.")
		break

	# here is where we are going to do something with the code
	# move the rover with whichever direction is send to us
	print("Received Data: ", data)
	if data == 1:
		#move rover forward
	elif data == 2:
		#move rover backward
	elif data == 3:
		#move rover left
	elif data == 4:
		#move rover right
s.close()

