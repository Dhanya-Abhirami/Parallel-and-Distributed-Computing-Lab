/*
==========MPI PROGRAM RING COMMUNICATION==========");
S. DHANYA ABHIRAMI
16BCE0965
Ring Communication
*/
#include	<stdio.h>
#include	<mpi.h>

void main(int argc, char *argv[])
{
  int rank, size, leftid, rightid;
  int val, sum, tmp;
  MPI_Status wait_status;
  MPI_Request recv_request;
  
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (rank==0){
        printf("==========MPI PROGRAM RING COMMUNICATION==========\n");
    printf("\t\t\t\t\tS. DHANYA ABHIRAMI\n\t\t\t\t\t16BCE0965\n\n");
    }  
  
  if ((leftid=(rank-1)) < 0) leftid = size-1;
  if ((rightid=(rank+1)) == size) rightid = 0;
  
  val = rank;
  sum = 0;
  do {
    MPI_Irecv(&tmp,1, MPI_INT, leftid, 99, MPI_COMM_WORLD, &recv_request);
    
    MPI_Ssend(&val,1,MPI_INT,rightid,99, MPI_COMM_WORLD);
    
    MPI_Wait(&recv_request,&wait_status);
    
    val = tmp;
    sum += val;
  } while (val != rank);
  printf("\nProcess %d \nReceived from %d \nSends To %d Value %d\n",rank,leftid,rightid,val);
  MPI_Finalize();

}