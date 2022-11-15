//#include <mpi.h>
//#include <stdio.h>
//int main(int argc, char* argv[])
//{
//	int size, rank, count;
//	MPI_Init(&argc, &argv);
//	MPI_Comm_size(MPI_COMM_WORLD, &size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//	unsigned int const bufferSize = rank > 0 ? rank * 10 : 10;
//	/*unsigned int const bufferSize = rank * 10;*/
//	long* buffer = new long[bufferSize];
//	printf("Rank: %d. Buffer size: %d\n", rank, bufferSize);
//	MPI_Status status;
//	if (size != 2)
//	{
//		if (rank == 0)
//		{
//			printf("Only 2 tasks reqiured instead of %d, abort\n", size);
//		}
//		// MPI_Barrier(MPI_COMM_WORLD);
//		MPI_Abort(MPI_COMM_WORLD, MPI_ERR_OTHER);
//		return -1;
//	}
//	if (rank == 1)
//	{
//		for (int i = 0; i < rank + 1; i++)
//		{
//			buffer[i] = i;
//		}
//		// buffer, buffer_len, type, process, id, communicator
//		MPI_Send(buffer, bufferSize, MPI_LONG, 0, 100, MPI_COMM_WORLD);
//	}
//	else
//	{
//		MPI_Recv(buffer, bufferSize, MPI_LONG, 1, 100, MPI_COMM_WORLD, &status);
//		MPI_Get_count(&status, MPI_LONG, &count);
//		for (int i = 0; i < bufferSize; i++) {
//			printf("%d\n", buffer[i]);
//		}
//		printf("Received %d elements\n", count);
//	}
//	MPI_Finalize();
//	// free heap memory from the redeundant array
//	delete[] buffer;
//	return 0;
//}