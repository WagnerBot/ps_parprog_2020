// Peter Koll, Jonas Wagner
// Inspiration: https://www.geeksforgeeks.org/merge-sort/
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <errno.h>
#include <string.h>

int min(int x, int y) {
	return (x < y) ? x : y;
}

void merge(int arr[], int l, int m, int r) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 =  r - m;
	int32_t *L = malloc(n1 * sizeof(int32_t));
	int32_t *R = malloc(n2 * sizeof(int32_t));

  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1+ j];

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2){
    if (L[i] <= R[j]){
      arr[k] = L[i];
      i++;
    }
    else{
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
  }

	free(L);
	free(R);
}

void mergeSortSequential(int arr[], int l, int r) {
  if (l < r) {
    int m = l+(r-l)/2;
    mergeSortSequential(arr, l, m);
    mergeSortSequential(arr, m+1, r);
    merge(arr, l, m, r);
  }
}

void mergeSortParallel(int arr[], int l, int r) {
  if (l < r) {
    int m = l+(r-l)/2;

		if(r-l >= 256){
			#pragma omp taskgroup
			{
				#pragma omp task shared(arr)
				{
					mergeSortParallel(arr, l, m);
				}
				#pragma omp task shared(arr)
				{
					mergeSortParallel(arr, m+1, r);
				}
				#pragma omp taskwait
		    merge(arr, l, m, r);
			}
		} else{
				mergeSortParallel(arr, l, m);
				mergeSortParallel(arr, m+1, r);
				merge(arr, l, m, r);
		}
  }
}

int checkSorting(int32_t* array, int size) {
	int32_t tmp = array[0];
	for(int i = 1; i < size; i++){
		if(tmp > array[i])
			return 0;
		tmp = array[i];
	}
	return 1;
}

int main(int argc, char const **argv) {
  if (argc != 2) {
    fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
    return EXIT_FAILURE;
  }
  errno = 0;
	const char *str = argv[1];
	char *endptr;
	long n = strtol(str, &endptr, 0);
	if (errno != 0) {
		perror("strtol");
		return EXIT_FAILURE;
	}
	if (endptr == str) {
		fprintf(stderr, "Error: no digits were found!\n");
		return EXIT_FAILURE;
	}
	if (n < 0) {
		fprintf(stderr, "Error: array size must not be negative!\n");
		return EXIT_FAILURE;
	}

  int32_t *arraySequential = malloc(n * sizeof(int32_t));
	int32_t *arrayParallel = malloc(n * sizeof(int32_t));

	srand(1000);
	for(int i = 0; i < n; i++){
		arraySequential[i] = (int32_t) rand()%10;
		arrayParallel[i] = (int32_t) rand()%10;
	}

	double start = omp_get_wtime();
	mergeSortSequential(arraySequential, 0, n-1);
	double end = omp_get_wtime();
	printf("Sequential took %f\n", end-start);

	if(checkSorting(arraySequential, n)){
		printf("array (Sequential) sorted correctly\n");
	}

	start = omp_get_wtime();
	#pragma omp parallel
	#pragma omp single
	mergeSortParallel(arrayParallel, 0, n-1);
	end = omp_get_wtime();
	printf("Parallel took %f\n", end-start);

	if(checkSorting(arrayParallel, n)){
		printf("array (Parallel) sorted correctly\n");
	}

	free(arraySequential);
	free(arrayParallel);
  return EXIT_SUCCESS;
}
