/*
==========MPI AVERAGE PROGRAM==========");
S. DHANYA ABHIRAMI
16BCE0965
Calculating average of first 100 natural numbers
*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int rank, size, i ;
    int n , begin, end, N=100 ;
    
    // Initialisig MPI Environment
    MPI_Init( &argc , &argv );
    
    // Getting number of processors
    MPI_Comm_size(MPI_COMM_WORLD , &size);
    
    // Getting Rank of process
    MPI_Comm_rank(MPI_COMM_WORLD , &rank);
    
    // Rescaling the parameters 
    begin = N * rank/size +1;
    end = N * (rank+1) / size;

    n = N / size;

    // The array
    int* array = (int*)malloc(N*sizeof(int));
    for (i = begin; i <= end; i++) {
        array[i] = i;
    }

    // Find the partial sum
    int partial_sum = 0;
    for (i = begin; i <= end; i++) {
        partial_sum = partial_sum+array[i];
    }

    // Print the random numbers on each process
    printf("For process %d Partial sum = %d, Avg = %d\n",
        rank, partial_sum, partial_sum / n);
        
        
    // Using MPI_Reduce to reduce the ocal sums into global sum
    int global_sum=0;
    MPI_Reduce(&partial_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0,MPI_COMM_WORLD);

    // Computing Average
    if (rank == 0) {
       printf("Total sum = %d, Avg = %d\n", global_sum,
       global_sum/(size*n)); 
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();
}