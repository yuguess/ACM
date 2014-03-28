/*
ID: yuguess1
TASK: fracdec 
LANG: C++
*/

#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define OUT fout
#define MAX_V 11

//int g[MAX_V][MAX_V];
int N, D;
vector<int> rems;
map<int, bool> rem_map;

int has_cycle(int rem) {
  vector<int>::iterator it;
  if (rem_map.find(N) != rem_map.end()) {
    it = find(rems.begin(), rems.end(), rem);
    return distance(it, rems.end());
  }
  return 0; 
}

int char_len = 0;

void incre_char_len(int inc, FILE *fout) {
  char_len += inc;
  if (char_len % 76 == 0) {
    //printf("char_len %d\n", char_len);
    fprintf(fout, "\n");
    //getchar();
  }
}
int main () {
  int integer, q, prev_frac;
  int len = 0; 

  vector<int> qs;
  vector<int> cycle;

  FILE *fin = fopen("fracdec.in", "r");
  FILE *fout = fopen("fracdec.out", "w");

  fscanf(fin, "%d %d", &N, &D);
 
  int prev_N = -1;

  do {
    integer = N / D;
    N = N - D * integer;
      
    qs.push_back(integer);
    
    if ((len = has_cycle(N)) != 0) {
      cycle.assign(qs.begin() + qs.size() - len, qs.end());
      qs.erase(qs.begin() + qs.size() - len, qs.end());
      break;
    } else {
      rems.push_back(N);
      rem_map.insert(pair<int, bool>(N, true));
    }

    prev_N = N;
    N = N * 10;

  } while (N != 0);

  fprintf(OUT, "%d.", qs[0]);

  if (qs.size() == 1 && cycle.size() == 0) {
    fprintf(OUT, "0");
  } else {
    if (qs[0] != 0)
      incre_char_len(floor(log10(qs[0])) + 1, OUT);
    else
      incre_char_len(1, OUT);

    for (int i = 1; i < qs.size(); i++) {
      incre_char_len(1, OUT);
      fprintf(OUT, "%d", qs[i]);
    }

    if (cycle.size() != 0) {
      incre_char_len(1, OUT);
      fprintf(OUT, "(");

      for (int j = 0; j < cycle.size(); j++) {
        incre_char_len(1, OUT);
        fprintf(OUT, "%d", cycle[j]);
      }

      incre_char_len(1, OUT);
      fprintf(OUT, ")");
    }
  }
  fprintf(OUT, "\n");

  fclose(fin);
  fclose(fout);
  return 0;
}
