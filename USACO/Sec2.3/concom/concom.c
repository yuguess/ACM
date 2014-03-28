/*
ID: yuguess1
LANG: C
TASK: concom 
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX 101
#define OUTPUT fout

int data[MAX][MAX];
int is_transfer[MAX][MAX];

void flood_to_parent(int owner, int ownee, int perc) {
  int i;

  for (i = 0; i < MAX; i++) {
    if (i == owner)
      continue;

    if (data[i][owner] > 50) {  
      data[i][ownee] += perc;
    }
  }
}

void transfer_flood(int from, int to) {
  int i, j;

  if (is_transfer[from][to] != 0) {
    return;  
  }

  is_transfer[from][to] = 1;

  for (i = 0; i < MAX; i++) {
    if (i == to)
      continue;

    int old = data[to][i];
    data[to][i] += data[from][i];
    if (old < 50 && data[to][i] > 50) {
#ifdef DEBUG
      printf("generate new transfer from %d to %d\n", i, to);
#endif
      transfer_flood(i, to);
    }
  }

  for (i = 0; i < MAX; i++) {
    if (i == to) {
      continue;
    }

    if (data[i][to] > 50) {
#ifdef DEBUG
      printf("transfer %d to %d's parent %d\n", from, to, i);
#endif
      transfer_flood(from, i);
    }
  }
}

int main () {
  int N;
  int i, owner, ownee, perc, j;

  FILE *fin = fopen("concom.in", "r");
  FILE *fout = fopen("concom.out", "w");

  for (i = 0; i < MAX; i++)
    for (j = 0; j < MAX; j++)
      data[i][j] = 0;

  for (i = 0; i < MAX; i++) {
    for (j = 0; j < MAX; j++) {
      if (i == j) { 
        is_transfer[i][j] = 1;
      } else {
        is_transfer[i][j] = 0;
      }
    }
  }

  fscanf(fin, "%d", &N);

  for (i = 0; i < N; i++) {
    fscanf(fin, "%d %d %d", &owner, &ownee, &perc);

    data[owner][ownee] += perc;
    flood_to_parent(owner, ownee, perc);

    if (data[owner][ownee] > 50) {
#ifdef DEBUG
      printf("begin transfer %d to %d's parents\n", ownee, owner);
#endif
      transfer_flood(ownee, owner);
    }
  }

  for (i = 0; i < MAX; i++)
    for (j = 0; j < MAX; j++) {
      if (i == j)
        continue;

      if (data[i][j] > 50) {
        fprintf(OUTPUT, "%d %d\n", i, j); 
      }
    }

  fclose(fin);
  fclose(fout);
}
