#include <stdio.h> 
#include <vector>
#include <limits.h>
using namespace std;

struct entry{
  int start; 
  int end;
  int weight;
}; 

struct node {
  int num;
  int dis;
  int is_visit;
  int parent;
};

vector<entry> graph;
vector<node> verts;

void dis(int s, int d) {
  int i;
  if (s == d) {
    return;
  }

  verts[s].is_visit = 1;

  for (i = 0; i < graph.size(); i++) {
    if (graph[i].start == s) {
      if ((verts[s].dis + graph[i].weight) < verts[graph[i].end].dis) {
        verts[graph[i].end].dis = (verts[s].dis + graph[i].weight);
        verts[graph[i].end].parent = s;
      }
    }
  }

  int min_dis = INT_MAX;
  int next = 0;

  for (i = 0; i < verts.size(); i++) {
    if (verts[i].is_visit == 0 && verts[i].dis < min_dis) {
      min_dis = verts[i].dis;
      next = i;
    }
  }

  dis(next, d);
  return;
}

void print_route(int end, int start) {
  if (end == start) {
    printf("%d \n", end);
    return;
  }
  printf("%d ", end);
  print_route(verts[end].parent, start);
}

int main () {
  int N, i, s, d, w;

  FILE *fin = fopen("test.in", "r");
  FILE *fout = fopen("test.out", "w");

  fscanf(fin, "%d", &N);

  for (i = 0; i < N; i++) {
    entry t;
    fscanf(fin, "%d %d %d", &(t.start), &(t.end), &(t.weight));
    graph.push_back(t);
  }

  for (i = 0; i < 6 + 1; i++) {
    node t;
    t.num = i;
    t.dis = INT_MAX;
    t.is_visit = 0;
    t.parent = 0;
    verts.push_back(t);
  }

  verts[1].dis = 0;
  dis(1, 6);
  
  printf("distance %d\n", verts[6].dis);
  print_route(6, 1);
  return 0;
}
