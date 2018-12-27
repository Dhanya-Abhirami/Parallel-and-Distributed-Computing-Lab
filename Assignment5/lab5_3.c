/*
==========MPI PROGRAM FOR SQUARING AN ARRAY==========");
S. DHANYA ABHIRAMI
16BCE0965
Squaring the elements in a array
*/
#include <stdio.h> 
#include "mpi.h" 
#include <stdlib.h> 
int main(int argc,char *argv[]) 

    {  
        int size,rank; 
        int i,N=10;
        int* array = (int*)malloc(N*sizeof(int));
        int* sq_array = (int*)malloc(N*sizeof(int));
        if(rank==0)
        {
            for (i = 0; i < N; i++)
            array[i] = i+1;
        }
        MPI_Init(&argc,&argv); 
        MPI_Comm_size(MPI_COMM_WORLD,&size); 
        MPI_Comm_rank(MPI_COMM_WORLD,&rank); 
        for(i=0;i<N;i++) 
        { 
            sq_array[i]=array[i]*array[i]; 
        } 
        MPI_Finalize(); 
        if(rank==0)
        {
            printf("==========SQUARING ARRAY USING MPI==========\n");
        printf("\t\t\tS. DHANYA ABHIRAMI\n\t\t\t16BCE0965\n");
        printf("Input Array\n");
            for(i=0;i<N;i++)
        printf("%d ",array[i]);
        printf("\nSquared Array\n");
            for(i=0;i<N;i++)
        printf("%d ",sq_array[i]);
        printf("\n");}
        return 0; 

    }