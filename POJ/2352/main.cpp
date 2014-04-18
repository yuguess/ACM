#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>

using namespace std;

#define MAX 15010 
#define MAX_R 32010

int MAX_V = 0;

int level[MAX];
int bit[MAX_R];
int d[MAX];

int read(int idx) {
  int sum = 0; 
  while (idx) {
    sum += bit[idx];
    idx -= (idx & -idx);
  }

  return sum;
}

void update(int idx, int val) {
  while (idx <= MAX_V) {
    bit[idx] += val;  
    idx += (idx & -idx); 
  }
}

int main() {
  int x = 0, y = 0, N = 0;

  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    scanf("%d %d", &x, &y);
    d[i] = x + 1;
    MAX_V = max(MAX_V, d[i]);
  }

  for (int i = 0; i < N; i++) {
    //printf("%d, %d, level %d\n", x, y, l);
    level[read(d[i])]++;
    update(d[i], 1);
  }

  for (int i = 0; i < N; i++) {
    printf("%d\n", level[i]);
  }
}
