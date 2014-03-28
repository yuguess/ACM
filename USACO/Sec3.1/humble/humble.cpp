/*
ID: yuguess1
TASK: humble 
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <limits.h>
using namespace std;

#define MAX 100001
#define MAX_P 100

#define IN fin
#define OUT fout

int n[MAX];
int p[MAX_P];
int idx[MAX_P] = {0};
int K, N;

int main() {
  FILE *fin = fopen("humble.in", "r");
  FILE *fout = fopen("humble.out", "w");

  fscanf(IN, "%d %d", &K, &N);
  for (int i = 0; i < K; i++) {
    fscanf(IN, "%d", &(p[i]));
  }

  n[0] = 1;
  int cnt = 0;
  int cnt_i = 0;

  int min = INT_MAX;

  while (cnt != N) {
    for (int i = 0; i < K; i++) {
      //printf("i %d, idx %d\n", i, idx[i]);
      while (n[idx[i]] * p[i] <= n[cnt]) {
        idx[i]++;
      }
      int v = n[idx[i]] * p[i];
      if (v < min) {
          min = v;  
          cnt_i = i;
          n[cnt + 1] = min;
      }
    }
    cnt++;
    idx[cnt_i]++;
    min = INT_MAX;
    //printf("%d\n", n[cnt]);
    //getchar();
  }

  fprintf(OUT, "%d\n", n[cnt]);

  fclose(fin);
  fclose(fout);
}
