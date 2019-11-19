# SecureChat
# client.py
#
# INCOMPLETE
#
# Last Updated: 20/03/2013

#!C:\python27

import socket
import sys
import time
import string
import thread
import random

# Take input parameters for PORT and IP
PORT = int(sys.argv[2])
IP = sys.argv[1]
BUFFER = 1024
p=23
g=5
a=random.randint(1,100)
b=random.randint(1,100)
# Create TCP/IP socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

print 'Connecting...'

# Connect to the IP and PORT given in user parameters
s.connect((IP, PORT))

print 'Connected!'
dataIn = s.recv(BUFFER)
print dataIn, '\n'
# Function for new receiving thread
def send():
	#B=str((g**b)%p)
	B='l'
	s.sendall(B)
	#S2=int(s.recv(BUFFER))
	S2=s.recv(BUFFER)
	#s2=(S2**b)%p
	s2=S2+'h'
	print s2

	while True:
		dataOut = raw_input('')
		s.sendall(dataOut)
		

# Start receiving thread

thread.start_new_thread(send,())
#A=(g**a)%p
A='m'
#s.sendall(str(A))
s.sendall(A)
S=s.recv(BUFFER)
#s=(int(S)^a)%p
s1=A+'d'
print s1

# Current thread handles the sending instead
while True:
	dataIn = s.recv(BUFFER)
	if (dataIn=='end'): 
		print 'Closing socket...'
		s.close()
		thread.exit()
		break 
	print dataIn, '\n'

	#if (dataOut=='end'):
	#	print 'Closing socket...'
	#	s.close()
	#	break
		#thread.exit()

#print 'Closing socket...'
#s.close()


## END OF FILE