/*
*	Author: Avinash Sonawane <rootkea@gmail.com>
*	Title : Design a distributed application using Message Passing Interface 
*			(MPI) for remote computation where client submits a string to the
*			server and server returns the reverse of it to the client.
*	License: GPLv3 or later
*/

#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <stdlib.h>

void error(char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char **argv) 
{
	int rank, retval, len;
	char buff[21];

	retval = MPI_Init(&argc, &argv);
	if(retval != MPI_SUCCESS)
		error("MPI_Init failed");

	retval = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(retval != MPI_SUCCESS)
		error("MPI_Comm_rank failed");


	if(rank)
	{
		printf("String: ");
		scanf("%20s", buff);

		retval = MPI_Send(buff, strlen(buff)+1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
		if(retval != MPI_SUCCESS)
			error("MPI_Send failed in rank 1");

		len = strlen(buff);
		int i;
		for(i = 0; i < len; i++)
		{
			retval = MPI_Recv(&buff[i], 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(retval != MPI_SUCCESS)
				error("MPI_Recv failed in rank 1");
		}
		retval = MPI_Recv(&buff[i], 1, MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if(retval != MPI_SUCCESS)
			error("MPI_Recv failed in rank 1");

		printf("Reversed string : %s\n", buff);

	}
	else
	{
printf("On rank 0\n");
		retval = MPI_Recv(buff, sizeof(buff), MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if(retval != MPI_SUCCESS)
			error("MPI_Recv failed in rank 0");

printf("buff = %s\n", buff);

		for(len = strlen(buff) - 1; len >= 0; len--)
		{
			retval = MPI_Send(&buff[len], 1, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
			if(retval != MPI_SUCCESS)
				error("MPI_Send failed in rank 0");
		}
		retval = MPI_Send(&buff[strlen(buff)], 1, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
		if(retval != MPI_SUCCESS)
			error("MPI_Send failed in rank 0");
	}

	retval = MPI_Finalize();
	if(retval != MPI_SUCCESS)
		error("MPI_Finalize failed");

	return 0;
}
