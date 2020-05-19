# Exercise 3 (Peter Koll, Jonas Wagner)

1. Tell the compiler with "restricted" that the pointer are not overlapping. Parallization can be simply with a omp parallel for.

    ```c
    void copy(double* restricted x, double* restricted y) {
        #pragma omp parallel for
        for(int i = 0; i < 1024; i++) {
            x[i] = y[i];
        }
    }
    ``` 

2. Normalization can be done by incrementing i by 1 and change the for loop accordingly.
  
    ```c
    for (int i=4; i<=N/7; i++) {
            A[i*7] = 0;
    }
    ```

3. "Loop-carried dependence" and within the for-loops "True dependence".

    Distance Vector: (1, 0, -1)
    Direction Vector: (<,=,>)

    ```c
    for(int i = 1; i < N; i++) {
        for(int j = 1; j < M; j++) {
            for(int k = 1; k < L; k++) {
                a[i+1][j][k-1] = a[i][j][k] + 5;
            }
        }
    }
    ```
