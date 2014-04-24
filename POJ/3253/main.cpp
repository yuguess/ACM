#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <queue>
#include <functional>
using namespace std;

#define MAX_N 20010
#define MAX_L 50010

int main() {
  int n = 0, tmp = 0;
  long long sum = 0;
  priority_queue<int, vector<int>, greater<int> > q;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    scanf("%d", &tmp);
    q.push(tmp);
  }

  while (q.size() != 1) {
    int t = q.top();
    q.pop();
    int s = q.top() + t;
    q.pop();
    sum += s;
    q.push(s);
  }

  printf("%lld\n", sum);
}
