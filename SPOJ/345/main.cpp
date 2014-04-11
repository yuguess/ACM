#include <stdio.h>

#define MAX 110

int n[MAX];
int dp[MAX][MAX];
int c[MAX][MAX];

int main() {
  int n = 0;

  while (scanf("%d", &n) != EOF) {
    
    for (int i = 0; i < n; i++) {
      scanf("%d", c);
    }

    for (int b = n - 1; b >= 0; b--) 
      for (int e = b + 1; e < n; e++)
        for (int s = b; s < e - 1; s++) {
          dp[b][e] = dp[b][s] + dp[s + 1][e] + c[b][s] * c[s + 1][e];
          if (dp[b][e] == minS) {
            c[b][e] = (c[b][s] + c[s + 1][e]) % 100;
          } else if (dp[b][e] < minS) {

          }
        }
  }
}
