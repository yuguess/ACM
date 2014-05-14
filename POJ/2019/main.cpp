#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <deque>
using namespace std;

#define MAX_N 255

deque<pair<int, int> > minq;
deque<pair<int, int> > maxq;

int f[MAX_N][MAX_N];
int auxMin[MAX_N][MAX_N];
int auxMax[MAX_N][MAX_N];

int resMin[MAX_N][MAX_N];
int resMax[MAX_N][MAX_N];

void update(deque<pair<int, int> > &deq, int idx) {
  if (deq.front().second < idx)
    deq.pop_front();
}

template<typename T>
void push(deque<pair<int, int> > &deq, int v, int t) {
  T cmp;

  while (!deq.empty() && cmp(v, deq.back().first)) {
    deq.pop_back();
  }

  deq.push_back(make_pair(v, t));
}

int main() {
  int N = 0, B = 0, K = 0, l = 0, u = 0;
  scanf("%d %d %d", &N, &B, &K);
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) 
      scanf("%d", f[i] + j);

  for (int j = 0; j < N; j++) {
    for (int i = 0; i < B; i++) {
      push<less<int> >(minq, f[i][j], i);
      push<greater<int> >(maxq, f[i][j], i);
    }

    auxMin[0][j] = minq.front().first;
    auxMax[0][j] = maxq.front().first;

    for (int i = B, k = 1; k < N; i++, k++) {
      if (i < N) {
        push<less<int> >(minq, f[i][j], i);
        push<greater<int> >(maxq, f[i][j], i);
      }

      update(minq, k);
      update(maxq, k);

      auxMin[k][j] = minq.front().first;
      auxMax[k][j] = maxq.front().first;

    }
    
    minq.clear();
    maxq.clear();
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < B; j++) {
      push<less<int> >(minq, auxMin[i][j], j);
      push<greater<int> >(maxq, auxMax[i][j], j);
    }

    resMin[i][0] = minq.front().first;
    resMax[i][0] = maxq.front().first;

    for (int j = B, k = 1; k < N; j++, k++) {
      if (j < N) {
        push<less<int> >(minq, auxMin[i][j], j);
        push<greater<int> >(maxq, auxMax[i][j], j);
      }

      update(minq, k);
      update(maxq, k);

      resMin[i][k] = minq.front().first;
      resMax[i][k] = maxq.front().first;
    }
    
    minq.clear();
    maxq.clear();
  }

  //for (int i = 0; i < N; i++)
  //  for (int j = 0; j < N; j++) {
  //    printf("res %d %d, min %d, max %d\n", i, j, resMin[i][j], resMax[i][j]);
  //  }

  for (int i = 0; i < K ; i++) {
    scanf("%d %d", &l, &u);
    printf("%d\n", resMax[l - 1][u - 1] - resMin[l - 1][u - 1]);
  }
}
