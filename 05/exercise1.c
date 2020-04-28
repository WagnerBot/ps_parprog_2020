// Peter Koll, Jonas Wagner
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <limits.h>

int main(int argc, char **argv) {
  if (argc != 3) {
		fprintf(stderr, "Error: usage: %s <threads> <iterations>\n", argv[0]);
		return EXIT_FAILURE;
	}
  int threads = atoi(argv[1]);
  int N = atoi(argv[2]);
  int globalcounter = 0;
	double start = 0;
	double end = 0;

  start = omp_get_wtime();
  #pragma omp parallel num_threads(threads)
  {
		#pragma omp for
    for(int i = 0; i < N; i++){
    	#pragma omp atomic
	      globalcounter += i;
		}

  }
  end = omp_get_wtime();
	printf("Threads (%d), Iterations (%d), Time taken: %f\n", threads, N, end-start);
}
