#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

int main() {
  int N = 0, tmp = 0;

  vector<int> v;
  v.push_back(-1);

  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d", &tmp);

    for (int j = v.size() - 1; j >= 0; j--) {
      if (tmp > v[j]) {
        if (j + 1 > v.size() - 1) {
          v.push_back(tmp);
        } else {
          v[j + 1] = min(v[j + 1], tmp); 
        }
      }
    }
  }

  //for (int i = 0; i < v.size(); i++)  {
  //  printf("%d -> %d\n", i, v[i]);
  //}

  printf("%d\n", v.size() - 1);
}
