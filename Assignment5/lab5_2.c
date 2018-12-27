#include "mpi.h"
#include <stdio.h>
#include<stdlib.h>
#define NUM 1000
void main (int argc, char *argv[])
{

    int numtasks, rank, rc, i, dest = 1, tag = 111, source = 0, size;
    double *data, result;
    void *buffer;

    data=(double*)malloc(sizeof(double)*NUM);
    if(data==NULL)
    {
        printf("Unable to allocate memory\n");
        return;
    }
    MPI_Status status;

    MPI_Init (&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);


    for (i = 0; i < NUM; i++)
        data[i] = (double) random ();

    if (rank == 0)
        source=numtasks-1;
    else
        source=rank-1;
    if(rank==numtasks-1)
        dest=0;
    else
        dest=rank+1;

    printf("Rank %d sending data to rank %d\n",rank,dest);
    MPI_Send(data, NUM, MPI_DOUBLE, dest, tag,MPI_COMM_WORLD);
    printf("Rank %d send complete\n",rank);

    printf("Rank %d receiving data from rank %d\n",rank,source);
    MPI_Recv (data, NUM, MPI_DOUBLE, source, tag, MPI_COMM_WORLD,&status);
    printf("Rank %d received data from rank %d\n",rank,source);
    MPI_Finalize ();
}