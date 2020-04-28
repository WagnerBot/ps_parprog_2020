// Peter Koll, Jonas Wagner
#include <omp.h>
#include <stdio.h>
//inspired by https://stackoverflow.com/questions/19687233/explict-flush-directive-with-openmp-when-is-it-necessary-and-when-is-it-helpful

int main() {
   int data, flag = 0;
   #pragma omp parallel num_threads(2)
   {
      if (omp_get_thread_num()==0) {
         /* Write to the data buffer that will be read by thread */
         data = 42;
         /* Flush data to thread 1 and strictly order the write to data
            relative to the write to the flag */
         #pragma omp flush(flag, data)
         /* Set flag to release thread 1 */
         flag = 1;
         /* Flush flag to ensure that thread 1 sees S-21 the change */
         #pragma omp flush(flag)
      }
      else if (omp_get_thread_num()==1) {
         /* Loop until we see the update to the flag */
         #pragma omp flush(flag, data)
         while (flag < 1) {
            #pragma omp flush(flag, data)
         }
         /* Values of flag and data are undefined */
         printf("flag=%d data=%d\n", flag, data);
         #pragma omp flush(flag, data)
         /* Values data will be 42, value of flag still undefined */
         printf("flag=%d data=%d\n", flag, data);
      }
   }
   return 0;
}

/*
 * shared memory of threads is not consistent and the original version
 * of flush deadlocks at a certain point. therefore you should edit the
 * code like above, this solves the problem.
 */
