/*
*	Author: Avinash Sonawane <rootkea@gmail.com>
*	Title : Implement following operations using Socket Programming & Multithreading.
*			a) Addition of digits of a given number. (Ex 12345 = 15).
*			b) Find given number is prime or not.
*	License: GPLv3 or later
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}

void *sumfn(void *num)
{
	int n = *(int *)num;
	int *sum = malloc(sizeof(int));
	if(!sum)
		error("malloc failed");
	
	*sum = 0;
	while(n > 0)
	{
		*sum = *sum + (n % 10);
		n = n / 10;
	}

	pthread_exit(sum);
}

void *primefn(void *num)
{
	int i, n = *(int *)num;
	int *prime = malloc(sizeof(int));
	if(!prime)
		error("malloc failed");
	
	*prime = 1;
	for(i = 2; i <= n / 3 ; i++)
	{
		if(!(n % i))
		{
			*prime = 0;
			break;
		}
	}

	pthread_exit(prime);
}

int main(int argc, char **argv)
{
	int sockfd, newsockfd, n;
	void *sumval, *primeval;
	struct sockaddr_in server;
	char buf[21];
	pthread_t thread_prime, thread_sum;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("socket() failed");

	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd, (const struct sockaddr *)&server, sizeof(server)) < 0)
		error("bind failed");
	
	if (listen(sockfd, 5) < 0)
		error("listen failed");

	if ((newsockfd = accept(sockfd, NULL, NULL)) < 0)
		error("accept() failed");

	if (recv(newsockfd, buf, sizeof(buf), 0) < 0)
		error("recv failed");
	
	n = atoi(buf);
	pthread_create(&thread_sum, NULL, sumfn, &n);
	pthread_create(&thread_prime, NULL, primefn, &n);

	pthread_join(thread_sum, &sumval);
	pthread_join(thread_prime, &primeval);

	sprintf(buf,"%d %d", *(int *)sumval, *(int *)primeval);
	if (send(newsockfd, buf, strlen(buf), 0) < 0)
		error("send failed");

	free(sumval);
	free(primeval);
	close(newsockfd);
	close(sockfd);

	return 0;
}
