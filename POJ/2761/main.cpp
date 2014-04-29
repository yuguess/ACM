#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 100010
#define MAX_Q 50011

int d[MAX];

struct Node {
  int low;
  int upper;
  int res;
  int idx;
  int k;
} query[MAX_Q];

int main() {
  int m = 0, n = 0;
  scanf("%d %d", &m, &n);

  for (int i = 0; i < m; i++) {
    scanf("%d", d + i);
  }

  for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &query[i].low, &query[i].upper, &query[i].k);
    query[i].idx = i;
  }

  //sort

  //Treap treap;

  for (int i = query[i].low - 1; i < query[i].upper; i++) {
    treap.insert(d[i]);
  }

  for (int i = 1; i < n; i++) {
    for (int j = query[i - 1].low - 1; j < query[i].low - 1; j++) {
      treap.del(d[j]);
    }

    for (int j = query[i - 1].upper; j <= query[i].upper - 1; j++) {
      treap.insert(d[j]);
    }

    query[i].res = treap.findKth(query[i].k);
  }

  //sort

  for (int i = 0; i < n; i++) {
    printf("%d\n", query[i].res);
  }
}
