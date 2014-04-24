#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX_W 25



int main() {
  int nc = 0, nw = 0;
  char st[MAX_W];

  vector<vector<string> > strs;

  scanf("%d", &nc);
  while (nc--) {
    scanf("%d", &nw);
    while (nw--) {
      scanf("%s", st);
      outd[st[strlen(st) - 1] - 'a']++;
      st[0] - 'a'
    }
  }
}
