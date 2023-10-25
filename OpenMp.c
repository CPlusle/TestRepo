#include <omp.h>
#include <stdio.h>

void main(){
	
	int nthreads;

	for (int i = 0; i < 8; i++) {
		#pragma omp parallel for num_threads(2)
		for (int j = 0; j < 8; j++) {
			nthreads = omp_get_thread_num();
			if (nthreads == 0) {
				printf("Thread: %d, i=%d, j=%d \n", nthreads, i, j);
			}
		}
	}
}