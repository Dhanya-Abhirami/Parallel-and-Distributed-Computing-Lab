#include	<stdio.h>
#include	<mpi.h>

void main(int argc, char *argv[])
{
  int myrank, nprocs, leftid, rightid;
  int val, sum, tmp;
  MPI_Status recv_status, send_status;
  MPI_Request send_request;
  
  /*----------------*/
  /* Initialize MPI */
  /*----------------*/

  MPI_Init(&argc, &argv);

  /*--------------------------------------------------------------------*/
  /* Find out my rank and size using global communicator MPI_COMM_WORLD */
  /*--------------------------------------------------------------------*/

  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
     
  /*--------------------*/
  /* Find out neighbors */
  /*--------------------*/

  if ((leftid=(myrank-1)) < 0) leftid = nprocs-1;
  if ((rightid=(myrank+1)) == nprocs) rightid = 0;
  
  /*---------------------------------------------------------------------*/
  /* Send the process rank stored as val to the process on my right and  */
  /* receive a process rank from the process on my left and store as tmp */
  /*---------------------------------------------------------------------*/

  val = myrank;
  sum = 0;
  do {
    MPI_Issend(&val,1,MPI_INT,rightid,99,MPI_COMM_WORLD,&send_request);
    MPI_Recv(&tmp,1,MPI_INT,leftid,99,MPI_COMM_WORLD,&recv_status);
    MPI_Wait(&send_request,&send_status);
    val = tmp;
    sum += val;
  } while (val != myrank);

  /*--------------------------*/
  /* Print the output message */
  /*--------------------------*/

  printf("Proc %d sum = %d \n", myrank, sum);

  /*-----------------------*/
  /* Exit and finalize MPI */
  /*-----------------------*/

  MPI_Finalize();

}