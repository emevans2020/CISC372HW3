CC = cc -pedantic -std=c11
MPICC = mpicc -pedantic -std=c11
LINKS = -lm

HOST := $(shell hostname)
ifeq ($(HOST),cisc372)
RUN = srun
else
RUN = mpiexec
endif

all : pingpong.exe
	$(RUN) -n 20 ./pingpong.exe

pingpong.exe : pingpong.c
	$(MPICC) -o pingpong.exe pingpong.c $(LINKS)

clean :
	rm -f *.exe *~
