#include <mpi.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	int size, rank, count;
	double doubleData[20];
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (size != 2)
	{
		if (rank == 0)
		{
			printf("Only 2 tasks reqiured instead of %d, abort\n", size);
		}
		// MPI_Barrier(MPI_COMM_WORLD);
		MPI_Abort(MPI_COMM_WORLD, MPI_ERR_OTHER);
		return -1;
	}
	if (rank == 0)
	{
		// buffer, buffer_len, type, process, id, communicator
		MPI_Send(doubleData, 5, MPI_DOUBLE, 1, 100, MPI_COMM_WORLD);
	}
	else
	{
		MPI_Recv(doubleData, 5, MPI_DOUBLE, 0, 100, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_DOUBLE, &count);
		printf("Received %d elements\n", count);
	}
	MPI_Finalize();
	return 0;
}