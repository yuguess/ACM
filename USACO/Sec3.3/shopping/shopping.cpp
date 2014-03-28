/*
ID: yuguess1
TASK: shopping 
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <map>
#include <math.h>
#include <string>
using namespace std;

#define OUT fout
#define IN fin
#define MAX_C 1000 
#define MAX 0x01000000
int s, n;

class Deal {
public:
  int pairn;
  vector<int> pc;
  vector<int> pn;
  int price;
};

map<int, int> m;
map<int, int> tb;

int prices[MAX_C] = {0};
vector<Deal> ds;

int f(map<int, int> &m, int cate) {
    if (cate == s) {  
    int thr = 0;
    for (map<int, int>::iterator it = m.begin(); it != m.end(); it++) { 
      thr += prices[it->first] * it->second;
    }
    
    return thr; 
  }

  for (map<int, int>::iterator it = m.begin(); it != m.end(); it++) { 
    if (it->second < 0)
      return MAX;
  }

  int nth = 0, key = 0;
  for (map<int, int>::iterator it = m.begin(); it != m.end(); it++) {
    key += it->second * pow(6, nth + 1);
    nth++;
  }
  key += cate * pow(6, nth) * 100; 

  if (tb.find(key) != tb.end())
    return tb[key];

  for (int i = 0; i < ds[cate].pairn; i++) {
    m[ds[cate].pc[i]] -= ds[cate].pn[i];
  }
  int fir = f(m, cate) + ds[cate].price; 

  for (int i = 0; i < ds[cate].pairn; i++) {
    m[ds[cate].pc[i]] += ds[cate].pn[i];
  }

  int sec = f(m, cate + 1);

  tb[key] = min(fir, sec);
  return tb[key];
}

int main() {
  int _pc, _pn;

  FILE *fin = fopen("shopping.in", "r");
  FILE *fout = fopen("shopping.out", "w");

  fscanf(IN, "%d", &s);
  ds.resize(s);

  for (int i = 0; i < s; i++) {
    fscanf(IN, "%d", &(ds[i].pairn)); 
    for (int j = 0; j < ds[i].pairn; j++) {
      fscanf(IN, "%d %d", &_pc, &_pn); 
      ds[i].pc.push_back(_pc);
      ds[i].pn.push_back(_pn);
    }
    fscanf(IN, "%d", &(ds[i].price));
  }

  fscanf(IN, "%d", &n);
  for (int i = 0; i < n; i++) {
    fscanf(IN, "%d %d", &_pc, &_pn);    
    m[_pc] = _pn;
    fscanf(IN, "%d", &(prices[_pc]));
  }

  int min_p = f(m, 0);
  fprintf(OUT, "%d\n", min_p);

  fclose(fin);
  fclose(fout);
}
