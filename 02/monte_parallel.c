#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <sys/stat.h>

#define SEED 485614

int threads = 8;
int N = 50000000;

void* thr_start();

struct thr_info{
  pthread_t id;
  int thr_num;
  int num_calc;
  int* counter;
};

struct thr_info* create(int number_thr, int* cnt, int n){
  max_thr = number_thr;
  int calc_per_thr = n / number_thr;

  struct thr_info* info;

  for(int i = 0; i < number_thr; i++){
    info[i].thr_num = i;
    info[i].num_calc = calc_per_thr;
    info[i].counter = cnt;
  }
  return info;
}

void thr_wait(struct thr_info* info){
  for(int i = 0; i < threads; i++)
    pthread_join(info[i].id, NULL);
}



void *aprox_pi(void *ptr){
  double x, y;
  int cnt = 0;
  double z, pi;

  srand(SEED);
  for(int i = 0; i < N; i++){
    x = (double) rand_r(SEED) / RAND_MAX;
    y = (double) rand_r(SEED) / RAND_MAX;
    z = x * x + y * y;
    if(z <= 1) cnt++;
  }
  pi = (double) cnt / N * 4;
}

int main() {
  int cnt = 0;
  double pi;
  struct thr_info *info;
  srand(SEED);


  return EXIT_SUCCESS;
}
