#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX_WL 15
#define MAX 516010
#define MAX_EDGE 27

int hashV = 1;
int p = 0;

int r[MAX];
int sz[MAX]; 
int degree[MAX];

struct Node {
  struct Node* edges[MAX_EDGE];
  int hash;
} pool[MAX * 11];

int insert(char *d) {
  Node *n = pool;
  int idx = 0;

  while (*d) {
    idx = *d - 'a';
    if (n->edges[idx] == NULL) {
      n->edges[idx] = (&pool[p++]);
    }
    n = n->edges[idx];
    d++;
  }

  if (n->hash == 0) {
    n->hash = hashV++;  
  }

  return n->hash;
}

int root(int idx) {
  if (idx == r[idx])
    return idx;

  r[idx] = root(r[idx]);
  return r[idx];
}

void unite(int idx1, int idx2) {
  if (idx1 == idx2)
    return;

  idx1 = root(idx1);
  idx2 = root(idx2);

  if (idx1 != idx2) {
    if (sz[idx1] > sz[idx2]) {
      r[idx2] = idx1;      
      sz[idx1] += sz[idx2];
    } else {
      r[idx1] = idx2;      
      sz[idx2] += sz[idx1];
    }
  }
}

bool isConnect(int N) {
  for (int i = 1; i <= N; i++) {
    if (sz[i] == N) {
      return true;
    }
  }

  return false;
}

bool isEuler(int N) {
  int oddNum = 0;

  for (int i = 0; i <= N; i++) {
    if (degree[i] % 2 != 0) {
      oddNum++;
      if (oddNum > 2)
        return false;
    }
  }

  if (oddNum != 2 && oddNum != 0) {
    return false;
  }

  return true;
}

int main() {
  int N = 0, i = 0, j = 0;
  char b[MAX_WL], e[MAX_WL];

  for (int k = 0; k < MAX; k++) {
    r[k] = k;
    sz[k] = 1;
  }

  while (scanf("%s%s", b, e) > 0) {
    i = insert(b);
    j = insert(e);

    degree[i]++;
    degree[j]++;

    unite(i, j);

    N = max(N, max(i, j));
  }

  // deal with empty data !
  if (N == 0) {
    printf("Possible\n");
    return 0;
  }

  if (isEuler(N) && isConnect(N)) {
    printf("Possible\n");
  } else {
    printf("Impossible\n");
  }
}
