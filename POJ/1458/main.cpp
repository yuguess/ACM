#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define MAX 10100

char a[MAX];
char b[MAX];

int dp[MAX][MAX]; 

int main() {
  while (scanf("%s %s", a + 1, b + 1) != EOF) {
    
    int la = strlen(a + 1);
    int lb = strlen(b + 1);


    for (int j = 1; j <= la; j++)
      for (int i = 1; i <= lb; i++) {
        if (b[i] == a[j]) {
          dp[i][j] = 1 + dp[i - 1][j - 1];
        } else {
          dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
        }
        //printf("%d %d %d\n", i, j, dp[i][j]);
      }
    printf("%d\n", dp[lb][la]);
    memset(dp, 0, sizeof(int) * (la + 1) * (lb + 1));
  }
}
