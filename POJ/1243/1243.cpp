#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

#define G_MAX 32
#define L_MAX 32

int f[G_MAX][L_MAX];

int fun(int g, int l) {
  if (g == 0)
    return 0;
  if (l == 0)
    return g;
  if (f[g][l] != -1)
    return f[g][l];

  return f[g][l] = 1 + fun(g - 1, l) + fun(g - 1, l - 1);
}

int main() {
  int g = -1, l = -1;
  int i = 0;
  memset(f, -1, sizeof(int) * G_MAX * L_MAX);

  while (scanf("%d %d", &g, &l) && g) {
    printf("Case %d: %d\n", ++i, fun(g, l));
    memset(f, -1, sizeof(int) * (g + 1) * (l + 1));
  }
}
