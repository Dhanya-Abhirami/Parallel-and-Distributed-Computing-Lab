/*
==========MPI PROGRAM TO CALCULATE VALUE OF PI==========");
S. DHANYA ABHIRAMI
16BCE0965
tan(pi/4) = 1
arctan(1) = pi/4
d(arctan(x))/dx = 1.0/(1+x*x)
Performing numerical integration and multiplying by 4
*/
#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int n;
    double PI25DT = 3.141592653589793238462643;
    double local_value, h, pi, i, sum, x, dx_arctan, startwtime, endwtime;
    int rank, size, resultlen;

    MPI_Init(&argc,&argv);    
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if (rank==0){
        printf("==========APPROXIMATING VALUE OF PI USING BROADCAST AND REDUCE==========\n");
    printf("\t\t\t\t\tS. DHANYA ABHIRAMI\n\t\t\t\t\t16BCE0965\n\n");
    }
    if(rank == 0) 
    {	
    // n = number of evaluation points
    n = 100000;
    printf("The number of intervals = %d \n", n); 
    startwtime = MPI_Wtime();
    }

    // Share intervals with other processors 
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    sum = 0.0;
    h   = 1.0/n;
    // Computing and Adding the "Heights" of each bar of the integration
    for (i=rank+0.5; i<n; i+=size)
    {
        // Derivative of arctan
        dx_arctan = 1.0 / (1.0 + (i*h)*(i*h));
        sum += dx_arctan;
    }
    // Multiplying by the "Widths" of each bar and 4.0 (arctan(1)=Pi/4) 
    local_value = 4.0*h*sum;
    /* Show all processor IDs */
    printf("Process-%d Local value = %lf \n",rank,local_value);
    // Consolidate and Sum Results
    MPI_Reduce(&local_value, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        endwtime = MPI_Wtime();
        printf("pi = (approx) %.16f\nError is %.16f\n",pi, fabs(pi - PI25DT)); 
        printf("Execution Wall clock time = %f\n", endwtime-startwtime); 
    }
    MPI_Finalize();
    return 0;
}


