#include <stdio.h>
#include <math.h>
#include <time.h>
#include <cstdlib>
#include <mpi.h>

#define RAND_MAX 32767
int main(int argc, char* argv[])
{
	time_t t;
	long i, N = 1000000000;
	double x, y, mc_res = 0.0, total_mc_res = 0.0,
		standard = double(1) / 12;
	double start_time;
	int numprocs, rank;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
	start_time = MPI_Wtime();
	srand((unsigned)time(&t));
	for (i = rank; i < N; i+= numprocs)
	{
		x = rand() / (double)RAND_MAX;
		y = rand() / (double)RAND_MAX;
		mc_res += (x * y) / N;
	}
	MPI_Reduce(&mc_res, &total_mc_res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) {
		printf("mc_res=%.16lf err=%.15lf\n", total_mc_res, fabs(standard - total_mc_res));
		printf("Total time spent: %f seconds", MPI_Wtime() - start_time);
	}
	
	MPI_Finalize();
	return 0;
}