#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

int main() {
  int a = 0, v = 0, p = 0;
  map<int, int> d;

  while (scanf("%d", &a) && a) {
    switch (a) {
    case 1:
      scanf("%d %d", &v, &p);
      d[p] = v;
      break;

    case 3:
      if (d.size() == 0) {
        printf("0\n");
      } else {
        printf("%d\n", d.begin()->second);
        d.erase(d.begin());
      }
      break;

    case 2:
      if (d.size() == 0) { 
        printf("0\n");
      } else {
        printf("%d\n", d.rbegin()->second);
        d.erase(--d.end());
      }
      break;
    }
  }
}
