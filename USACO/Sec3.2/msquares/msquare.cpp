/*
ID: yuguess1
TASK: msquare 
LANG: C++
*/
#include <stdio.h>
#include <string>
#include <queue>
#include <set>

using namespace std;

#define OUT fout
#define IN fin

queue<int> num;
queue<string> seq;
queue<string> ptn;
set<string> tb;

string opA(string s) {
  return string(s.rbegin(), s.rend());
}

string opB(string s) {
  string head = string(1, s[3]);
  string tail = string(1, s[4]);
  s.erase(3, 2);
  s.append(tail);
  return head.append(s);
}

string opC(string s) {
  char c1 = s[1]; 
  char c2 = s[2];
  char c5 = s[5];
  char c6 = s[6];

  s[1] = c6;
  s[2] = c1;
  s[5] = c2;
  s[6] = c5;

  return s;
}

char ops[3] = {'A', 'B', 'C'};

string (*oper[3])(string) = {opA, opB, opC};

int main() {
  int tmp;

  FILE *fin = fopen("msquare.in", "r");
  FILE *fout = fopen("msquare.out", "w");

  string t;

  for (int i = 0; i < 8; i++) {
    fscanf(IN, "%d", &tmp); 
    t += string(1, tmp + '0');
  }

  num.push(0);
  seq.push("");
  ptn.push("12345678");
  tb.insert("12345678");

  while (1) {
    int lv = num.front();
    string p = ptn.front();
    string stp = seq.front(); 

    ptn.pop();
    num.pop();
    seq.pop();

    for (int i = 0; i < 3; i++) {
      string np = (oper[i]) (p);
      
      string ns = stp + string(1, ops[i]); 
      int nl = lv + 1;
      if (p == t) {
        fprintf(OUT, "%d\n", lv);
        fprintf(OUT, "%s\n", stp.c_str());
        return 0;
      }
      if (tb.find(np) == tb.end()) {
        num.push(nl);
        seq.push(ns);
        ptn.push(np);
        tb.insert(np);     
      }
    }
  }
}
