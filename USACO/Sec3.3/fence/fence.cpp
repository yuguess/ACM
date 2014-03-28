/*
ID: yuguess1
TASK: fence 
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <map>
#include <limits.h>
using namespace std;

#define OUT fout
#define IN fin
#define MAX 501

int N;
vector<int> cir;
vector<map<int, int > > g;
map<int, int> m;

void incre(map<int, int> &mm, int k) {
  if (mm.find(k) == m.end()) {
    mm[k] = 1;
  } else {
    mm[k]++;
  }
}

void decre(map<int, int> &mm, int k) {
  mm[k]--;
  if (mm[k] == 0)
    mm.erase(k);
}

void euler_tour(int s) {
  while (g[s].size() != 0) {
    int next = g[s].begin()->first;
    decre(g[s], next);
    decre(g[next], s);
    euler_tour(next);
  }

  cir.push_back(s);
}

int main() {
  int src, des;
  int odd_st = INT_MAX;
  int min_st = INT_MAX;

  g.resize(MAX);

  FILE *fin = fopen("fence.in", "r");
  FILE *fout = fopen("fence.out", "w");

  fscanf(IN, "%d", &N);
  for (int i = 0; i < N; i++) {
    fscanf(IN, "%d %d", &src, &des); 
    
    incre(g[src], des);
    incre(g[des], src);
    
    incre(m, src);
    incre(m, des); 
  }

  for (map<int, int>::iterator it = m.begin(); it != m.end(); ++it) {
    if (it->second % 2 == 1 && it->first < odd_st) {
      odd_st = it->first;
    }

    if (it->second % 2 == 0 && it->first < min_st) {
      min_st = it->first;
    }
  }

  if (odd_st != INT_MAX)
    euler_tour(odd_st);
  else
    euler_tour(min_st);

  while (cir.size() != 0) {
    fprintf(OUT, "%d\n", cir.back());
    cir.pop_back();
  }

  fclose(fin);
  fclose(fout);
}
