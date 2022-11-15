#include <mpi.h>
#include <stdio.h>
#include <string>
#include <ctype.h>

int main(int argc, char* argv[])
{
	int size, rank, count;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	unsigned int const bufferSize = 24;
	char buffer[bufferSize] = {0};
	unsigned int buffer2[1];
	float buffer3[1];
	std::string studentName = "Andrii Kicha";
	MPI_Status status;
	if (rank == 0)
	{
		
		// send student name to all the processes
		for (int i = 0; i < studentName.size(); i++)
		{
			// fill in the buffer for rank 0
			buffer[i] = studentName.at(i);
		}

		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				continue;
			}
			MPI_Send(buffer, bufferSize, MPI_CHAR, i, 100, MPI_COMM_WORLD);
		}

		MPI_Recv(buffer, bufferSize, MPI_CHAR, 1, 101, MPI_COMM_WORLD, &status);

		printf("Received a message from rank 1:\n");
		for (int i = 0; i < bufferSize; i++)
		{
			printf("%c", buffer[i]);
		}
		printf("\n");

		MPI_Recv(buffer2, 1, MPI_UNSIGNED, 2, 102, MPI_COMM_WORLD, &status);
		printf("Received a message from rank 2: %d\n", buffer2[0]);

		MPI_Recv(buffer3, 1, MPI_FLOAT, 3, 103, MPI_COMM_WORLD, &status);
		printf("Received a message from rank 3: %f\n", buffer3[0]);
	}
	
	switch (rank)
	{
		case 1:
		{
			MPI_Recv(buffer, bufferSize, MPI_CHAR, 0, 100, MPI_COMM_WORLD, &status);

			std::string studentNameReceived;

			for (int i = 0; i < bufferSize; i++)
			{
				if (buffer[i])
				{
					studentNameReceived += buffer[i];
				}
			}

			std::string studentNameResult = studentName + studentNameReceived;

			for (int i = 0; i < bufferSize; i++)
			{
				buffer[i] = studentNameResult.at(i);
			}

			MPI_Send(buffer, bufferSize, MPI_CHAR, 0, 101, MPI_COMM_WORLD);

			break;
		}
		case 2:
		{
			MPI_Recv(buffer, bufferSize, MPI_CHAR, 0, 100, MPI_COMM_WORLD, &status);

			unsigned int studentNameNumChars = 0;

			for (int i = 0; i < bufferSize; i++)
			{
				if (buffer[i] != 0)
				{
					studentNameNumChars++;
				}
			}

			buffer2[0] = studentNameNumChars;

			MPI_Send(buffer2, 1, MPI_UNSIGNED, 0, 102, MPI_COMM_WORLD);

			break;
		}
		case 3:
		{
			MPI_Recv(buffer, bufferSize, MPI_CHAR, 0, 100, MPI_COMM_WORLD, &status);

			unsigned int studentNameCodesSum = 0;

			for (int i = 0; i < bufferSize; i++)
			{
				if (buffer[i] != 0)
				{
					studentNameCodesSum += int(buffer[i]);
				}
			}

			const double PI = 3.141592653589793238463;

			buffer3[0] = studentNameCodesSum * PI;

			MPI_Send(buffer3, 1, MPI_FLOAT, 0, 103, MPI_COMM_WORLD);

			break;
		}
		default:
			break;
	}

	MPI_Finalize();
	return 0;
}