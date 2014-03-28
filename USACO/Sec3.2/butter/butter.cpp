/*
ID: yuguess1
TASK: butter
LANG: C++
*/
#include <stdio.h>
#include <limits.h>
#include <set>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

#define OUT fout
#define IN fin
#define MAX_N 801
int N, P, C, dsrc;
int c[MAX_N] = {0};
int m[MAX_N][MAX_N];

set<pair<int, int> > hp;
vector< vector<pair<int,int> > > g;

void dijkstra(int s, int d) {
  set<pair<int, int> >::iterator sit;

  for (int i = 0; i < g[s].size(); i++) {

      if (m[dsrc][g[s][i].first] == -1) {
          m[dsrc][g[s][i].first] = d + g[s][i].second;
          hp.insert(pair<int, int>(d + g[s][i].second, g[s][i].first));
      } else {
        if ((d + g[s][i].second) < m[dsrc][g[s][i].first]) {
            hp.erase(pair<int, int>(m[dsrc][g[s][i].first], g[s][i].first));
            hp.insert(pair<int, int>(d + g[s][i].second, g[s][i].first));
            m[dsrc][g[s][i].first] = d + g[s][i].second;
        }
      }
  }
 
  if (hp.size() == 0) {
    return;
  }

  sit = hp.begin();
  int dis = sit->first;
  int k = sit->second;
  hp.erase(sit);

  dijkstra(k, dis);
}

void data_init() {
  for (int i = 0; i < MAX_N; i++)
    for (int j = 0; j < MAX_N; j++) {
      if (i == j) 
        m[i][j] = 0;
      else
        m[i][j] = -1;
    }
}

int main() {
  int src, des, len;

  data_init();

  FILE *fin = fopen("butter.in", "r");
  FILE *fout = fopen("butter.out", "w");

  fscanf(IN, "%d %d %d", &N, &P, &C);
  for (int i = 0; i < N; i++)
    fscanf(IN, "%d", &(c[i]));

  g.resize(P + 1);

  for (int j = 0; j < C; j++) {
    fscanf(IN, "%d %d %d", &src, &des, &len);
    g[src].push_back(pair<int, int>(des, len));
    g[des].push_back(pair<int, int>(src, len));
    //m[src][des] = len; 
    //m[des][src] = len;
  }

  long long min_v = INT_MAX;
  int place = 0;
  for (int i = 1; i <= P; i++) {
    hp.insert(pair<int, int>(0, i));
    dsrc = i;
    dijkstra(i, 0);
    /*
    for (int j = 0; j <= P; j++) {
        printf("%d => %d\n", j, m[dsrc][j]);
    }
    getchar();
    */
    long long sum = 0;
    for (int j = 0; j < N; j++) {
      if (c[j] != i)
        sum += m[i][c[j]];  
    }

    if (sum != 0)
      min_v = min(sum, min_v); 
  }

  fprintf(OUT, "%d\n", min_v);
  
  fclose(fin);
  fclose(fout);
}
