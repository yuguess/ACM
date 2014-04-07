#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <set>
using namespace std;

vector<pair<int, int> > gv;
vector<int> wv;
vector<int> cv;
vector<int> pres;
int r = 0, c = 0;

void revPrint(int idx) {
  if (idx == -1)
    return;
  revPrint(pres[idx]);
  printf(" %d", (gv[idx].first - 1) * c + gv[idx].second);
}

int main() {
  int rp = 0, cp = 0, cases = 0;
  int cs = 0, ws = 0, pre = -1, maxC = 0, maxW = 0, last = -1;

  while (scanf("%d %d", &r, &c) && r != -1) {

    while (scanf("%d %d", &rp, &cp) && rp) {

      cs = 0;
      ws = 1;
      pre = -1;

      for (int i = 0; i < gv.size(); i++) {
        if (rp < gv[i].first || cp < gv[i].second)
          continue;

        if (cv[i] > cs) { 
          cs = cv[i];
          ws = wv[i];
          pre = i; 
        } else if (cv[i] == cs) {
          ws += wv[i];
        }
      }

      wv.push_back(ws);
      cv.push_back(cs + 1);
      gv.push_back(make_pair(rp, cp));
      pres.push_back(pre);

      maxC = max(maxC, cs + 1);
    }

    maxW = 0;
    for (int i = 0; i < cv.size(); i++) {
      if (cv[i] == maxC) {
        maxW += wv[i];
        last = i;
      }
    }

    printf("CASE#%d: %d %d", ++cases, maxC, maxW);
    revPrint(last);
    printf("\n");
    maxC = 0;
    maxW = 0;
    last = -1;

    wv.clear();
    cv.clear();
    gv.clear();
    pres.clear();
  }
}
