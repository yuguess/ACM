#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <math.h>
using namespace std;

#define MAX 100100
#define OFFSET 100000

int N = 0;
int pos = 0;
int d[MAX];
int freq[MAX];
int maxR[MAX][19];
int beg[2 * MAX];
int idx[2 * MAX];
int eIdx[2 * MAX];

void rmqInit() {
  for (int i = 0; i < N; i++) {
    maxR[i][0] = i;
  }

  for (int step = 1; 1 << step <= N; step++)
    for (int j = 0; j + (1 << step) - 1 < N; j++)
      if (freq[maxR[j][step - 1]] > freq[maxR[j + (1 << (step - 1))][step - 1]]) {
        maxR[j][step] = maxR[j][step - 1]; 
      } else {
        maxR[j][step] = maxR[j + (1 << (step - 1))][step - 1];
      }
}

int rmq(int l, int u) {
  if (l > u) 
    return 0;
  int k = log2(u - l + 1);
  return max(freq[maxR[l][k]], freq[maxR[u - (1 << k) + 1][k]]);
}

int main() {
  int n = 0, q = 0, l = 0, u = 0;

  while (scanf("%d", &n) && n != 0) {
    scanf("%d", &q);

    scanf("%d", d); 
    d[0] += OFFSET;
    beg[d[0]] = 0;
    idx[d[0]] = pos;
    freq[pos]++;

    for (int i = 1; i < n; i++) {
      scanf("%d", d + i);
      d[i] += OFFSET;

      if (d[i] != d[i - 1]) {
        eIdx[d[i - 1]] = i - 1;

        pos++;
        idx[d[i]] = pos;
        beg[d[i]] = i;
        
      }
      freq[pos]++;
    }
    eIdx[d[n - 1]] = n - 1;
    N = pos + 1;

    //for (map<int, int>::iterator it = beg.begin(); 
    //    it != beg.end(); it++) {
    //  printf("beg %d:%d\n", it->first, it->second);
    //}
    //for (map<int, int>::iterator it = end.begin(); 
    //    it != end.end(); it++) {
    //  printf("end %d:%d\n", it->first, it->second);
    //}
    //for (map<int, int>::iterator it = idx.begin(); 
    //    it != idx.end(); it++) {
    //  printf("idx %d:%d\n", it->first, it->second);
    //}

    //printf("pos %d\n", pos);

    //for (int i = 0; i <= pos; i++)
      //printf("freq %d, %d\n", i, freq[i]);

    rmqInit();

    for (int i = 0; i < q; i++) {
      scanf("%d %d", &l, &u);
      l--; u--;
      if (idx[d[u]] == idx[d[l]]) {
        printf("%d\n", u - l + 1);
      } else if (idx[d[u]] - idx[d[l]] == 1) {
        printf("%d\n", max(eIdx[d[l]] - l + 1, u - beg[d[u]] + 1));
      } else {
        //printf("low %d\n", end[d[l]] - l + 1);
        //printf("upper %d\n", u - beg[d[u]] + 1);
        //printf("rmq %d\n", rmq(idx[d[l]] + 1, idx[d[u]] - 1));

        printf("%d\n", max(rmq(idx[d[l]] + 1, idx[d[u]] - 1), 
              max(eIdx[d[l]] - l + 1, u - beg[d[u]] + 1)));
      }
    }

    memset(freq, 0, sizeof(int) * (pos + 1));
    pos = 0;
  }
}
