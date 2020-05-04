CC = cc -pedantic -std=c11
MPICC = mpicc -pedantic -std=c11

HOST := $(shell hostname)
ifeq ($(HOST),cisc372)
RUN = srun
else
RUN = mpiexec
endif
run: pi_mpi
	$(RUN) -n 4 ./pi_mpi

run_seq : pi
	$(RUN) -n 1 ./pi

pi : pi.c
	$(CC) -o pi pi.c $(LINKS)

pi_mpi : pi_mpi.c
	$(MPICC) -o pi_mpi pi_mpi.c $(LINKS)

clean :
	rm -f pi pi_mpi *~ a.out
