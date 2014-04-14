#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX_B 52
#define MAX_F 1002

int dp[MAX_B][MAX_F];

int main() {
  int n = 0, b = 0, f = 0, c = 0, t = 0;
  scanf("%d", &n);

  for (int i = 1; i < MAX_B; i++) 
    dp[i][1] = 1; 


  for (int i = 1; i < MAX_B; i++)
    for (int j = 2; j < MAX_F; j++) {
      dp[i][j] = dp[i - 1][j - 1] + 1 + dp[i][j - 1];
      //printf("%d %d %d\n", i, j, dp[i][j]);
      if (dp[i][j] >= MAX_F)
        break;
    }

  while (n--) {
    scanf("%d %d %d", &c, &b, &f);
    for (t = 1; t <= MAX_F; ++t) {
      if(dp[b][t] >= f) {
        //printf("here %d %d %d\n", b, t, dp[b][t]);
        break;
      }
    }

    printf("%d %d\n", c, t);
  }
}
