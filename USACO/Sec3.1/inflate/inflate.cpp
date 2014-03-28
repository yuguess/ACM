/*
ID: yuguess1
TASK: inflate 
LANG: C++
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

#define OUT fout
#define MAX_M 10001

int M, N;
vector<int> ps;
vector<int> ts;
int table[MAX_M];

int max_v(int c) {
  int p = 0;
  int tmp_max = 0;

  if (c <= 0)
    return 0;

  if (table[c] != -1)
    return table[c];

  for (int i = 0; i < N; i++) {
    if (c - ts[i] >= 0)
      p = max_v(c - ts[i]) + ps[i];

    if (p > tmp_max) 
      tmp_max = p;
  }

  table[c] = max(table[c], tmp_max); 
  return  table[c];
}

int main () {
  int p, t;

  for (int i = 0; i < MAX_M; i++)
    table[i] = -1;

  FILE *fin = fopen("inflate.in", "r");
  FILE *fout = fopen("inflate.out", "w");

  fscanf(fin, "%d", &M);
  fscanf(fin, "%d", &N);
  for (int i = 0; i < N; i++) {
    fscanf(fin, "%d %d", &p, &t);
    ps.push_back(p);
    ts.push_back(t);
  }

  fprintf(OUT, "%d\n", max_v(M));

  fclose(fin);
  fclose(fout);
}
