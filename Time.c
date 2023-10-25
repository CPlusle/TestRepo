#include<time.h>
#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

void main(){
	double *vector;
	double *result;
	double **matrix;
	double time;
	int rows;
	int columns;
	int nthreads;
	clock_t start_time, end_time;

	rows = 30000;
	columns = 30000; 

	result = (double *)malloc((sizeof(double) * columns));
	vector = (double *)malloc((sizeof(double) * rows));

	matrix = (double **)malloc((sizeof(double *) * rows));

	for(int i=0; i<rows; i++){
		matrix[i] = (double *)malloc((sizeof(double) * columns));
	}

	for(int i=0; i<rows; i++){
		vector[i] = 1;
		for(int j=0; j<columns; j++){
			matrix[i][j] = 1;
		}
	}

	//  Normal  //
	start_time = clock();
	printf("//  Normal  //\n");

	for(int j=0; j<columns; j++){
		for(int i=0; i<rows; i++){
			result[j] += matrix[j][i] * vector[i];
		}
	}
	end_time = clock();

	time = (end_time-start_time);
	printf("Time: %f \n", time);

	printf("Result: %f \n \n", result[1]);
	
	//Result neu auf 0
	for(int i=0; i<columns; i++){
		result[i] = 0;
	}

	//  Flipped //
	start_time = clock();
	printf("//  Flipped  //\n");

	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			result[j] += matrix[j][i] * vector[i];
		}
	}
	end_time = clock();

	time = (end_time-start_time);
	printf("Time: %f \n", time);

	printf("Result: %f \n \n", result[1]);

	//Result neu auf 0
	for(int i=0; i<columns; i++){
		result[i] = 0;
	}

	//  OpenMp  //
	start_time = clock();
	printf("//  OpenMP  //\n");

	for(int i=0; i<rows; i++){
		#pragma omp parallel for num_threads(4)
		for(int j=0; j<columns; j++){
			nthreads = omp_get_thread_num();
			result[j] += matrix[j][i] * vector[i];
		}
	}
	end_time = clock();

	time = (end_time-start_time);
	printf("Time: %f \n", time);

	printf("Result: %f \n", result[1]);
}
