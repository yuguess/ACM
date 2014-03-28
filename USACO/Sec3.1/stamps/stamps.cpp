/*
ID: yuguess1
TASK: stamps 
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

#define IN fin
#define OUT fout

#define MAX_N 50
#define MAX 2000001

int K, N;
int vs[MAX_N];
int idx[MAX_N] = {0};

int v[MAX] = {0};
short cn[MAX] = {0};

int main () {
  FILE *fin = fopen("stamps.in", "r");
  FILE *fout = fopen("stamps.out", "w");

  fscanf(IN, "%d %d", &K, &N);
  for (int i = 0; i < N; i++) {
    fscanf(IN, "%d", &(vs[i]));
  }

  int cnt = 0;
  int min_num = K;

  while (1) {
    for (int i = 0; i < N; i++) {
      while (v[idx[i]] + vs[i] <= v[cnt]) idx[i]++; 
      int tmp = v[idx[i]] + vs[i];
      int num = cn[idx[i]] + 1;
      if (tmp == (v[cnt] + 1)) { 
        v[cnt + 1] = tmp;
        if (num < min_num) {
          min_num = num;
        }
      }
    }

    if (v[cnt] + 1 != v[cnt + 1]) {
      break;
    }

    if (min_num > K) {
      break;
    } else {
      cn[cnt + 1] = min_num;
    }

    min_num = K + 1;
    cnt++;
  }

  fprintf(OUT, "%d\n", v[cnt]);

  fclose(fin);
  fclose(fout);
}
