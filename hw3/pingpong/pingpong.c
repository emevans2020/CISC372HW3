/* The program will measure the time for sending a message between
process 0 and another process i!=0. It will do this for 1<=i<nprocs.

Given i, the ping-pong game works like this: process 0 marks the time.
It then sends a message (the ping) of 0 bytes to process i. Process i
receives the message and sends back a message of 0 bytes (the pong).
*/
#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define NPINGS 1000000

int num_procs, rank;

int main(int argc, char *argv[]) {
    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    
    if (rank == 0) {
        for (int i = 1; i<num_procs; i++) {
	    clock_t start = clock();
		for (int j = 0; j < NPINGS; j++) {	
		    MPI_Send(NULL, 0, MPI_CHAR, i, j, MPI_COMM_WORLD);
		    MPI_Recv(NULL, 0, MPI_CHAR, i, j, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		clock_t end = clock();
		double total_t = (double)(end-start)/CLOCKS_PER_SEC;
		double mean = (total_t)/(2*(double)NPINGS);
		printf("Average time to transmit between 0 and %d: %11.10f\n", i, mean);
	}
    } else {
	for (int j = 0; j < NPINGS; j++) {
		MPI_Recv(NULL, 0, MPI_CHAR, 0, j, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Send(NULL, 0, MPI_CHAR, 0, j, MPI_COMM_WORLD);
	    }
	}
	fflush(stdout);
	MPI_Finalize(); 
}
