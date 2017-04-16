# SL-V
Software Laboratory 5

# How to use:  
	$ sudo apt-get install git				#use OS specific command to install git
	$ git clone https://github.com/rootkea/SL-V.git
	$ cd SL-V

# Assignments Index
1. Implement following operations using Socket Programming & Multithreading.  
	a. Addition of digits of a given number. (Ex 12345 = 15)  
	b. Find given number is prime or not.  
	
	Usage :  
	
		$ cd 1
		$ gcc server.c -pthread -o server
		$ ./server 51123				#substitute any non-privileged port
		$ gcc client.c -o client 			#on other machine or separate tab
		$ ./client 127.0.0.1 51123			#substitute any LAN ip and port

2. Implement following operations using Socket Programming & Multithreading.  
	a. Addition of digits of a given number. (Ex 12345 = 15)  
	b. Perform String Operations. (Compare, Concatenation, Substring)  

	Usage :  
	
		$ cd 2
		$ gcc server.c -pthread -o server
		$ ./server 51123				#substitute any non-privileged port
		$ gcc client.c -o client 			#on other machine or separate tab
		$ ./client 127.0.0.1 51123			#substitute any LAN ip and port

3.  [WIP]Design a distributed application using RPC for remote computation  
    where client submits a string to the server and server checks whether it is  
    palindrome or not, reverse the string and returns the result to the client  
    program.  

4.  Design a distributed application using Message Passing Interface  
    (MPI) for remote computation where client submits a string to the server  
    and server returns the reverse of it to the client.  
    
    Usage :  
    	
	On Slave(`w.x.y.z`):  

		$ sudo apt-get install openssh-server		#install ssh server on slave
		$ sudo service ssh start			#start ssh server on slave
		$ sudo adduser foo				#create same user as on Master e.g foo

	On Master(`127.0.0.1`) for user `foo`:  

		$ cd 4
		$ mpicc mpi.c -o mpi
		$ ssh foo@w.x.y.z				#login to slave
		$ mkdir ... 					#create direcotry structure same as Master leading to mpi.c
		$ scp mpi.c foo@w.x.y.z:`pwd` && exit		#in new tab : copy mpi.c to client
		$ mpicc mpi.c -o mpi				#create binary
		$ exit
		$ mpirun -H 127.0.0.1,w.x.y.z -npernode 1 ./mpi

5.	[WIP]Design application using MapReduce under Hadoop for Character counting  
	in a given text file.
