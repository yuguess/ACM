#include <stdio.h>
#include <vector>
#include <stack>
#include <map>
using namespace std;

#define MAX 8

#define IN fin
#define OUT fout

stack<int> cir;
vector<map<int, int > > g;
int N;

void euler_tour(int s) {
  while (g[s].size() != 0) {
    int next = g[s].begin()->first;
    g[s].erase(next);
    g[next].erase(s);
    printf("next %d\n", next);
    getchar();
    euler_tour(next);
  }

  cir.push(s);
}

int main() {
  int src, des;
  FILE *fin = fopen("euler.in", "r");
  FILE *fout = fopen("euler.out", "w");

  fscanf(IN, "%d", &N);

  g.resize(N);
  
  for (int i = 0; i < N; i++) {
    fscanf(IN, "%d %d", &src, &des);
    g[src][des] = 1;
    g[des][src] = 1;
  }

  euler_tour(1);

  while (cir.size() != 0) {
    printf("%d ", cir.top());
    cir.pop();
  }

  fclose(fin);
  fclose(fout);
}
