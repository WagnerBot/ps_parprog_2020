// Peter Koll, Jonas Wagner
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <limits.h>

int main(int argc, char **argv) {
  if (argc != 3) {
		fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
		return EXIT_FAILURE;
	}
  int threads = atoi(argv[1]);
	int construct = atoi(argv[2]);
  int N = 500000000;
  int globalcounter = 0;
  double pi;
	double start = 0;
	double end = 0;

	if(construct == 1 || construct == 2){
	  start = omp_get_wtime();
	  #pragma omp parallel num_threads(threads)
	  {
			double x, y, z;
			unsigned seed = 48561431;
			int counter = 0;
			#pragma omp for
	    for(int i = 0; i < N; i++){
	      x = (double) rand_r(&seed) / RAND_MAX;
	      y = (double) rand_r(&seed) / RAND_MAX;
	      z = x * x + y * y;
	      if(z <= 1) counter++;
	    }

			if(construct == 1){
				#pragma omp critical (globalcounter)
		    {
		      globalcounter += counter;
		    }
			}

			else if(construct == 2){
				#pragma omp atomic
					globalcounter += counter;
			}
	  }
	  end = omp_get_wtime();
	}

	else if(construct == 3){
		start = omp_get_wtime();
		#pragma omp parallel num_threads(threads)
		{
			double x, y, z;
			unsigned seed = 48561431;
			#pragma omp for reduction(+:globalcounter)
			for(int i = 0; i < N; i++){
				x = (double) rand_r(&seed) / RAND_MAX;
				y = (double) rand_r(&seed) / RAND_MAX;
				z = x * x + y * y;
				if(z <= 1) globalcounter++;
			}
		}
		end = omp_get_wtime();
	}

	pi = (double) globalcounter / N * 4;


	if(construct == 1)
		printf("Critical/ %d thread(s): Work took %f seconds, Pi = %f\n", threads, end - start, pi);

	else if(construct == 2)
		printf("Atomic/ %d thread(s): Work took %f seconds, Pi = %f\n", threads, end - start, pi);

	else if(construct == 3)
		printf("Reduction/ %d thread(s): Work took %f seconds, Pi = %f\n", threads, end - start, pi);

  return EXIT_SUCCESS;
}
