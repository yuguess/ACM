#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define MAX 500010

struct T {
  int v;
  int p;
};


T d[MAX];
long long bit[MAX];
int n;

long long read(int idx) {
  long long sum = 0;

  while (idx) {
    sum += bit[idx];  
    idx -= (idx & -idx);
  }

  return sum;
}

void update(int idx, int val) {
  while (idx <= n) {
    bit[idx] += val;  
    idx += (idx & -idx);
  }
}

int vCmp(const void *a, const void *b) {
  if (*(int*)a < *(int*)b) 
    return -1;
  if (*(int*)a == *(int*)b) 
    return 0;
  if (*(int*)a > *(int*)b) 
    return 1;
}

int pCmp(const void *a, const void *b) {
  if (((T*)a)->p < ((T*)b)->p) 
    return -1;
  if (((T*)a)->p == ((T*)b)->p) 
    return 0;
  if (((T*)a)->p > ((T*)b)->p) 
    return 1;
}

int main() {
  long long sum = 0;

  while (scanf("%d", &n) && n) {
    for (int i = 0; i < n; i++) {
      d[i].p = i;
      scanf("%d", &d[i].v);
    }

    qsort(&(d[0].v), n, sizeof(T), vCmp);
    for (int i = 0; i < n; i++) {
      //printf("%d\n", d[i].v);
      d[i].v = i + 1;
      //printf("a %d\n", d[i].v);
      
    }
    qsort(d, n, sizeof(T), pCmp);
    //qsort(&(d[0].p), n, sizeof(T), pCmp);

    //for (int i = 0; i < n; i++)
      //printf("%d %d\n", d[i].v, d[i].p);

    for (int i = n - 1; i >= 0; i--) {
      sum += read(d[i].v);
      update(d[i].v, 1);
    }

    printf("%lld\n", sum);

    sum = 0;
    memset(bit, 0, sizeof(long long) * (n + 1));
  }
}

