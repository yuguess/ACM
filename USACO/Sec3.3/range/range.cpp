/*
ID: yuguess1
TASK: range 
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <limits.h>
#include <list>
using namespace std;

#define OUT fout
#define IN fin
#define MAX 250

int N;
int mat[MAX][MAX];
int hsum[MAX][MAX];
int wsum[MAX][MAX];

set<pair<int, int> > rs;

bool test_h(int x, int yl, int yh) {
  int n = hsum[yh][x] - hsum[yl][x] + mat[yl][x];
  return n == (yh - yl + 1);
}

bool test_w(int y, int xl, int xh) {
  int n = wsum[y][xh] - wsum[y][xl] + mat[y][xl];
  return n == (xh - xl + 1);
}

void f(list<pair<int, int> > &t, int l) {
  if (l > N) {
    return;
  }

  int lsize = 0;

  for (list<pair<int, int> >::iterator it = t.begin(); it != t.end();) {
    if (mat[it->second][it->first] == 1 
        && test_h(it->first + l - 1, it->second, it->second + l - 1) 
        && test_w(it->second + l - 1, it->first, it->first + l - 1)) {
      lsize++;
      it++;
    } else {
      it = t.erase(it);
    }
  }

  
  if (lsize != 0) {
    rs.insert(pair<int, int>(l, lsize));
    f(t, l + 1);
  }
}

int main() {
  FILE *fin = fopen("range.in", "r");
  FILE *fout = fopen("range.out", "w");
  
  fscanf(IN, "%d", &N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      fscanf(IN, "%1d", &(mat[i][j])); 
      hsum[i][j] = mat[i][j];
      wsum[i][j] = mat[i][j];
    }
  }

  for (int i = 1; i < N; i++)
    for (int j = 0; j < N; j++) {
      hsum[i][j] += hsum[i - 1][j];
      wsum[j][i] += wsum[j][i - 1];
    }

  list<pair<int, int> > t;
  for (int i = 0; i < N - 1; i++)
    for (int j = 0; j < N - 1; j++)
      t.push_back(pair<int, int>(j, i));

  f(t, 2);

  for (set<pair<int, int> >::iterator it = rs.begin(); it != rs.end(); it++)
    fprintf(OUT, "%d %d\n", it->first, it->second);

  fclose(fin);
  fclose(fout);
}
