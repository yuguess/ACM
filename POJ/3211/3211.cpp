#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define STR_MAX 10
#define COLOR_MAX 10
#define CLOTH_MAX 100
#define TIME_MAX 1000
#define WASH_TIME_PERCOLOR CLOTH_MAX * CLOTH_MAX * TIME_MAX / 2

int cost[COLOR_MAX][CLOTH_MAX];
int colorTotal[COLOR_MAX];
int costByColor[COLOR_MAX];
int clothByColor[COLOR_MAX];

map<string, int> colToIdx;
bool f[WASH_TIME_PERCOLOR];

int main() {
  int M = 0, N = 0, c = 0, sum = 0, balanceTime = 0;
  char str[STR_MAX];

  while (1) {
    scanf("%d %d", &M, &N);
    if (M == 0 && N == 0)
      break;

    colToIdx.clear();
    memset(cost, 0, sizeof(int) * COLOR_MAX * CLOTH_MAX);
    memset(costByColor, 0, sizeof(int) * COLOR_MAX);
    memset(clothByColor, 0, sizeof(int) * COLOR_MAX);
    memset(f, false, sizeof(bool) * WASH_TIME_PERCOLOR);
    f[0] = true;
    sum = 0;

    for (int i = 0; i < M; i++) {
      scanf("%s", str);
      int tmp = colToIdx.size();
      colToIdx[str] = tmp;
    }

    for (int i = 0; i < N; i++) {
      scanf("%d %s", &c, str);
      int idx = colToIdx[str];
      //printf("idx %d\n", idx);
      cost[idx][clothByColor[idx]] = c;
      clothByColor[idx]++;
      costByColor[idx] += c;
    }

    for (int i = 0; i < M; i++) {
      balanceTime = costByColor[i] / 2;
      //printf("balanceTime %d\n", balanceTime);

      for (int j = 0; j < clothByColor[i]; j++) 
        for (int k = balanceTime; k >= cost[i][j]; k--) {
          //printf("%d:%d | %d:%d\n", k, f[k], k - cost[i][j], f[k - cost[i][j]]);
          f[k] = f[k] || f[k - cost[i][j]];
        }

      for (int j = balanceTime; j >= 0; j--) {
        if (f[j]) {
          //printf("costByColor[%d]:%d, balance %d\n", i, costByColor[i], j);
          sum += (costByColor[i] - j);
          break;
        }
      }

      memset(f, false, sizeof(bool) * (balanceTime + 1));
      f[0] = true;
    }

    printf("%d\n", sum);
  }
}
