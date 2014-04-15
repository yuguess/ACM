#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 50010

int fNum = 0;

int s[MAX];
int r[MAX];

int root(int n) {

}

void unite(int rx, int x, int ry, int y, int r) {

  if (sz[] > sz[]) {

  } else {

  }
}

int main() {
  int N = 0, k = 0, d = 0, x = 0, y = 0;

  scanf("%d %d", N, k);
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
}
