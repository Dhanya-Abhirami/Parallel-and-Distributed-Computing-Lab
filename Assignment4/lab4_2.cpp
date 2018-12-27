/*
==========MPI SEND AND RECEIVE PROGRAM==========");
S. DHANYA ABHIRAMI
16BCE0965
*/
#include<mpi.h>
#include<stdlib.h>
#include <stdio.h>

int main( int argc, char *argv[] )
{
    // Initialisig MPI Environment
    MPI_Init( &argc, &argv );
    int rank, size;
    // Getting Rank of process
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    // Getting number of processors
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    // Assuming at least 2 processess for this task
    if(size<2){
        fprintf(stderr,"World size must be greater than 1 for %s\n",argv[0]);
        MPI_Abort(MPI_COMM_WORLD,1);
    }
    int number;
    // If rank = 0, set number to -1 and send it to process 1
    if(rank==0){
        number=-1;
        // MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
        MPI_Send(&number,1,MPI_INT,1,0,MPI_COMM_WORLD);
    }
    else if(rank==1){
        // MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag,MPI_Comm comm, MPI_Status *status)
        MPI_Recv(&number,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    	printf("Process 1 received %d from process 0\n",number);
    }
    MPI_Finalize();
    return 0;
}
