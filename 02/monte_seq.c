#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define SEED 485614

int N = 50000000;

int main() {
  double x, y;
  int cnt = 0;
  double z, pi;

  srand(SEED);
  for(int i = 0; i < N; i++){
    x = (double) rand() / RAND_MAX;
    y = (double) rand() / RAND_MAX;
    z = x * x + y * y;
    if(z <= 1) cnt++;
  }

  pi = (double) cnt / N * 4;
  printf("%f\n", pi);
  return EXIT_SUCCESS;
}
