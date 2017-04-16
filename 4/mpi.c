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

void rev(char *);
//********************* Debugging (optional)***************************
void error(int errorcode, char *msg)
{
	int len;
	char string[MPI_MAX_ERROR_STRING];

	MPI_Error_string(errorcode, string, &len);
	fprintf(stderr, "%s: %s\n", msg, string);

	MPI_Abort(MPI_COMM_WORLD, errorcode);
}
//*********************************************************************
int main(int argc, char **argv) 
{
	int rank, retval, size, resultlen;
	char buff[21], name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc, &argv);
	MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);	//debugging

	retval = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(retval != MPI_SUCCESS)
		error(retval, "MPI_Comm_rank failed");
//********************* Debugging (optional)***************************
	retval = MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(retval != MPI_SUCCESS)
		error(retval, "MPI_Comm_size failed");

	retval = MPI_Get_processor_name(name, &resultlen);
	if(retval != MPI_SUCCESS)
		error(retval, "MPI_Comm_Get_processor_name failed");

	printf("Running rank #%d out of %d on %s\n", rank, size, name);
//*********************************************************************
	if(!rank)
	{
		scanf("%20s", buff);

		retval = MPI_Send(buff, strlen(buff)+1, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
		if(retval != MPI_SUCCESS)
			error(retval, "MPI_Send failed in rank 0");

		retval = MPI_Recv(buff, sizeof(buff), MPI_CHAR, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);	
		if(retval != MPI_SUCCESS)
			error(retval, "MPI_Recv failed in rank 0");

		printf("Reversed string : %s\n", buff);
	}
	else
	{
		retval = MPI_Recv(buff, sizeof(buff), MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if(retval != MPI_SUCCESS)
			error(retval, "MPI_Recv failed in rank 1");

		rev(buff);

		retval = MPI_Send(buff, strlen(buff)+1, MPI_CHAR, 0, 1, MPI_COMM_WORLD);
		if(retval != MPI_SUCCESS)
			error(retval, "MPI_Send failed in rank 1");
	}

	retval = MPI_Finalize();
	if(retval != MPI_SUCCESS)
		error(retval, "MPI_Finalize failed");

	return 0;
}

void rev(char *str)
{
	int i, last;
	char temp;

	for(i = 0, last = strlen(str)-1; i < last; i++, last--)
	{
		temp = str[i];
		str[i] = str[last];
		str[last] = temp;
	}

	return ;
}
