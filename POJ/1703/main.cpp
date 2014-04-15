#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX_N 100010

int s[MAX_N];
int r[MAX_N];
int sz[MAX_N];

int root(int n) {
  //printf("find root %d\n", n);
  while (n != s[n]) {
    //r[n] =  r[n] ^ r[s[n]];
    r[n] = r[n] + r[s[n]];
    s[n] = s[s[n]];

    n = s[n];
  }

  //printf("root %d\n", n);
  return n;
}

int find(int p, int q) {
  return root(p) == root(q) ? (r[p] == r[q] ? 1 : 2) : 0;
}

int unite(int p, int q) {
  int rp = root(p);
  int rq = root(q);

  if (rp != rq) {
    if (sz[rp] > sz[rq]) {
      s[rq] = rp;      
      sz[rp] += sz[rq];
      sz[rq] = (r[p] + 1 + r[q]) % 2;
      //r[rq] = r[p] ^ 1 ^ r[q]; 
    } else {
      s[rp] = rq;      
      sz[rq] += sz[rp];
      sz[rp] = (r[p] + 1 + r[q]) % 2;
      //r[rp] = r[p] ^ 1 ^ r[q];
    }
  }
}

int main() {
  int N = 0, n = 0, q = 0, i = 0, j = 0;
  char act[2];

  scanf("%d", &N);
  while (N--) {
    scanf("%d %d", &n, &q);

    if (n == 2) {
      s[1] = 1;
      s[2] = 1;
      r[1] = 0; 
      r[2] = 1;
    } else {
      for (i = 1; i <= n; i++) {
        s[i] = i;
        r[i] = 0;
        sz[i] = 1;
      }
    }

    while (q--) {
      scanf("%s %d %d", &act, &i, &j);
      //printf("act %s\n", act);

      if (strcmp(act, "A") == 0) {
        switch (find(i, j)) {
        case 0:
          printf("Not sure yet.\n");
          break;
        case 1:
          printf("In the same gang.\n");
          break;
        case 2:
          printf("In different gangs.\n");
          break;
        }
      } else if (strcmp(act, "D") == 0) {
        unite(i, j);
      }
    }
  }
}
