/*
ID: yuguess1
TASK: contact 
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include <map>
#include <iostream>
#include <vector>

using namespace std;

#define OUT fout
#define IN fin
#define MAX_S 200000

int A, B, N;
char buf[MAX_S];

class Entry {
public:
  Entry(string args, int argf):s(args), fre(argf){}
  string s;
  int fre;
};

bool cmp(const Entry &e1, const Entry &e2) {
  if (e1.fre == e2.fre) {
    if (e1.s.length() != e2.s.length())
      return e1.s.length() < e2.s.length();
    else 
      if (e1.s.compare(e2.s) < 0)
        return true;
      else
        return false;
  } else {
    return e1.fre > e2.fre;
  }
}

int main () {
  char c;
  int l = 0;

  map<string, int> m; 
  
  FILE *fin = fopen("contact.in", "r");
  FILE *fout = fopen("contact.out", "w");

  fscanf(fin, "%d %d %d", &A, &B, &N);

  while (fscanf(IN, "%c", &c) != EOF) {
    if (c == '\n')
      continue;
    buf[l++] = c; 
  }

  string s;
  for (int i = 0; i < l; i++) {
    if (s.length() == B) {
      s.erase(0, 1);
    }
    s.push_back(buf[i]);

    for (int j = A; j <= B && s.length() >= j; j++) {
      string tmp = s.substr(s.length() - j, j);
      if (m.find(tmp) == m.end()) {
        m[tmp] = 0;
      } else {
        m[tmp]++;
      }
    }
  }

  vector<Entry> v;

  for (map<string, int>::iterator it = m.begin(); it != m.end(); it++) {
    //cout << it->first << "=>" << it->second << endl;
    v.push_back(Entry(it->first, it->second));
  }

  sort(v.begin(), v.end(), cmp);
  int pfre = 0;
  int num = 0;
  int pos = 0;

  for (int i = 0; i < v.size();) {
    fprintf(OUT, "%d\n", v[i].fre + 1);
    fprintf(OUT, "%s", v[i].s.c_str());

    pos += v[i].s.length();

    pfre = v[i].fre;
    i++;
    while (pfre == v[i].fre) {
      if (pos + v[i].s.length() > 80) {
        fprintf(OUT, "\n%s", v[i].s.c_str()); 
        pos = v[i].s.length();
      } else {
        fprintf(OUT, " %s", v[i].s.c_str());
        pos += v[i].s.length();
      }
      i++;
    }
    pos = 0;
    num++;
    fprintf(OUT, "\n");
    if (num == N)
      break;
    /*
    if (v[i].fre != pfre) {
      if (i != 0) 
        fprintf(OUT, "\n");
      fprintf(OUT, "%d\n%s", v[i].fre + 1, v[i].s.c_str());
      num++;
    } else {
      fprintf(OUT, " %s", v[i].s.c_str());
    }
    pfre = v[i].fre;
    */
  }

  //fprintf(OUT, "\n");

  fclose(fin);
  fclose(fout);
}
