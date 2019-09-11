/*
Emmanuel Rovirosa
Sept 2019
Practice using openMP by doing matrix multiplication
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int size = 500;
int NUMT = 16;
void createMatrix(int Matrix [size][size])
{
	for(int x=0; x<size; x++)
	{
		for(int y=0; y<size; y++)
		{
			Matrix [y][x] = rand()%10;
	 //change to random number later
		}
	}
}

void writeMatrix(int Matrix[size][size])
{
	for(int x=0; x<size; x++)
	{
		for(int y=0; y<size; y++)
		{
			printf("%d ", Matrix [y][x]);
		}
		printf("\n");
	}
}
void transpose(int sMatrix[size][size],int dMatrix[size][size])
{
	for(int x=0; x<size; x++)
	{
		for(int y=0; y<size; y++)
		{
			dMatrix[x][y] = sMatrix[y][x];
		}
	}
}
void Multiply(int M1[size][size],int M2[size][size],int dMatrix[size][size])
{
	int M2Trans[size][size];
	transpose(M2, M2Trans);
	//printf("M2 transposed:\n");
	//writeMatrix(M2Trans);
	omp_set_num_threads(NUMT);	
	
	int sum;
	#pragma omp parallel for
	for(int y1=0; y1<size; y1++)
	{
		for(int y2=0; y2<size; y2++)
		{
			sum=0;
			for(int x=0; x<size; x++)
			{
				//printf("M1[%d][%d] = %d\n",y1,x,M1[y1][x]);
				//printf("M2Transposed[%d][%d] = %d\n",y1,x,M2Trans[y2][x]);	
				sum = sum+(M1[x][y1]*M2Trans[x][y2]);
			}
			dMatrix[y2][y1] = sum;
		}
	}

}

int main (void)
{
	int M1[size][size];
	int M2[size][size];

	srand((unsigned)time(NULL));
	createMatrix(M1);
	createMatrix(M2);

	/*
	printf("M1:\n");
	writeMatrix(M1);
	printf("M2:\n");
	writeMatrix(M2);
	*/

	int FinalMatrix[size][size];
	double time0 = omp_get_wtime();
	for(int i =0; i<10; i++)
	{	
		Multiply(M1, M2, FinalMatrix);
	}
	double time1 = omp_get_wtime();
	printf("Elapsed time = %10.2lf microsecondSSSS\n", 1000000*(time1-time0));
	//printf("Answer:\n");
	//writeMatrix(FinalMatrix);
}
