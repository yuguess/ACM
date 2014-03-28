/*
ID: yuguess1
TASK: heritage 
LANG: C++
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#define OUT fout
#define IN fin
#define MAX 27

char pre[MAX];
char in[MAX];

void post_print(string pre, string in, int beg, int end, int in_beg, int in_end, FILE *fout) {
  if (beg > end)
    return;

  int mid = pre.find(in[in_beg]);
  int len = mid - beg;

  post_print(pre, in, beg, mid - 1, in_beg + 1, in_beg + len, fout); 

  post_print(pre, in, mid + 1, end, in_beg + 1 + len, in_end, fout);

  fprintf(OUT, "%c", in[in_beg]);
}

int main() {
  FILE *fin = fopen("heritage.in", "r");
  FILE *fout = fopen("heritage.out", "w");

  fscanf(fin, "%s", &pre);
  fscanf(fin, "%s", &in);

  post_print(pre, in, 0, strlen(pre) - 1, 0, strlen(pre) - 1, fout);

  fprintf(OUT, "\n");
  fclose(fin);
  fclose(fout);
}
