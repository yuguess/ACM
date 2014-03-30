#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX_WEIGHT 25
#define MAX_NUM 21
#define MAX_POS 30
#define MAX_STATE MAX_WEIGHT * MAX_NUM * MAX_POS

int pos[MAX_POS];
int cost[MAX_WEIGHT];

int f[MAX_NUM][MAX_STATE];

int main() {
  int g = 0, c = 0, totalWeight = 0, minPos = 0, maxPos = 0;

  scanf("%d %d", &c, &g);
  for (int i = 0; i < c; i++) {
    scanf("%d", &pos[i]);
    if (i == 0)
      minPos = pos[i];

    if (i == c - 1)
      maxPos = pos[i];
  }

  for (int i = 1; i <= g; i++) {
    scanf("%d", &cost[i]);
    totalWeight += cost[i];
  }

  int shift = 7500;
  int low = minPos * totalWeight;
  int high = maxPos * totalWeight;
  f[0][0 + shift] = 1;

  for (int i = 1; i <= g; i++)
    for (int j = low; j <= high; j++)  
      for (int k = 0; k < c; k++) 
        f[i][j + shift + - pos[k] * cost[i]] += f[i - 1][j  + shift]; 
  
  printf("%d\n", f[g][0 + shift]);
}
