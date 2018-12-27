/*
==========MPI DOT PRODUCT PROGRAM==========");
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
    
    if(size<2){
    fprintf(stderr,"World size must be greater than 1 for %s\n",argv[0]);
    MPI_Abort(MPI_COMM_WORLD,1);
    }
    int i,len=10;
    double dotprod=0.0,partial_dotprod=0.0;
    double *vec1,*vec2;
    vec1 = (double*)malloc(len*sizeof(double));
    vec2 = (double*)malloc(len*sizeof(double));
    
    // Rescaling the parameters 
    int startval = len * rank/size + 1;
    int endval = len * (rank+1) / size;

    // Assigning values to vectors
    for(i=startval;i<=endval;i++){
    vec1[i]=1.0; // vec1 = [1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0]
    vec2[i]=i*1.;// vec2=[0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0]
    }

    // Computing Partial Dot Product
    for(i=0;i<len;i++){
    partial_dotprod+=vec1[i]*vec2[i];
    }
    printf("\nTask: %d Partial Sum: %f\n",rank,partial_dotprod);

    // Combining Partial Products to Global Dot Product
    MPI_Reduce(&partial_dotprod,&dotprod,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    
    if(rank==0){
    printf("\nDot Product = %f\n",dotprod);}
    
    // Blocks until all processes in the communicator have reached this routine
    MPI_Barrier(MPI_COMM_WORLD);
    
    // Finalising MPI environment
    MPI_Finalize();
    return 0;
}
