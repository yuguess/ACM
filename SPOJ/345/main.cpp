#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <algorithm>

using namespace std;

#define MAX 110

int n[MAX];
int dp[MAX][MAX];
int c[MAX][MAX];

int main() {
  int n = 0;
  int minS = INT_MAX;

  while (scanf("%d", &n) != EOF) {
    
    for (int i = 0; i < n; i++) {
      scanf("%d", &c[i][i]);
    }

    for (int b = n - 1; b >= 0; b--) 
      for (int e = b + 1; e < n; e++) {
        for (int s = b; s <= e - 1; s++) {
          //printf("[%d][%d]: %d, [%d][%d]:%d\n", b, s, dp[b][s], 
              //s + 1, e, dp[s + 1][e]);
          minS = min(minS, dp[b][s] + dp[s + 1][e] + c[b][s] * c[s + 1][e]);
          c[b][e] = (c[b][s] + c[s + 1][e]) % 100;
        }

        if (minS != INT_MAX) {
          //printf("%d %d %d\n", b, e, minS);
          dp[b][e] = minS;
          minS = INT_MAX;
        }
      }

    printf("%d\n", dp[0][n - 1]);
    memset(dp, 0, sizeof(int) * n * n);
    memset(c, 0, sizeof(int) * n * n);
    minS = INT_MAX;
  }
}
