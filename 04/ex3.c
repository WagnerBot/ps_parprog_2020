// Peter Koll, Jonas Wagner
// Inspiration: https://www.geeksforgeeks.org/iterative-merge-sort/
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
    int L[n1], R[n2];

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
}

void mergeSortSequential(int arr[], int n) {
   int curr_size;
   int left_start;
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size) {
       for (left_start=0; left_start<n-1; left_start += 2*curr_size) {
           int mid = min(left_start + curr_size - 1, n-1);
           int right_end = min(left_start + 2*curr_size - 1, n-1);
           merge(arr, left_start, mid, right_end);
       }
   }
}

void mergeSortParallel(int arr[], int n) {
   int curr_size;
   int left_start;
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size) {
			 #pragma omp for
       for (left_start=0; left_start<n-1; left_start += 2*curr_size) {
           int mid = min(left_start + curr_size - 1, n-1);
           int right_end = min(left_start + 2*curr_size - 1, n-1);
           merge(arr, left_start, mid, right_end);
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
	mergeSortSequential(arraySequential, n);
	double end = omp_get_wtime();
	printf("Sequential took %f\n", end-start);

	if(checkSorting(arraySequential, n)){
		printf("array (Sequential) sorted correctly\n");
	}

	start = omp_get_wtime();
	mergeSortParallel(arrayParallel, n);
	end = omp_get_wtime();
	printf("Parallel took %f\n", end-start);

	if(checkSorting(arrayParallel, n)){
		printf("array (Parallel) sorted correctly\n");
	}

	free(arraySequential);
	free(arrayParallel);
  return EXIT_SUCCESS;
}
