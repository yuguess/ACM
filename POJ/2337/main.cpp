#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <deque>
using namespace std;

#define MAX_W 25
#define MAX_L 28

int outd[MAX_L];
int ind[MAX_L];

int nw;
deque<string> path;
vector<deque<string> > strs(MAX_L);

bool euler(int idx) {
  if (nw == path.size())
    return true;
  if (strs[idx].size() == 0)  
    return false;

  for (int i = 0; i < strs[idx].size(); i++) {
    string s = strs[idx][0];
    strs[idx].pop_front();
    path.push_back(s);

    if (euler(s[s.size() - 1] - 'a'))
      return true;

    strs[idx].push_back(s);
    path.pop_back();
  }

  return false;
}

int main() {
  int nc = 0, be = -1;
  int oddNum = 0;
  char st[MAX_W];

  scanf("%d", &nc);
  while (nc--) {
    scanf("%d", &nw);

    for (int i = 0; i < nw; i++) {
      scanf("%s", st);
      outd[st[0] - 'a']++;
      ind[st[strlen(st) - 1] - 'a']++;
      strs[st[0] - 'a'].push_back(st);
    }

    for (int i = 0; i < MAX_L; i++) {
      if (strs[i].size() != 0) {
        sort(strs[i].begin(), strs[i].end());
      }
    }

    for (int i = 0; i < MAX_L; i++) {
      if (ind[i] != outd[i]) {
        oddNum++;
        if (outd[i] - ind[i] == 1) {
          be = i; 
        } else if (ind[i] - outd[i] != 1) {
          oddNum = 1;
          break;
        }
      }
    }

    if (oddNum != 2 && oddNum != 0) {
      printf("***\n");
    } else {
      if (oddNum == 0) {
        for (int i = 0; i < MAX_L; i++) {
          if (strs[i].size() != 0) {
            be = i;
            break;
          }
        }
      }

      if (euler(be)) {
        printf("%s", path[0].c_str());
        for (int i = 1; i < path.size(); i++) {
          printf(".%s", path[i].c_str());
        }
        printf("\n");
      } else {
        printf("***\n");
      }
    }

    for (int i = 0; i < MAX_L; i++)
      strs[i].clear();
    
    memset(ind, 0, sizeof(int) * MAX_L);
    memset(outd, 0, sizeof(int) * MAX_L);

    path.clear();
    oddNum = 0;
    be = -1;
  }
}
