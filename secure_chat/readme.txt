To run this program:
=====================

This assumes you have the python interpreter set up already on your system.
From the command line, these programs take the following arguments:

	python server.py <port number>
	python client.py <IP address> <port number>

Arbitrary port numbers can be used as long as they match.
And since the server instance runs on the local machine, the IP in the server code was set to localhost (or 127.0.0.1). 

Ex.:
	python server.py 8005
	python client.py 127.0.0.1 8005

