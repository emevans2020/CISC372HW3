#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <mpi.h>
#include <time.h>
#define INTERVALS 5000000000L

//Pi run: Pi is  3.14159265358979357
//pi run_seq: Pi is  3.14159265358979079
// Emily Evans March 8 2020

int rank, num_procs;
long double global_area;

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  long double area = 0.0;
  long double xi;
  long i;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  // for (i=0; i<INTERVALS; i++) {
  for (i = (long) rank; i<INTERVALS; i+=(long)num_procs){
    xi=(1.0L/INTERVALS)*(i+0.5L);
    area += 4.0L/(INTERVALS*(1.0L+xi*xi));
  }
  MPI_Reduce(&area, &global_area,1,MPI_LONG_DOUBLE, MPI_SUM,0,MPI_COMM_WORLD);
  
  fflush(stdout);

  MPI_Finalize();

  if (rank == 0){
    printf("Pi is %20.17Lf\n", global_area);
  }
}
