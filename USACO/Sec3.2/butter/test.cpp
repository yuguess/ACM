#include <stdio.h>
#include <limits.h>
#include <set>
#include <map>
using namespace std;

#define MAX_N 801
#define OUT stdout
#define IN fin

int P;
int g[MAX_N][MAX_N];
set<pair<int, int> > hp;
map<int, int> m;

void dijkstra(int s, int d) {
  map<int, int>::iterator it;
  set<pair<int, int> >::iterator sit;
  if (hp.size() == 0) {
    return;
  }

  for (int i = 1; i <= P; i++) {
    if (g[s][i] != -1 && s != i) {
      if ((it = m.find(i)) == m.end()) {
        m[i] = d + g[s][i];
        printf("before insert i %d, %d to %d:%d, d :%d\n", i, s, i, g[s][i], d);
        hp.insert(pair<int, int>(d + g[s][i], i));
      } else {
        if ((d + g[s][i]) < (it->second)) {
          printf("update %d, replace %d with %d\n", i,it->second,d + g[s][i]);   
          hp.erase(pair<int, int>(it->second, i));
          hp.insert(pair<int, int>(d + g[s][i], i));
          m[i] = d + g[s][i];
        }
      }
    }
  }

  printf("hp size %d\n", hp.size());
  for (sit = hp.begin(); sit != hp.end(); sit++)
    printf("%d => %d\n", sit->first, sit->second);

  sit = hp.begin();
  int dis = sit->first;
  int k = sit->second;

  printf("next %d => dis %d, d %d\n", k, dis, d); 
  getchar();

  hp.erase(sit);

  dijkstra(k, dis);
}

void data_init() {
  for (int i = 0; i < MAX_N; i++)
    for (int j = 0; j < MAX_N; j++) {
      if (i == j) {
        g[i][j] = 0;
      } else {
        g[i][j] = -1;
      }
    }
}

int main() {
  int src, des, len;
  FILE *fin = fopen("test.in", "r");
  data_init();
  fscanf(IN, "%d", &P);
  for (int i = 1; i <= P; i++) {
    fscanf(IN, "%d %d %d", &src, &des, &len);
    g[src][des] = len;
    g[des][src] = len;
  }

  map<int, int>::iterator it;

  for (int i = 1; i <= P; i++) {
    hp.insert(pair<int, int>(0, i));
    m[i] = 0;
    dijkstra(i, 0);
     
    for (it = m.begin(); it != m.end(); it++)
      printf("%d => %d\n", it->first, it->second);
    getchar();
  }
}
