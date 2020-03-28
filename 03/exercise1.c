//Peter Koll, Jonas Wagner
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void) {
  int num_threads, id, i;

  #pragma omp parallel private(num_threads, id, i) num_threads(4)
  {
    num_threads = omp_get_num_threads();
    id = omp_get_thread_num();

    //a)
    //printf("Hello World from thread %d\n", id);

    //b)
      for(i = 0; i < num_threads; i++){
        if(i == id)
          printf("Hello World from thread %d\n", omp_get_thread_num());
        //synchronizing threads and waiting for all threads to finish
        #pragma omp barrier
      }

    //c)
    #pragma omp single
      printf("Number of threads: %d\n", num_threads);
  }
  return 0;
}

/*
 * b) the output is not predictable and changes with every execution. we can fix this behaviour by a for-loop which controlls the execution of each thread one by one.
 * d) for every nested region we can define a new number of threads, which will execute the given task. this leads to a parallel region within another parallel region (number of threads ^ (level of the nested region)).
 */
