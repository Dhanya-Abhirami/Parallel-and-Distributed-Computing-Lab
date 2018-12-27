/*
==========MPI SUM USING BROADCAST AND REDUCE PROGRAM==========");
S. DHANYA ABHIRAMI
16BCE0965
Calculating sum of first 1000 natural numbers
*/
#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include<stdlib.h>
int main(int argc, char **argv)
{
	int rank, size,num, N=1000;
	int i, n, low, high, partial_sum=0, global_sum;
	double startwtime,endwtime;
	int* array = (int*)malloc(N*sizeof(int));
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank==0) {
		for(i=0; i<N; i++) {
			array[i]=i+1;
		}
		printf("==========SUM OF 1000 NATURAL NUMBERS==========\n");
        printf("\t\t\tS. DHANYA ABHIRAMI\n\t\t\t16BCE0965\n");
		startwtime = MPI_Wtime();
	}

	MPI_Bcast(array, N, MPI_INT, 0, MPI_COMM_WORLD);
	
	n = N/size;	
	low = N * rank / size;
	high = N * (rank+1) / size;
	for(i=low; i<high; i++) {
		partial_sum += array[i];
	}
	printf("Process %d Partial Sum %d\n", rank,partial_sum);

	/* compute global sum */
	MPI_Reduce(&partial_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(0 == rank) {
		endwtime = MPI_Wtime();
		printf("Global Sum = %d\n", global_sum);
		printf("Wall Clock Time: %lf\n",endwtime- startwtime );
	}

	MPI_Finalize();
}