#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#define MAX_V 13
#define OUT stdout

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
int g[MAX_V][MAX_V];
vector<Entry> table;

void mst(int s) {
  vector<Entry>::iterator it;

  for (int i = 1; i < MAX_V; i++) {
    if (g[s][i] != 0) { 
      if ((it = find(table.begin(), table.end(), Entry(i, g[s][i], false))) == table.end()) {
        table.push_back(Entry(i, g[s][i], false));   
      } else {
        if (g[s][i] < it->dis) {
          it->dis = g[s][i];
        }
      }
    }
  }

  int tmp = INT_MAX;
  int tmp_idx = -1;

  for (int i = 0; i < table.size(); i++) {
    if (table[i].intree == false && table[i].dis < tmp) {
      tmp = table[i].dis;
      tmp_idx = i; 
    }
  }

  if (tmp_idx != -1) {
    printf("pick up %d\n", table[tmp_idx].idx);
    printf("dis %d\n", tmp);
    getchar();
    table[tmp_idx].intree = true;
    mst(table[tmp_idx].idx);
  }

  return;
}

int main () {
  int s, e, w;

  for (int i = 0; i < MAX_V; i++)
    for (int j = 0; j < MAX_V; j++)
      g[i][j] = 0;

  FILE *fin = fopen("mst.in", "r");
  FILE *fout = fopen("mst.out", "w");

  fscanf(fin, "%d", &N); 
  for (int i = 0; i < N; i++) {
    fscanf(fin, "%d %d %d", &s, &e, &w);
    g[s][e] = w;
    g[e][s] = w;
  }

  table.push_back(Entry(1, 0, true));
  mst(1);

  fclose(fin);
  fclose(fout);
}
