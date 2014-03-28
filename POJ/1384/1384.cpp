#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

#define OUT fout
#define IN stdin
#define MAX 510
#define MAX_WEIGHT 10001

int v[MAX];
int c[MAX];
int f[MAX_WEIGHT];

const int INF = 0x0fffffff;

int main() {
  int N = 0;
  int p = 0, pt = 0, w = 0, n = 0;

  FILE *fin = fopen("1384.in", "r");

  fscanf(IN, "%d", &N);
  for (int i = 0; i < N; i++) {
    fscanf(IN, "%d %d", &p, &pt);  
    w = pt - p;
    fscanf(IN, "%d", &n);
    for (int j = 0; j < n; j++) {
      fscanf(IN, "%d %d", &v[j], &c[j]);
    }

    f[0] = 0; 
    for (int j = 1; j < MAX_WEIGHT; j++)
      f[j] = INF;

    for (int j = 0; j < n; j++)
      for (int k = c[j]; k <= w; k++) {
        f[k] = min(f[k], f[k - c[j]] + v[j]); 
      }

    if (f[w] != INF) {
      printf("The minimum amount of money in the piggy-bank is %d.\n", f[w]);
    } else {
      printf("This is impossible.\n");
    }

    memset(f, 0, sizeof(int) * MAX_WEIGHT);
  }
}
