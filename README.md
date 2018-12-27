# Parallel-and-Distributed-Computing-Lab
My solutions to lab assignments for the course CSE 4001
## Instructions for running OpenMP
```
gcc -fopenmp filename.c
./a.out filename.c
```
## Instructions for MPI
Install MPI
```
mpicc filename.c
mpirun -np x ./a.out
```
Where x is the number of processors
