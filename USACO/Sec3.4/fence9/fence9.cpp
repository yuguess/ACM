/*
ID: yuguess1
TASK: fence9 
LANG: C++
*/

#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#define OUT stdout
#define IN fin
#define MAX 27

char pre[MAX];
char in[MAX];

int main() {
  long sum = 0;
  int n = 0, m = 0, p = 0;

  FILE *fin = fopen("fence9.in", "r");
  FILE *fout = fopen("fence9.out", "w");

  fscanf(fin, "%s", &n);
  fscanf(fin, "%s", &m);
  fscanf(fin, "%s", &p);

  //for (int i = )

  fprintf(OUT, "\n");
  fclose(fin);
  fclose(fout);
}
