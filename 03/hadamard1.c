//Peter Koll, Jonas Wagner
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int SIZE = 10000;

int main(int argc, char* argv[]){
  double start, end;
  int n_threads = atoi(argv[1]);

  int **a = (int**)malloc(SIZE * sizeof(int*));
  int **b = (int**)malloc(SIZE * sizeof(int*));
  int **c = (int**)malloc(SIZE * sizeof(int*));

  for(int i = 0; i < SIZE; i++){
    a[i] = (int*)malloc(SIZE * sizeof(int));
    b[i] = (int*)malloc(SIZE * sizeof(int));
    c[i] = (int*)malloc(SIZE * sizeof(int));
  }

  srand(time(NULL));
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < SIZE; j++){
      a[i][j] = rand();
      b[i][j] = rand();
    }
  }

  start = omp_get_wtime();
  #pragma omp parallel for collapse(2) num_threads(n_threads)
    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
          c[i][j] = a[i][j] * b[i][j];
      }
    }
  end = omp_get_wtime();
  printf("Work took %f seconds (%d threads)\n", end - start, n_threads);

  return EXIT_SUCCESS;
}
