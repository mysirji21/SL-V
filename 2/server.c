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
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

struct str
{
	char str1[21];
	char str2[21];
};

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

void *substr(void *num)
{
	struct str *foo = num;
	int *sub = malloc(sizeof(int));
	if(!sub)
		error("malloc failed");
	
	if(strstr(foo->str1, foo->str2))
		*sub = 1;
	else
		*sub = 0;

	pthread_exit(sub);
}

void *cmp(void *num)
{
	struct str *foo = num;
	int *sub = malloc(sizeof(int));
	if(!sub)
		error("malloc failed");
	
	if(strcmp(foo->str1, foo->str2))
		*sub = 0;
	else
		*sub = 1;

	pthread_exit(sub);
}

void *concat(void *num)
{
	struct str *foo = num;
	char *cat = malloc(sizeof(foo->str1) + sizeof(foo->str2));
	if(!cat)
		error("malloc failed");

	cat[0] = '\0';	
	strcat(cat, foo->str1);
	strcat(cat, foo->str2);

	pthread_exit(cat);
}

int main(int argc, char **argv)
{
	int sockfd, newsockfd, n;
	void *sumval, *subval, *cmpval, *concatvar;
	struct sockaddr_in server;
	struct str strvar;
	char buf[21];
	pthread_t thread_substr, thread_sum, thread_cmp, thread_concat;

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

	memset(buf, '\0', sizeof(buf));
	if (recv(newsockfd, buf, sizeof(buf), 0) < 0)
		error("recv failed");
	sscanf(buf, "%20s", strvar.str1);

	memset(buf, '\0', sizeof(buf));
	if (recv(newsockfd, buf, sizeof(buf), 0) < 0)
		error("recv failed");
	sscanf(buf, "%20s", strvar.str2);

	pthread_create(&thread_sum, NULL, sumfn, &n);
	pthread_create(&thread_substr, NULL, substr, &strvar);
	pthread_create(&thread_cmp, NULL, cmp, &strvar);
	pthread_create(&thread_concat, NULL, concat, &strvar);

	pthread_join(thread_sum, &sumval);
	pthread_join(thread_substr, &subval);
	pthread_join(thread_cmp, &cmpval);
	pthread_join(thread_concat, &concatvar);

	sprintf(buf,"%d %d %d", *(int *)sumval, *(int *)subval, *(int *)cmpval);
	if (send(newsockfd, buf, strlen(buf), 0) < 0)
		error("send failed");

	if (send(newsockfd, concatvar, strlen(concatvar), 0) < 0)
		error("send failed");

	free(sumval);
	free(subval);
	free(cmpval);
	free(concatvar);
	close(newsockfd);
	close(sockfd);

	return 0;
}
