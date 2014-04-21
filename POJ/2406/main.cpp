#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 1000100
char s[MAX];
int F[MAX];
int l = 0;

void buildFailure() {
  int j = 0;
  F[0] = 0;
  F[1] = 0;

  for (int i = 2; i <= l; i++) {
    j = F[i - 1]; 

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
  
  while (scanf("%s", s) && strcmp(s, ".")) {
    l = strlen(s);  
    buildFailure();

    if (l % (l - F[l]) == 0) {
      printf("%d\n", l / (l - F[l]));
    } else {
      printf("1\n");
    }

    memset(F, 0, sizeof(int) * (l + 1));
  }
}
