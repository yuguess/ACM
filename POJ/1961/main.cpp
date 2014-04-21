#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 1000010 

int L = 0;
char s[MAX];
int F[MAX];

void buildFailFunc() {
  F[0] = F[1] = 0;

  for (int i = 2; i <= L; i++) {
    int j = F[i - 1]; 

    while (1) {
      if (s[j] == s[i - 1]) {
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

int main() {
  int k = 1;
  while (scanf("%d", &L) && L) {
    scanf("%s", s);
    buildFailFunc();

    printf("Test case #%d\n", k++); 
    for (int i = 2; i <= L; i++) {
      if (F[i] != 0 && i % (i - F[i]) == 0) {
        printf("%d %d\n", i, i / (i - F[i]));
      }
    }
    printf("\n");

    memset(F, 0, sizeof(int) * (L + 1));
  }
}
