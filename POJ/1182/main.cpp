#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 50010

int fNum = 0;

int s[MAX];
int sz[MAX];
int r[MAX];

int con[3][3] = {2, 0, 1, 0, 1, 2 , 1, 2, 0};
int neg[3] = {2, 1, 0};

int f(int fir, int sec) {
  return con[fir][sec];
}

int rev(int rl) {
  return neg[rl];
}

int root(int n) {
  if (n == s[n])
    return n;

  int p = s[n];
  s[n] = root(p);
  r[n] = f(r[n], r[p]); 
  return s[n];
}

void unite(int rx, int x, int ry, int y, int d) {

  if (sz[rx] > sz[ry]) {
    sz[rx] += sz[ry];
    s[ry] = rx;

    r[ry] = f(f(rev(r[y]), rev(d)), r[x]);
  } else {
    s[rx] = ry; 
    sz[ry] += sz[rx];

    r[rx] = f(f(rev(r[x]), d), r[y]);
  }
}

int find(int x, int y) {
  return f(r[x], rev(r[y]));
}

int main() {
  int N = 0, k = 0, d = 0, x = 0, y = 0;

  scanf("%d %d", &N, &k);
  for (int i = 1; i <= N; i++) {
      s[i] = i;
      sz[i] = 1;
      r[i] = 1;
  }

  while (k--) {
    scanf("%d %d %d", &d, &x, &y);
    
    if ((x > N || y > N) || (d == 2 && x == y)) {
      fNum++;
      continue;
    }

    int rx = root(x);
    int ry = root(y);

    if (rx != ry) {
      unite(rx, x, ry, y, d);
    } else {
      if (find(x, y) != d) {
        fNum++;
      }
    }
  }

  printf("%d\n", fNum);
}
