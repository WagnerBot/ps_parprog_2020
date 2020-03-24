#include <stdio.h>
#include <stdlib.h>

int n = 100;

int main(){
  int a[n][n];
  int b[n][n];
  int c[n][n];

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      a[i][j] = rand();
      b[i][j] = rand();
    }
  }

  for (size_t j = 0; j < n; ++j) {
    for (size_t i = 0; i < n; ++i) {
        c[i][j] = a[i][j] * b[i][j];
    }
  }
  return 1;
}
