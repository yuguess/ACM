#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 1000

int d[MAX][MAX];
int aux[MAX][MAX];

int maxConSum(int a[], int m) {
  int s[MAX];
  memset(s, 0, sizeof(int) * MAX);

  int subMax = 0;
  int endMax = 0;

  for (int i = 0; i < m; i++) {
    if (a[i] < 0) {
      subMax = max(endMax, subMax);
    } else {
      endMax = max(endMax + a[i], a[i]);
    }
  }

  return max(subMax, endMax); 
}

int main() {
  int r = 0, c = 0;

  scanf("%d %d", &r, &c);
  for (int i = 0; i < r; i++) 
    for (int j = 0; j < c; j++)
      scanf("%d", &d[i][j]);

  for (int ci = 0; ci < c; ci++) {
    int sum = 0;
    for (int ri = c - 1; ri >= 0; ri--) {
      sum += d[ri][ci]; 
      aux[ri][ci] = sum;
    }
  }

  int sum = 0;
  for (int ci = 0; ci < c; ci++) {
    for (int ri = 0; ri < r; ri++) {
      sum = max(sum, maxConSum(aux[ri], c));
    }
  }

  printf("sum %d\n", sum);
}
