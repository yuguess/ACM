#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

#define MAX 300100
#define MAX_N MAX 

int bit[MAX];
int n = 0;

void update(int idx, int val) {
  while (idx <= n) {
    bit[idx] += val;  
    idx += (idx & -idx);
  }
}

int findKth(int k) {
  int mb = (int)(log2(k)) + 3, cnt = 0, ans = 0;
  //int mb = 20, cnt = 0, ans = 0;

  //printf("mb %d, k %d\n", mb, k);
  for (int i = mb; i >= 0; i--) {
    ans += (1 << i);
    if (ans >= n || cnt + bit[ans] >= k) {
      ans -= (1 << i);
    } else {
      cnt += bit[ans];
    }
  }

  return ans + 1;
}

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
  int M = 0, op = 0, a = 0, b = 0, ra = 0, rb = 0, k = 0, ng = 0;

  scanf("%d %d", &n, &M);
  ng = n;
  update(1, n);

  for (int i = 0; i <= n; i++) {
    s[i] = i;
    sz[i] = 1;
  }

  for (int i = 0; i < M; i++) {
    scanf("%d", &op);

    if (op == 0) {
      scanf("%d %d", &a, &b);
      ra = root(a);
      rb = root(b);

      if (ra != rb) {
        ng--;
        update(sz[ra], -1);
        update(sz[rb], -1);
        update(sz[ra] + sz[rb], 1);
        unite(a, b);
      }

    } else {
      scanf("%d", &k);
      printf("%d\n", findKth(ng - k + 1));
    }
  }
}
