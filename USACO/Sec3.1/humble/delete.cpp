#include <stdio.h>
#include <math.h>

int main () {
  int k = 6;

  for (int i = 1; i < 7; i++)
    printf("i %d, %d\n", i, k * ((int)pow(k, i) - 1) / (k - 1));
}
