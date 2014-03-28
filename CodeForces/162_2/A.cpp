#include <stdio.h>
using namespace std;
#define MAX 50
#define OUT stdin

char s[MAX];
char t[MAX];
int sn, tn;

int main() {
  char c;

  //FILE *fin = fopen("A.in", "r");

  for (int i = 0;; i++) {
    fscanf(OUT, "%c", &c);
    if (c == '\n') {
      break;
    } else {
      s[i] = c;
      sn = i;
    }
  }
  for (int i = 0;; i++) {
    fscanf(OUT, "%c", &c);
    if (c == '\n') {
      break;
    } else {
      t[i] = c;
      tn = i;
    }
  }

  int p = 0;
  for (int i = 0; i <= tn; i++) {
    if (s[p] == t[i]) {
      p++;
    }
  }

  printf("%d\n", p + 1);
}
