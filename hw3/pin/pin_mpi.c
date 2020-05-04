// The PIN is 221 (nprocs = 40, time = 20.65 sec.)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mpi.h>
#include <time.h>


int num_procs; //How many processes were started.
int rank; //Find out MY process ID
// int root_process;
// int local;
int global_result;

int main(int argc, char *argv[]) {
  clock_t start = clock();

  MPI_Init(&argc, &argv);

  assert(argc==2);

  MPI_Barrier(MPI_COMM_WORLD);
  double stop = (double)atol(argv[1]); //input from user on how many iterations
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  assert(stop >= 1.0);

  int result = 0;

  //for (double x = 0.0; x < stop; x += 1.0) {
  for (double x=(double)rank; x< stop; x+=(double)num_procs){
    double tmp = sin(x);
    double tmp2 = tmp*tmp;
    int z = (int)(tmp2*10000.0);
    
    result = (result + z)%10000; // 0<=result<10000

#ifdef DEBUG
    printf("x=%lf, y=%lf, z=%d\n", x, y, z);
    printf("new result : %d\n", result);
    fflush(stdout);
#endif
  }

  MPI_Reduce(&result, &global_result,1,MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
  global_result = global_result %10000;
  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Finalize();
  clock_t finish = clock();
  double timeElapsed = (double)(finish-start)/CLOCKS_PER_SEC;
  if (rank == 0){
      printf("The PIN is %d (nprocs = %d, time = %.2f sec.)\n", 
	global_result, num_procs, timeElapsed);
  }
  fflush(stdout);
}

