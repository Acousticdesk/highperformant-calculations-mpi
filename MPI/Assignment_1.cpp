#include "mpi.h"
#include <stdio.h>
#include <string>
bool isEven(int num)
{
	return num % 2 == 0;
}

int main(int argc, char* argv[])
{
	int size, rank, i;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0)
	{
		printf("Amount of processes=%d\n", size);
	}
	std::string evenOrOdd = isEven(rank) ? "even" : "odd";
	printf("My rank is %d. I am %s", rank, evenOrOdd.c_str());
	MPI_Finalize();
	return 0;
}
