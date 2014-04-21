#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 400010

int L = 0;
char S[MAX];
int F[MAX];

void buildFailure() {
  F[0] = F[1] = 0;
  
  for (int i = 2; i <= L; i++) {
    int j = F[i - 1];

    while (1) {
      if (S[j] == S[i - 1]) {
        F[i] = j + 1;
        break;
      }

      if (j == 0) {
        F[i] = 0;
        break;
      }

      j = F[j];
    }
  }
}

void revPrint(int idx) {
  if (F[idx] == 0)
    return;

  revPrint(F[idx]);
  printf("%d ", F[idx]);
}

int main() {
  while (scanf("%s", S) > 0) {
    L = strlen(S);
    buildFailure();
    
    revPrint(L);
    printf("%d\n", L);

    memset(F, 0, sizeof(int) * (L + 1));
  }
}
