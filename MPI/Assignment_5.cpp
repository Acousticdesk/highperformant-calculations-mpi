#include "mpi.h"

int main(int argc, char* argv[])
{
	int size, rank, i;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
  // A current code block will be available to each and every process that runs during the app run
  for (int i = 0; i < size; i++)
  {
    int *dynamicArray = new int[size * rank];
  }
  
	MPI_Finalize();
	return 0;
}
