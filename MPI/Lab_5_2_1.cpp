#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define n_in_proc 1000000
#define RAND_MAX 32767

int main(int argc, char* argv[])
{
	time_t t;
	int rank, numprocs, i, N_in_proc;
	long j, in_circle = 0L, total_in_circle, total;
	double x, y, R = 0.5, approx,
		pi = 3.141592653589793238462643;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) N_in_proc = atoi(argv[1]);
	MPI_Bcast(&N_in_proc, 1, MPI_INT, 0, MPI_COMM_WORLD);
	for (i = 0; i < N_in_proc; i++)
	{
		srand((unsigned int)time(&t));
		for (j = 0L; j < n_in_proc; j++)
		{
			x = rand() / (double)RAND_MAX - 0.5;
			y = rand() / (double)RAND_MAX - 0.5;
			// check if a randomly generated point is in the unary circle 
			if (x * x + y * y < R * R)
				in_circle++;
		}
		/*printf("x: %lf\n", x);
		printf("y: %lf\n", y);*/
		MPI_Reduce(&in_circle, &total_in_circle, 1, MPI_INT,
			MPI_SUM, 0, MPI_COMM_WORLD);
		if (rank == 0)
		{
			total = n_in_proc * (i + 1) * numprocs;
			approx = 4.0 * ((double)total_in_circle / total);
			printf("pi=%.16f; error=%.16f, points=%ld\n",
				approx, fabs(pi - approx), total);
		}
	}
	MPI_Finalize();
	return 0;
}