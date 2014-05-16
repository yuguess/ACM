#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
using namespace std;

#define MAX 10010
#define LOG_MAX 16

int N;
int s[MAX];
int L[MAX];
int T[MAX];
int P[MAX][LOG_MAX];

int root(int n) {
  if (n == s[n]) 
    return n;

  int p = s[n];
  s[n] = root(p);
  L[n] = L[p] + L[n];

  return s[n];
}

int unite(int p, int q) {
  int rp = root(p);
  int rq = root(q);

  if (rp != rq) {
    s[rq] = rp;
    L[rq] = 1 + L[p];
  }
}

int process3() {
  for (int i = 1; i <= N; i++)
    for (int j = 0; 1 << j < N; j++) 
      P[i][j] = -1;

  for (int i = 1; i <= N; i++)
    P[i][0] = T[i];

  for (int i = 1; 1 << i < N; i++) 
    for (int j = 1; j <= N; j++) {
      P[j][i] = P[P[j][i - 1]][i - 1];
      //printf("table %d %d, %d\n", j, i, P[j][i]);
    }

}

int query(int l, int u) {
  if (L[l] < L[u])
    swap(l, u);

  for (int i = log2(L[l]); i >= 0; i--) {
    if (L[l] - (1 << i) >= L[u])
      l = P[l][i]; 
  }

  if (l == u) return l;

  for (int i = log2(L[l]); i >= 0; i--)
    if (P[l][i] != -1 && P[u][i] != -1 && P[l][i] != P[u][i]) {
      l = P[l][i];
      u = P[u][i];
    }

  return T[l];
}

int main() {
  int caseN = 0, p = 0, q = 0;
  scanf("%d", &caseN);
  while (caseN--) {
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {
      L[i] = 0;
      s[i] = i;
      T[i] = i;
    }

    for (int i = 0; i < N - 1; i++) {
      scanf("%d %d", &p, &q);
      unite(p, q);
      T[q] = p;
    }

    for (int i = 1; i <= N; i++) {
      root(i);
    }

    process3();

    scanf("%d %d", &p, &q); 
    printf("%d\n", query(p, q));
  }
}
