# SecureChat
# server.py
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


# Take input parameter for PORT
PORT = int(sys.argv [1])
BUFFER = 1024
TCP_IP = 'localhost'
clients = 0
# List of 2 socket objects for the 2 players
client_list = [] 


###### DECLARING ALL LOCAL FUNCTIONS FIRST

# Function for User 0 thread
def U0():
	A = client_list[0].recv(BUFFER)
	client_list[1].sendall (A)
	while True:
		data1 = client_list[0].recv(BUFFER)
		if(data1!='end'): client_list[1].sendall (data1)
		if (data1=='end'): 
			client_list[1].sendall ('end')
			client_list[0].sendall ('end')
			print 'Closing socket 0...'
			client_list[0].close()
			print 'Closing socket 1...'
			client_list[1].close()
			conversation=False
			#thread.exit()
			break		
		

###### DONE DECLARING LOCAL FUNCTIONS


# Create TCP/IP socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Associate the socket with the server address (which is localhost)
s.bind((TCP_IP, PORT))

# Put socket into server mode with listen, max of 2 connections in queue 
s.listen(2)
print 'Waiting for connections...'
while True:
	conn, clientAddr = s.accept()
	print 'User ', clients, ' connected by ', clientAddr
	
	conn.sendall('YOU ARE USER '+str(clients))

	# Append new socket object (conn) to list
	client_list.append(conn)
	clients += 1

	# Break when we have 2 players
	if clients == 2:
		break


# Start User 0 thread
thread.start_new_thread(U0,())
B = client_list[1].recv(BUFFER)
client_list[0].sendall (B)

# Current thread handles User 1 instead
while True:
	data2 = client_list[1].recv(BUFFER)
	if(data2 !='end'):client_list[0].sendall (data2)
	if (data2=='end'): 
		client_list[1].sendall ('end')
		client_list[0].sendall ('end')
		#thread.exit()
		print 'Closing socket 0...'
		client_list[0].close()
		print 'Closing socket 1...'
		client_list[1].close()
		
		break




## END OF FILE