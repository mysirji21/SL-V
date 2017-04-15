/*
*	Author: Avinash Sonawane <rootkea@gmail.com>
*	Title : Implement following operations using Socket Programming & Multithreading.
*			a) Addition of digits of a given number. (Ex 12345 = 15).
*			b) Perform String Operations. (Compare, Concatenation, Substring)
*	License: GPLv3 or later
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char **argv)
{
	int sockfd, sum, sub, cmp;
	struct sockaddr_in server;
	char buf[21];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("socket() failed");

	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	if(!inet_aton(argv[1], &server.sin_addr))
		error("Invalid Address");

	if (connect(sockfd, (const struct sockaddr *)&server, sizeof(server)) < 0)
		error("connect() failed");

	printf("Number: ");
	scanf("%20s", buf);
	if (send(sockfd, buf, strlen(buf), 0) < 0)
		error("send failed");

	printf("String 1: ");
	scanf("%20s", buf);
	if (send(sockfd, buf, strlen(buf), 0) < 0)
		error("send failed");

	printf("String 2: ");
	scanf("%20s", buf);
	if (send(sockfd, buf, strlen(buf), 0) < 0)
		error("send failed");

	memset(buf, '\0', sizeof(buf));
	if (recv(sockfd, buf, sizeof(buf), 0) < 0)
		error("recv failed");

	sscanf(buf, "%d %d %d", &sum, &sub, &cmp);
	printf("Sum = %d\nSubstring = %s\n", sum, sub? "Yes" : "No");
	printf("Compare = %s\n", cmp? "Equal" : "Unequal");

	close(sockfd);

	return 0;
}
