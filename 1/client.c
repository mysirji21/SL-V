/*
*	Author: Avinash Sonawane <rootkea@gmail.com>
*	Title : Implement following operations using Socket Programming & Multithreading.
*			a) Addition of digits of a given number. (Ex 12345 = 15).
*			b) Perform String Operations. (Compare, Concatenation, Substring).
*	License: GPL v3 or later
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <string.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char **argv)
{
	int sockfd, sum, prime;
	struct sockaddr_in server;
	char buf[21];

	printf("Number: ");
	scanf("%20s", buf);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("socket() failed");

	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	if(!inet_aton(argv[1], &server.sin_addr))
		error("Invalid Address");

	if (connect(sockfd, (const struct sockaddr *)&server, sizeof(server)) < 0)
		error("connect() failed");

	if (send(sockfd, buf, strlen(buf), 0) < 0)
		error("send failed");

	memset(buf, '\0', sizeof(buf));
	if (recv(sockfd, buf, sizeof(buf), 0) < 0)
		error("recv failed");

	sscanf(buf, "%d %d", &sum, &prime);
	printf("Sum = %d\nPrime = %s\n", sum, prime? "Yes" : "No");

	close(sockfd);

	return 0;
}
