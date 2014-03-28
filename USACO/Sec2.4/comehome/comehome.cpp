/*
ID: yuguess1
TASK: comehome 
LANG: C++
*/
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

#define MAX_V 58
#define MAX_D 1001
#define OUT fout

class Entry {
public:
  Entry(int e, bool v, int d) : idx(e), is_visit(v), dis(d) {} 
  int idx; 
  bool is_visit;
  int dis;
};

int n;
int g[MAX_V][MAX_V];
vector<Entry> table;

void dijk(int s) {
  table[s].is_visit = true;

  for (int i = 0; i < MAX_V; i++) {
    if (g[s][i] != -1 && (table[s].dis + g[s][i] < table[i].dis)) {
      table[i].dis = table[s].dis + g[s][i];
    }
  }

  int min = INT_MAX;
  int next_idx = -1;

  for (int i = 0; i < MAX_V; i++) {
    if (table[i].is_visit == false && table[i].dis < min) {
      next_idx = i;    
      min = table[i].dis;
    }
  }
  
  if (min < INT_MAX) {
    dijk(next_idx);
  }

  return;
}

int main () {
  char c, src, des;
  int dis;

  for (int i = 0; i < MAX_V; i++)
    table.push_back(Entry(i, false, INT_MAX - MAX_D - 2));

  for (int i = 0; i < MAX_V; i++)
    for (int j = 0; j < MAX_V; j++) {
      g[i][j] = -1;
    }

  FILE *fin = fopen("comehome.in", "r");
  FILE *fout = fopen("comehome.out", "w");

  fscanf(fin, "%d", &n);
  //skip newline 
  fscanf(fin, "%c", &c);

  for (int i = 0; i < n; i++) {
    fscanf(fin, "%c %c %d%c", &src, &des, &dis, &c);
    if (src == des) 
      continue;

    int s_idx = src - 'A';
    int d_idx = des - 'A';
/*
      printf("i %d\n", i);
      printf("s_idx:%d\n", s_idx);
      printf("d_idx:%d\n", d_idx);
*/
    if (g[s_idx][d_idx] != -1) {
      g[s_idx][d_idx] = min(g[s_idx][d_idx], dis);
      g[d_idx][s_idx] = g[s_idx][d_idx];
    } else {
      g[s_idx][d_idx] = dis;
      g[d_idx][s_idx] = g[s_idx][d_idx];
    }
  }
/*
  for (int i = 0; i < MAX_V; i++) { 
    for (int j = 0; j < MAX_V; j++) {
      printf("%2d ", g[i][j]);
    }
    printf("\n");
  }
  */

  table['Z' - 'A'].dis = 0;
  dijk('Z' - 'A'); 
/*
  for (int i = 0; i < MAX_V; i++) {
    if (table[i].idx >= 0 && table[i].idx <= ('Y' - 'A')) {
      printf("%c dis %d\n", table[i].idx + 'A', table[i].dis);
    }
  }
*/

  
  int short_dis = INT_MAX;
  char name;

  for (int i = 0; i < MAX_V; i++) {
    if (table[i].idx >= 0 && table[i].idx <= ('Y' - 'A') 
          && table[i].dis < short_dis) { 
      short_dis = table[i].dis;
      name = table[i].idx + 'A';
    }
  }

  fprintf(OUT, "%c %d\n", name, short_dis);

  fclose(fin);
  fclose(fout);
}
