/*
ID: yuguess1
TASK: agrinet 
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

#define OUT fout
#define MAX_V 100

class Entry {
public:
  Entry(int i, int d, bool in):idx(i), dis(d), intree(in) {}
  int idx;
  int dis;
  bool intree;
  bool operator == (const Entry &e) {
    return (this->idx == e.idx);
  }
};

int N;
int cost = 0;
int g[MAX_V][MAX_V];
vector<Entry> table;

void mst(int s) {
  for (int i = 0; i < N; i++) {
    if (g[s][i] != 0) {
      table[i].dis = min(table[i].dis, g[s][i]);
    }
  }

  int tmp = INT_MAX;
  int next = -1;

  for (int i = 0; i < table.size(); i++) {
    if (table[i].intree == false && table[i].dis < tmp) {
      tmp = table[i].dis;
      next = i;
    }
  }

  if (next != -1) {
    table[next].intree = true;
    cost += table[next].dis;
    mst(next);
  }

  return;
}

int main () {

  FILE *fin = fopen("agrinet.in", "r");
  FILE *fout = fopen("agrinet.out", "w");

  fscanf(fin, "%d", &N);

  for (int i = 0; i < N; i++)
    table.push_back(Entry(i, INT_MAX, false));

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
      fscanf(fin, "%d", &(g[i][j]));
    }

  table[0].dis = 0;
  table[0].intree = true;
  mst(0);

  fprintf(OUT, "%d\n", cost);

  fclose(fin);
  fclose(fout);
}
