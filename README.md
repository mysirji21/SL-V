# SL-V
Software Laboratory 5

# How to use:  
Download https://github.com/rootkea/SL-V/archive/master.zip or

	$ git clone https://github.com/rootkea/SL-V.git

# Assignments Index
1. Implement following operations using Socket Programming & Multithreading.  
	a. Addition of digits of a given number. (Ex 12345 = 15)  
	b. Find given number is prime or not.  
	
	Usage :  
	
		$ cd 1
		$ gcc server.c -pthread -o server
		$ ./server 51123			#substitute any non-privileged port
		$ gcc client.c -o client 		#on other machine or separate tab
		$ ./client 127.0.0.1 51123		#substitute any LAN ip and port

2. [WIP] Implement following operations using Socket Programming & Multithreading.  
	a. Addition of digits of a given number. (Ex 12345 = 15)  
	b. Perform String Operations. (Compare, Concatenation, Substring)  

	Usage :  
	
		$ cd 2
		$ gcc server.c -pthread -o server
		$ ./server 51123			#substitute any non-privileged port
		$ gcc client.c -o client 		#on other machine or separate tab
		$ ./client 127.0.0.1 51123		#substitute any LAN ip and port

3. 
