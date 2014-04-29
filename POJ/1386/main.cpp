#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 1021
#define MAX_L 27

int ind[MAX_L];
int outd[MAX_L];
int r[MAX_L];
int sz[MAX_L];
int unique[MAX_L];
int N = 0;

bool isConnect(int N) {
  for (int i = 0; i < MAX_L; i++) {
    if (sz[i] == N) {
      return true;
    }
  }

  return false;
}

bool isEuler() {
  int oddNum = 0;
  int a = 0, b = 0;

  for (int i = 0; i < MAX_L; i++) {
    if (ind[i] != outd[i]) {
      if (oddNum == 2)
        return false;
      oddNum++;
      if ((ind[i] - outd[i]) == 1) {
        a++;
      } else if ((outd[i] - ind[i]) == 1) {
        b++;
      } else {
        return false;
      }
    }
  }

  if ((a == 0 && b == 0) || (a== 1 && b == 1))
    return true;
  else
    return false; 
}

int root(int i) {
  if (i == r[i])
    return i;

  return r[i] = root(r[i]);
}

int unite(int i, int j) {
  int ir = root(i);
  int jr = root(j);

  if (ir != jr) {
    if (sz[ir] > sz[jr]) {
        r[jr] = r[ir];
        sz[ir] += sz[jr];
    } else {
        r[ir] = r[jr];
        sz[jr] += sz[ir];
    }
  }
}

void uniNum(int i) {
  if (unique[i] == 0) {
    N++;
    unique[i] = 1;
  }
}

int main() {
  int nc = 0, n = 0, bi = 0, ei = 0;
  char s[MAX];

  scanf("%d", &nc);
  while (nc--) {

    for (int i = 0; i < MAX_L; i++) {
      outd[i] = 0;
      ind[i] = 0;
      r[i] = i;
      sz[i] = 1;
      unique[i] = 0;
    }

    scanf("%d", &n);

    while (n--) {
      scanf("%s", s); 
      bi = s[0] - 'a';
      ei = s[strlen(s) - 1] - 'a';
      ind[ei]++;
      outd[bi]++;
      unite(bi, ei);
      uniNum(bi);
      uniNum(ei);
    }

    if (isConnect(N) && isEuler()) {
      printf("Ordering is possible.\n");
    } else {
      //printf("%d %d\n", isConnect(N), isEuler());
      printf("The door cannot be opened.\n");
    }

    N = 0;
  }
}
