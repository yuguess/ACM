#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
using namespace std;

#define MAX 110010
#define MAX_Q 50111

int d[MAX];
int bitMax = 0;
int bit[MAX];
int discrete[MAX];

struct Node {
  int low;
  int upper;
  int res;
  int idx;
  int k;
} query[MAX_Q];

struct Data {
  int pos;
  int dis;
  int val;
} data[MAX];

void update(int idx, int val) {
  while (idx <= bitMax) {
    bit[idx] += val;  
    idx += (idx & -idx);
  }
}

int findKth(int k) {
  int mb = 20, cnt = 0, ans = 0;
  //printf("mb %d, k %d\n", mb, k);

  for (int i = mb; i >= 0; i--) {
    ans += (1 << i);
    if (ans >= bitMax || cnt + bit[ans] >= k) {
      ans -= (1 << i);
    } else {
      cnt += bit[ans];
    }
  }

  return ans + 1;
}

bool cmpLow(const Node &l, const Node &r) {
  return l.low < r.low;
}

bool cmpIdx(const Node &l, const Node &r) {
  return l.idx < r.idx;
}

bool cmpVal(const Data &l, const Data &r) {
  return l.val < r.val;
}

bool cmpPos(const Data &l, const Data &r) {
  return l.pos < r.pos ;
}

int main() {
  int m = 0, n = 0, idx = 0;
  scanf("%d %d", &m, &n);
  bitMax = m;

  for (int i = 0; i < m; i++) {
    scanf("%d", &(data[i].val));
    data[i].pos = i;
  }

  sort(data, data + m, cmpVal); 
  data[0].dis = ++idx;
  discrete[idx] = data[0].val; 
  for (int i = 1; i < m; i++) {
    if (data[i].val == data[i - 1].val) {
      data[i].dis = idx;
    } else {
      data[i].dis = ++idx;
      discrete[idx] = data[i].val;
    }
  }
  sort(data, data + m, cmpPos);

  for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &(query[i].low), &(query[i].upper), &(query[i].k));
    query[i].idx = i;
  }

  //sort
  sort(query, query + n, cmpLow); 

  for (int i = query[0].low - 1; i < query[0].upper; i++) {
    update(data[i].dis, 1);
  }

  query[0].res = findKth(query[0].k);

  for (int i = 1; i < n; i++) {
    for (int j = query[i - 1].low - 1; j < query[i].low - 1; j++) {
      //printf("del %d\n", d[j]);
      update(data[j].dis, -1);
    }

    for (int j = query[i - 1].upper - 1; j >= query[i].upper; j--) {
      //printf("del %d\n", d[j]);
      update(data[j].dis, -1);
    }

    for (int j = query[i - 1].upper; j <= query[i].upper - 1; j++) {
      update(data[j].dis, 1);
    }

    query[i].res = findKth(query[i].k);
  }

  //sort
  sort(query, query + n, cmpIdx);

  for (int i = 0; i < n; i++) {
    printf("%d\n", discrete[query[i].res]);
  }
}
