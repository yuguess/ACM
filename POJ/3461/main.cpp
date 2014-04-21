#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX_P 10010 
#define MAX_S 1000010

int M = 0;
int WL = 0;
int TL = 0;

int F[MAX_P];
char W[MAX_P];
char T[MAX_S];

void kmp() {
  int j = 0;

  for (int i = 0; i < TL; i++) {

    while (1) {
      if (T[i] == W[j]) {
        j++;
        if (j == WL) {
          M++;
          j = F[j];
        }

        break;
      }

      if (j == 0) {
        break;
      }

      j = F[j];
    }
  }
}

void buildFailFunc() {
  F[0] = F[1] = 0; 

  for (int i = 2; i <= WL; i++) {
    int j = F[i - 1];

    while (1) {
      if (W[j] == W[i - 1]) {
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
  int n = 0;
  scanf("%d", &n);

  while (n--) {
    scanf("%s %s", W, T); 

    WL = strlen(W);
    TL = strlen(T);
    
    buildFailFunc();
    kmp();
    printf("%d\n", M);
    M = 0;
    memset(F, 0, sizeof(int) * (WL + 1));
  }
}
