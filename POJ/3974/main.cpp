#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 1000010

char r[MAX];
char s[MAX * 2];   
int span[MAX * 2];

int main() {

  int l = 0;
  int j = 0;
  int k = 1;

  while (scanf("%s", r) && strcmp(r, "END")) {
    l = strlen(r);
    j = 0;

    for (int i = 0; i < l; i++) {
      s[j++] = '#';
      s[j++] = r[i];
    }
    s[j] = '#';
    s[j + 1] = '\0';

    int c = 1;
    int maxS = 1;
    int rr = 2;

    span[0] = 0;
    span[1] = 1;

    for (int i = 2; i < 2 * l + 1; i++) {

      if ((2 * c - i) >= 0 && i + span[2 * c - i] < rr) {
        span[i] = span[2 * c - i];
      } else {

        int st = max(i, rr);
        while (st <= 2 * l && 2 * i - st >= 0 
            && s[st] == s[2 * i - st]) {
          span[i] = st - i;
          st++;
        }

        if (i + span[i] > rr) {
          c = i; 
          rr = i + span[i]; 
        }
      }

      //printf("%d, %d\n", i, span[i]);  
      maxS = max(maxS, span[i]);
    }

    printf("Case %d: %d\n", k++, maxS); 
  }

}
