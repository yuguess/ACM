/*
ID: yuguess1
TASK: game1 
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <map>
#include <limits.h>
#include <algorithm>
using namespace std;

#define OUT fout
#define IN fin
#define MAX 100
#define P 2

int N = 0;
vector<int> v;

pair<int, int> tb[P][MAX][MAX];

void game(int b, int e, int &A, int &B, int turn) {
  int Al = 0, Ar = 0;
  int Bl = 0, Br = 0;
  if (tb[turn][b][e].first != -1) {
    A = tb[turn][b][e].first;
    B = tb[turn][b][e].second;
    return;
  }

  if (b == e) {
    if (turn == 0) {
      A = v[b];
      B = 0;
    } else {
      A = 0;
      B = v[b];
    }
    tb[turn][b][e].first = A;
    tb[turn][b][e].second = B;
    return;
  }

  if (turn == 0) {
    game(b + 1, e, Al, Bl, 1);
    game(b, e - 1, Ar, Br, 1);

    if (v[b] + Al > v[e] + Ar) {
      A = v[b] + Al; 
      B = Bl;
    } else {
      A = v[e] + Ar; 
      B = Br;
    }
  } else {
    game(b + 1, e, Al, Bl, 0);
    game(b, e - 1, Ar, Br, 0); 

    if (v[b] + Bl > v[e] + Br) {
      A = Al; 
      B = v[b] + Bl;
    } else {
      A = Ar;
      B = v[e] + Br;
    }
  }

  tb[turn][b][e].first = A;
  tb[turn][b][e].second = B;
}

void data_init() {
  for (int i = 0; i < P; i++)
    for (int j = 0; j < MAX; j++)
      for (int k = 0; k < MAX; k++)
        tb[i][j][k].first = -1;
}

int main() {
  int tmp;
  FILE *fin = fopen("game1.in", "r");
  FILE *fout = fopen("game1.out", "w");

  data_init();

  fscanf(IN, "%d", &N);
  for (int i = 0; i < N; i++) {
    fscanf(IN, "%d", &tmp);
    v.push_back(tmp);
  }

  int A = 0;
  int B = 0;
  game(0, N - 1, A, B, 0);

  fprintf(OUT, "%d %d\n", A, B, 0);

  fclose(fin);
  fclose(fout);
}
