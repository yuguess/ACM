/*
ID: yuguess1
TASK: rect1 
LANG: C++
*/
#include <stdio.h>
#include <vector>

using namespace std;

#define OUT fout
#define IN fin

#define MAX_C 2500
#define MAX_O 1000

int lxs[MAX_O];
int lys[MAX_O];
int uxs[MAX_O];
int uys[MAX_O];
int c[MAX_O];

int cs[MAX_C] = {0};
int A, B, N;
int df;

void float_up(int lv, int lx, int ly, int ux, int uy, int c) {
  if (lv == N) {
    int area = (ux - lx) * (uy - ly);
    df -= area;
    cs[c] += area;
    return;
  }

  if (lx >= uxs[lv] || ux <= lxs[lv] || ly >= uys[lv] || uy <= lys[lv]) {
    float_up(lv + 1, lx, ly, ux, uy, c);
  } else {
    if (lxs[lv] > lx && lxs[lv] < ux) {
      float_up(lv + 1, lx, ly, lxs[lv], uy, c); 
      lx = lxs[lv];
    }
    if (uxs[lv] > lx && uxs[lv] < ux) {
      float_up(lv + 1, uxs[lv], ly, ux, uy, c);
      ux = uxs[lv];
    }
    if (lys[lv] > ly && lys[lv] < uy) {
      float_up(lv + 1, lx, ly, ux, lys[lv], c);
      ly = lys[lv];
    }
    if (uys[lv] > ly && uys[lv] < uy) {
      float_up(lv + 1, lx, uys[lv], ux, uy, c);
    }
    
  }
}

int main() {
  int lx, ly, ux, uy;

  FILE *fin = fopen("rect1.in", "r");
  FILE *fout = fopen("rect1.out", "w");

  fscanf(IN, "%d %d %d", &A, &B, &N);

  df = A * B;

  for (int i = 0; i < N; i++) {
    fscanf(IN, "%d %d %d %d %d", &(lxs[i]), &(lys[i]), &(uxs[i]), &(uys[i]), &(c[i]));
  }

  for (int i = N - 1; i >= 0; i--) {
    float_up(i + 1, lxs[i], lys[i], uxs[i], uys[i], c[i]);
  }

  cs[1] += df; 

  for (int i = 0; i < MAX_C; i++) {


    if (cs[i] != 0) {
      fprintf(OUT, "%d %d\n", i, cs[i]);
    }
  }

  fclose(fin);
  fclose(fout);
}
