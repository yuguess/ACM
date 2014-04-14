#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX_N 30010  

int s[MAX_N];
int sz[MAX_N];

int root(int n) {
  while (n != s[n]) {
    s[n] = s[s[n]];
    n = s[n];
  }

  return n;
}

int unite(int p, int q) {
  if (p == q)
    return 0;

  int rp = root(p);
  int rq = root(q);
  if (rp != rq) {
    if (sz[rp] > sz[rq]) {
      s[rq] = rp;      
      sz[rp] += sz[rq];
    } else {
      s[rp] = rq;      
      sz[rq] += sz[rp];
    }
  }
}

int main() {
  int n = 0, m = 0, gm = 0, id = 0, rt = 0;

  while (scanf("%d %d", &n, &m) && (n != 0 || m != 0)) {
    //printf("n %d, m %d\n", n, m);

    for (int i = 0; i < n; i++) {
      s[i] = i;
      sz[i] = 1;
    }

    while (m--) {
      scanf("%d", &gm);
      scanf("%d", &rt);
      gm--;

      while (gm--) {
        scanf("%d", &id);
        unite(rt, id);   
      }
    }

    printf("%d\n", sz[root(0)]);
  }
}
