/*
==========MPI SUM USING GATHER SCATTER PROGRAM==========");
S. DHANYA ABHIRAMI
16BCE0965
Calculating sum of first 1000 natural numbers
*/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int rank, size, i ;
    int n ,partial_sum, N=1000, global_sum=0 ;
    // Initialisig MPI Environment
    MPI_Init( &argc , &argv );
    
    // Getting number of processors
    MPI_Comm_size(MPI_COMM_WORLD , &size);
    
    // Getting Rank of process
    MPI_Comm_rank(MPI_COMM_WORLD , &rank); 

    // The array
    int* array = (int*)malloc(N*sizeof(int));
    if(rank==0){
    for (i = 0; i < N; i++) {
        array[i] = i+1;
    }
    printf("==========SUM OF 1000 NATURAL NUMBERS==========\n");
    printf("\t\t\tS. DHANYA ABHIRAMI\n\t\t\t16BCE0965\n\n");
    }
    
    
    n = N/size;
    int* sub_array = (int*)malloc(n*sizeof(int));
    int* sums = (int*)malloc(size*sizeof(int));

    // Scatter sub arrays to processess 
    MPI_Scatter(array,n,MPI_INT,sub_array,n,MPI_INT,0,MPI_COMM_WORLD);

    // Calculate partial sum of the sub array
    partial_sum = 0;
    for(i=0;i<n;i++)
        partial_sum+=sub_array[i];
    printf("Process %d Partial Sum = %d\n",rank,partial_sum);
    // Combine the partial sums into an array
    MPI_Gather(&partial_sum,1,MPI_INT, sums, 1,MPI_INT,0,MPI_COMM_WORLD);
    
    if(rank == 0)
    {
        for(i=0;i<size;i++)
            {
                global_sum+=sums[i];
            }
        printf("\n\nGlobal Sum = %d\n",global_sum );
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Finalize();
}