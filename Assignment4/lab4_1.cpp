/*
==========MPI HELLO WORLD PROGRAM==========");
S. DHANYA ABHIRAMI
16BCE0965
*/
#include "mpi.h"
#include <stdio.h>

int main( int argc, char *argv[] )
{
    int rank, size;
    // Initialisig MPI Environment
    MPI_Init( &argc, &argv );
    // Getting Rank of process
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    // Getting number of processors
    MPI_Comm_size( MPI_COMM_WORLD, &size );
    // Getting Name of Processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name,&name_len);
    printf( "Hello world from processor %s, rank %d out of %d processors\n", processor_name, rank, size );
    // Finalising MPI environment
    MPI_Finalize();
    return 0;
}
