#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define n_in_proc 1000000
#define RAND_MAX 32767

double dispersion(double pies[]) {
	double sum = 0;
	double average = 0;
	int num = 0;

	for (int i = 0; i < 100; i++) {
		if (pies[i] == 0) {
			break;
		}

		num++;
		average += pies[i];
	}

	average = average / num;

	for (int i = 0; i < 100; i++) {
		if (pies[i] == 0) {
			break;
		}

		double res = pies[i] - average;
		printf("res %f", res);
		sum += res * res;
	}

	printf("Average %.16f\n", average);
	// printf("Sum %.16f\n", sum);
	printf("Num %d\n", num);

	double res = ((double)1 / num) * sum;

	printf("Dispersion: %.16f\n", res);

	return res;
}

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
	double pies[100] = {0};
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
		MPI_Reduce(&in_circle, &total_in_circle, 1, MPI_INT,
			MPI_SUM, 0, MPI_COMM_WORLD);
		if (rank == 0)
		{
			total = n_in_proc * (i + 1) * numprocs;
			approx = 4.0 * ((double)total_in_circle / total);
			printf("pi=%.16f; error=%.16f, points=%ld\n",
				approx, fabs(pi - approx), total);
			for (int i = 0; i < 100; i++) {
				if (pies[i] == 0) {
					pies[i] = approx;
					printf("PI %.16f", pies[i]);
					break;
				}
			}
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if (rank == 0) {
		double disp = dispersion(pies);
	}
	MPI_Finalize();
	return 0;
}