#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <map>
using namespace std;

#define MAX_N 50100
#define MAX_LOG2 17

int N = 0;
int A[MAX_N];
int minR[MAX_N][MAX_LOG2];
int maxR[MAX_N][MAX_LOG2];

void processMin() {
  for (int i = 0; i < N; i++) {
    minR[i][0] = i;
  }

  for (int step = 1; 1 << step <= N; step++)
    for (int j = 0; j + (1 << step) - 1 < N; j++)
      if (A[minR[j][step - 1]] < A[minR[j + (1 << (step - 1))][step - 1]]) {
        minR[j][step] = minR[j][step - 1]; 
      } else {
        minR[j][step] = minR[j + (1 << (step - 1))][step - 1];
      }
}

void processMax() {
  for (int i = 0; i < N; i++) {
    maxR[i][0] = i;
  }

  for (int step = 1; 1 << step <= N; step++)
    for (int j = 0; j + (1 << step) - 1 < N; j++)
      if (A[maxR[j][step - 1]] > A[maxR[j + (1 << (step - 1))][step - 1]]) {
        maxR[j][step] = maxR[j][step - 1]; 
      } else {
        maxR[j][step] = maxR[j + (1 << (step - 1))][step - 1];
      }
}

int RMinQ(int l, int u) {
  int k = log2(u - l + 1);
  //printf("first %d %d %d\n", l, k, minR[l][k]);
  //printf("secon %d %d %d\n", u - (1 << k) + 1, k, minR[u - (1 << k) + 1][k]);
  return min(A[minR[l][k]], A[minR[u - (1 << k) + 1][k]]);
}

int RMaxQ(int l, int u) {
  int k = log2(u - l + 1);
  return max(A[maxR[l][k]], A[maxR[u - (1 << k) + 1][k]]);
}

int main() {
  int Q = 0, l = 0, u = 0;
  scanf("%d %d", &N, &Q);
  for (int i = 0; i < N; i++) {
    scanf("%d", A + i);
  }

  processMin();
  processMax();

  for (int i = 0; i < Q; i++) {
    scanf("%d %d", &l, &u);
    printf("%d\n", RMaxQ(l - 1, u - 1) - RMinQ(l - 1, u - 1));
  }

  //for (int i = 0; i < 6; i++)
  //  for (int j = i; j < 6; j++) {
  //    printf("range %d %d, min %d, max %d\n", i, j, RMinQ(i, j), RMaxQ(i, j));
  //  }
}
