#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 1010

char A[MAX];
char B[MAX];

int a[MAX][MAX];

int main() {
  int la = 0, lb = 0;

  while (cin >> la >> A + 1 >> lb >> B + 1) {
    int minD = 0;

    for (int i = 0; i < MAX; i++) {
      a[0][i] = i;
      a[i][0] = i;
    }

    for (int i = 1; i <= la; i++)
      for (int j = 1; j <= lb; j++) {
        if (A[i] == B[j])
          a[i][j] = min(a[i - 1][j - 1], min(a[i][j - 1] + 1, a[i - 1][j] + 1));
        else
          a[i][j] = min(a[i - 1][j], min(a[i][j - 1], a[i - 1][j - 1])) + 1;
      }

    printf("%d\n", a[la][lb]);
    memset(a, 0, sizeof(int) * MAX * MAX);
  }
}
