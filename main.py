from socket import *
import time


address = ('192.168.2.10', 5000) #server IP and port
client_socket = socket(AF_INET, SOCK_DGRAM) #Socket
client_socket.settimeout(1)  # wait max 1 sec for answer... if response is expected

while (1):
	data = "motor-L-20-5-1"  # settings for motor ... do motor, left, 20 steps, 5 ms delay, dir 1
	client_socket.sendto(data, address)  # send data request
	print(data)	#python output
	time.sleep(0.5)  # delay before sending next command
