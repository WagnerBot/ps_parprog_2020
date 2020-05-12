// Peter Koll, Jonas Wagner
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <stdint.h>

void sequentialPrefixSum(int32_t *a, int32_t *b, int N){
    double start = omp_get_wtime();
    b[0] = 0;
    for(int i = 1; i < N; i++)
        b[i] = b[i - 1] + a[i - 1];
    double end = omp_get_wtime();
    printf("Sequential: Size n = %d, Time = %f, Sum = %d\n", N, end-start, b[N-1]);
}

//Inspiration: https://de.wikipedia.org/wiki/Pr%C3%A4fixsumme#Parallele_Berechnung
void parallelPrefixSum(int32_t *a, int32_t *b, int N, int numThreads){
    int mid = N % 2 == 0 ? N/2 : (N/2 + 1);
    int32_t *x = malloc(sizeof(int32_t) * mid);
    int32_t *y = calloc(sizeof(int32_t), mid);

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(numThreads)
    for(int i = 1; i < N; i+=2)
        x[i/2] = a[i - 1] + a[i];

    for(int i = 1; i < mid; i++)
        y[i] = y[i - 1] + x[i - 1];

    #pragma omp parallel for num_threads(numThreads)
    for(int i = 1; i < N; i++)
        b[i] = i % 2 == 0 ? y[i/2] : (a[i - 1] + y[i/2]);
    
    double end = omp_get_wtime();

    free(x);
    free(y);

    printf("Parallel: Size n = %d, Time = %f, Sum = %d, numThreads = %d\n", N, end-start, b[N-1], numThreads);
}


int main(int argc, char **argv){
    if(argc != 4){
        printf("./ex1 <N> <0=sequential/1=parallel> <numThreads>\n");
        return EXIT_FAILURE;
    }
    int N = atoi(argv[1]);
    int mode = atoi(argv[2]);
    int numThreads = atoi(argv[3]);

    int32_t *a = malloc(sizeof(int32_t) * N);
    int32_t *b = calloc(sizeof(int32_t), N);

    for(int i = 0; i < N; i++)
        a[i] = 1;

    if(mode == 0)
        sequentialPrefixSum(a, b, N);

    else if(mode == 1)
        parallelPrefixSum(a, b, N, numThreads);

    free(a);
    free(b);
    
    return EXIT_SUCCESS;
}