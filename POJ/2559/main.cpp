#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 100010

int lm[MAX];
int rm[MAX];
int d[MAX];
int qe = -1;
pair<int, int> a[MAX];

void lenqueue(int h, int idx) {
  while (qe != -1 && h < a[qe].first) {
    lm[a[qe].second] = idx + 1;
    qe--;
  }

  qe++;
  a[qe] = make_pair(h, idx); 
}

void renqueue(int h, int idx) {
  while (qe != -1 && h < a[qe].first) {
    rm[a[qe].second] = idx - 1;
    qe--;
  }

  qe++;
  a[qe] = make_pair(h, idx); 
}

int main() {
  int n = 0;
  long long am = 0;

  while (scanf("%d", &n) && n) {
    for (int i = 0; i < n; i++)
      scanf("%d", d + i);

    for (int i = 0; i < n; i++) {
      renqueue(d[i], i);
    }

    renqueue(-1, n); 
    qe = -1;

    for (int i = n - 1; i >= 0; i--) {
      lenqueue(d[i], i);
    }

    for (int i = 0; i < n; i++) {
      am = max(am, static_cast<long long>(rm[i] - lm[i] + 1) * d[i]);
    }

    printf("%lld\n", am);

    am = 0;
    qe = -1;
    memset(lm, 0, sizeof(int) * n);
    memset(rm, 0, sizeof(int) * n);
    memset(d, 0, sizeof(int) * n);
  }
}
