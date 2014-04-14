#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 50010

int s[MAX];
int sz[MAX];

int numR; 

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
    numR--;

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
  int n = 0, m = 0, tmp1 = 0, tmp2 = 0, ncase = 1;

  while (scanf("%d %d", &n, &m) && (n != 0 || m != 0)) {
    for (int i = 1; i <= n; i++) {
      s[i] = i;
      sz[i] = 1;
    }
    numR = n;

    while (m--) {
      scanf("%d %d", &tmp1, &tmp2);
      unite(tmp1, tmp2);
    }

    printf("Case %d: %d\n", ncase++, numR);
  }
}
