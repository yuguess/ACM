/*
ID: yuguess1
TASK: kimbits 
LANG: C++
*/
#include <stdio.h>

using namespace std;

#define OUT fout
#define IN fin

#define MAX 32

unsigned t[MAX][MAX] = {-1};

unsigned table(unsigned N, unsigned L) {
  if (t[N][L] != -1) {
    return t[N][L];
  } else {
    
    t[N][L] = table(N - 1, L) + table(N - 1, L - 1);
    //prunsignedf("N %d, L %d, %d\n", N, L, t[N][L]);
    return t[N][L];
  }
}

unsigned acc(unsigned N, unsigned L) {
  unsigned sum = 0;

  for (unsigned i = 0; i <= L; i++) {
    //prunsignedf("table N %d, i %d, %d\n", N, i, table(N, i));  
    sum += table(N, i);
  }

  return sum;
}

void f(FILE *fout, unsigned N, unsigned i, unsigned L) {
  if (N == 1) {
    if (i == 1) {
      fprintf(OUT, "0\n"); 
    } else {
      fprintf(OUT, "1\n");
    }
    return;
  }

  //printf("(N - 1) %d, L %d, i %d\n", N - 1, L, i);
  //printf("accmulate %d\n", acc(N - 1, L));
  if (i <= acc(N - 1, L)) {
    fprintf(OUT, "0");
    f(fout, N - 1, i, L);
  } else {
    fprintf(OUT, "1");
    f(fout, N - 1, i - acc(N - 1, L), L - 1);
  }
}

int main() {
  unsigned N, L, I;

  for (unsigned i = 0; i < MAX; i++)
    for (unsigned j = 0; j < MAX; j++)
      t[i][j] = -1;
  for (unsigned i = 0; i < MAX; i++)
    t[1][i] = 0;

  FILE *fin = fopen("kimbits.in", "r");
  FILE *fout = fopen("kimbits.out", "w");

  fscanf(IN, "%u %u %u", &N, &L, &I);

  t[1][0] = 1;
  t[1][1] = 1;
  //prunsignedf("%d\n", acc(2, 1));
  f(fout, N, I, L);
}
