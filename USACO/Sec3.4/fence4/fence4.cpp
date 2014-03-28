/*
ID: yuguess1
TASK: fence4 
LANG: C++
*/

#include <stdio.h>
#include <vector>
#include <map>
#include <math.h>
#include <string>
using namespace std;

#define OUT stdout 
#define IN fin
#define MAX_C 1000 
#define MAX 0x01000000
int s, n;

int main() {

  FILE *fin = fopen("fence4.in", "r");
  FILE *fout = fopen("fence4.out", "w");



  //fscanf(IN, "%d", &s);
  //ds.resize(s);

  //for (int i = 0; i < s; i++) {
  //  fscanf(IN, "%d", &(ds[i].pairn)); 
  //  for (int j = 0; j < ds[i].pairn; j++) {
  //    fscanf(IN, "%d %d", &_pc, &_pn); 
  //    ds[i].pc.push_back(_pc);
  //    ds[i].pn.push_back(_pn);
  //  }
  //  fscanf(IN, "%d", &(ds[i].price));
  //}

  //fscanf(IN, "%d", &n);
  //for (int i = 0; i < n; i++) {
  //  fscanf(IN, "%d %d", &_pc, &_pn);    
  //  m[_pc] = _pn;
  //  fscanf(IN, "%d", &(prices[_pc]));
  //}

  //int min_p = f(m, 0);
  fprintf(OUT, "%d\n", min_p);

  fclose(fin);
  fclose(fout);
}
