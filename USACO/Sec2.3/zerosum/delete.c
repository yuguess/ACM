#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
  char a;
  char b;
  char c;
} Radix;

int compare(const void*t1, const void *t2) {
  return (((Radix*)t1)->b - ((Radix*)t2)->b);
}

int main () {
  //char a[] = {'-', ' ', '+', '+', '+', '+'}; 
  //char a[] = {'+', '-', '+', '-', '-', '+'};
  char a[] = {'-', ' ', '+', '+', '+', '+'};
  int rd_sum = 0;
  int i;
  for (i = 0; i < 6; i++) {
    char c = a[i];
    if (c == ' ') {
      rd_sum = rd_sum * 10 + 1;   
    }

    if (c == '+') {
      rd_sum = rd_sum * 10 + 2;
    }

    if (c == '-') {
      rd_sum = rd_sum * 10 + 3;
    }
  }

  printf("%d\n", rd_sum);
  /*
  Radix t = {'a', 'b', 'c'};
  Radix t2 = {'c', 'a', 'b'};
  Radix t3 = {'b', 'c', 'a'};

  Radix tt[]={t, t2, t3};
  qsort(tt, 3, sizeof(Radix), compare);

  int i = 0;
  int j = 0;
  for (i = 0; i < 3; i++) {
    printf("%c %c %c\n", tt[i].a, tt[i].b, tt[i].c); 
  }
  */
}
