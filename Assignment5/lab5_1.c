/*
==========MPI PROGRAM FOR BINARY SEARCH==========");
S. DHANYA ABHIRAMI
16BCE0965
Searching for an element in a array
*/
#include <stdio.h>
#include "mpi.h"
#include<stdlib.h>
int main(int argc,char *argv[]) 
{
    int rank, size;
    int n=10,i, first, middle, last, find;
    MPI_Init(&argc,&argv); 
    MPI_Comm_size(MPI_COMM_WORLD,&size); 
    MPI_Comm_rank(MPI_COMM_WORLD,&rank); 
    int* array = (int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
    array[i]=i*2+5;
    if(rank==0)
    {
     printf("==========BINARY SEARCH USING MPI==========\n");
        printf("\t\t\tS. DHANYA ABHIRAMI\n\t\t\t16BCE0965\n");
        printf("Array: ");
     for(i=0;i<n;i++)
      printf("%d ",array[i] );
     printf("\nEnter element to be searched: ");
     scanf("%d", &find);
    }
    first = 0;
    last = n - 1;
    middle = (first+last)/2;

    while (first <= last) {
      if (array[middle] < find)
         first = middle + 1;    
      else if (array[middle] == find) {
         printf("%d found at position : %d\n", find, middle+1);
         break;
      }
      else
         last = middle - 1;

      middle = (first + last)/2;
    }
    MPI_Finalize(); 
    if(rank==0){
      if (first > last)
      printf("Not found\n");
    }
    

    return 0;  
}