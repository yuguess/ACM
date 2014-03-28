/*
ID: yuguess1
TASK: ratios 
LANG: C++
*/
#include <stdio.h>
#include <limits.h>

using namespace std;

#define MAX 3
#define OUT fout
#define IN fin

int min = INT_MAX;
int g[MAX];
int m[MAX][MAX];
int r[MAX];


int ratio(int gm1, int gm2, int gm3, int idx, int m1, int m2, int m3) {
  if (gm1 < 0 || gm2 < 0 || gm3 < 0 || idx >= 3)
    return -1;

  if (gm1 == 0 && gm2 == 0 && gm3 == 0) {
    if (m1 + m2 + m3 < min) {
      min = m1 + m2 + m3;
      r[0] = m1;
      r[1] = m2;
      r[2] = m3;
    }
    return 0;
  }

  int tmp1 = ratio(gm1, gm2, gm3, idx + 1, m1, m2, m3);

  switch (idx) {
  case 0:
    m1++;
    break;
  case 1:
    m2++; 
    break;
  case 2:
    m3++;
    break;
  }

  int tmp2 = ratio(gm1 - m[idx][0], gm2 - m[idx][1], gm3 - m[idx][2], idx, m1, m2, m3);

  if (tmp1 == -1 && tmp2 == -1)
    return -1;
  else
    return 0;
}

int main() {
  FILE *fin = fopen("ratios.in", "r");
  FILE *fout = fopen("ratios.out", "w");
  for (int i = 0; i < MAX; i++) {
    fscanf(IN, "%d", &(g[i])); 
  }

  for (int i = 0; i < MAX; i++) {
    fscanf(IN, "%d %d %d", &(m[i][0]), &(m[i][1]), &(m[i][2]));
  }

  int min = INT_MAX;

  for (int i = 1; i <= 100; i++) {
    if (ratio(g[0] * i, g[1] * i, g[2] * i, 0, 0, 0, 0) != -1) {
      int ra = (r[0] * m[0][0] + r[1] * m[1][0] + r[2] * m[2][0]) / g[0];
      fprintf(OUT, "%d %d %d %d\n", r[0], r[1], r[2], ra);
      return 0;
    }
  }

  fprintf(OUT, "NONE\n");

  fclose(fin);
  fclose(fout);
}
