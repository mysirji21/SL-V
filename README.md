# SL-V
Software Laboratory 5

# How to use:  
	$ sudo apt-get install git		#use OS specific command to install git
	$ git clone https://github.com/rootkea/SL-V.git
	$ cd SL-V

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

2. Implement following operations using Socket Programming & Multithreading.  
	a. Addition of digits of a given number. (Ex 12345 = 15)  
	b. Perform String Operations. (Compare, Concatenation, Substring)  

	Usage :  
	
		$ cd 2
		$ gcc server.c -pthread -o server
		$ ./server 51123			#substitute any non-privileged port
		$ gcc client.c -o client 		#on other machine or separate tab
		$ ./client 127.0.0.1 51123		#substitute any LAN ip and port

3.  [WIP]Design a distributed application using RPC for remote computation  
    where client submits a string to the server and server checks whether it is  
    palindrome or not, reverse the string and returns the result to the client  
    program.  

4.  [WIP]Design a distributed application using Message Passing Interface  
    (MPI) for remote computation where client submits a string to the server  
    and server returns the reverse of it to the client.  
