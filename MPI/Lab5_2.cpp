#include <mpi.h>
#include <cmath>
#include <stdio.h>

int main(int argc, char** argv)
{
	int done = 0, n = 10, e, myid, numprocs, i;
	double PI25DT = 3.141592653589793238462643;
	double myresult, result, h, sinsquared, x, start_time, b = PI25DT / 2, a = 0;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	while (!done)
	{
		if (myid == 0)
		{
			printf("Enter N for number of intervals in 1E^N format: (0-quit)\n");
			fflush(stdout); // prevent scanf_s from hanging
			scanf_s("%d", &e);
			start_time = MPI_Wtime(); // start time tracking after the iterations amount was entered
			if (e == 1) {
				n = 10;
			}
			for (int i = 1; i < e; i++) {
				n *= 10;
			}
			printf("The number of iterations is: %d\n", n);;
		}
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		if (n == 0)
			break;
		h = (b - a) / (double)n;
		sinsquared = 0.0;
		for (i = myid + 1; i <= n; i += numprocs)
		{
			x = h * ((double)i - 0.5);
			sinsquared = sin(x) * sin(x);
		}
		myresult = h * sinsquared;
		MPI_Reduce(&myresult, &result, 1, MPI_DOUBLE, MPI_SUM, 0,
			MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD); // using the barrier to calculate the overall time properly
		if (myid == 0)
		{
			n = 10;
			printf("result is approximately %.16f\n", result);
			printf("Time elapsed: %f seconds\n", MPI_Wtime() - start_time);
		}
	}
	MPI_Finalize();
	return 0;
}