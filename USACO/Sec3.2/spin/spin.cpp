/*
ID: yuguess1
TASK: spin 
LANG: C++
*/
#include <stdio.h>
#include <string.h>
using namespace std;

#define MAX 5
#define OUT fout
#define IN fin

#define DE 360
#define THRE 100000

int sp[MAX];
int wn[MAX];
int wdb[MAX][MAX];
int wdlen[MAX][MAX];

int inter[DE];

int main() {
  FILE *fin = fopen("spin.in", "r");
  FILE *fout = fopen("spin.out", "w");

  for (int i = 0; i < MAX; i++) {
    fscanf(IN, "%d %d", &sp[i], &wn[i]);
    for (int j = 0; j < wn[i]; j++) {
      fscanf(IN, "%d %d", &(wdb[i][j]), &(wdlen[i][j]));
      wdlen[i][j]++;
    }
  }

  int t = 0;
  int num = 1;
  int inter_flag = 0;
  
  while (1) {
    for (int i = 0; i < wn[0]; i++) {
      for (int k = 0; k < wdlen[0][i]; k++)
        inter[((wdb[0][i] + k) % DE)] = 1;
    }

    for (int i = 1; i < MAX; i++) {
      for (int j = 0; j < wn[i]; j++) {
        for (int k = 0; k < wdlen[i][j]; k++) {
          if (inter[((wdb[i][j] + k) % DE)] == i) {
            inter[((wdb[i][j] + k) % DE)]++;
            inter_flag = 1;
          } 
        }
      }

      if (inter_flag != 1)
        break;
      else
        num++;
      
      inter_flag = 0;
    }
    if (num == MAX) {
      fprintf(OUT, "%d\n", t);
      return 0;
    } else {
      num = 1;
    }

    for (int i = 0; i < MAX; i++) {
      for (int k = 0; k < wn[i]; k++) {
        wdb[i][k] = (wdb[i][k] + sp[i]) % DE; 
      }
    }

    if (t > THRE) {
      fprintf(OUT, "none\n");
      return 0;
    }

    t++;
    memset(inter, 0, DE * sizeof(int));
  }
}
