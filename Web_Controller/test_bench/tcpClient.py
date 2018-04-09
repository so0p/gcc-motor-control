import sys
import struct
import socket
import binascii

a = chr(183)
b = chr(1)
c = chr(0)
d = chr(10)
e = chr(237)

values = ( a,b,c,d,e)
s = struct.Struct('c c c c c')
data = s.pack(*values)

#mybytes = 'B704000AED'.decode('hex')
#mybytes=bytearray()
#mybytes.append(183)
#mybytes.append(4)
#mybytes.append(0)
#mybytes.append(10)
#mybytes.append(237)
TCP_IP='10.22.0.11'
TCP_PORT = 23
BUFFER_SIZE = 1024

s=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP,TCP_PORT))
print("connected")
while(1):
	s.send(data)
	print("Sending packets")
#data = s.recv(BUFFER_SIZE)
s.close()

print "sent data", type(data)
print sys.getsizeof(data)
print binascii.hexlify(data)
