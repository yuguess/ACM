#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX_N 100010

int nd[MAX_N];

int main() {
  int N = 0, n = 0, q = 0, i = 0, j = 0;
  char act;

  scanf("%d", &N);
  while (N--) {
    scanf("%d %d", &n, &q);

    while (q--) {
      scanf("%c %d %d", &act, &i, &j);
      switch(act) {

      case 'A':
        break;

      case 'D':
        break;
      }
    }

    memset(nd, 0, sizeof(int) * (n + 1));
  }
}
