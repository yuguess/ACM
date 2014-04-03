#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <climits>
using namespace std;

#define INF -(LLONG_MAX - 1) 
#define MAX_N 100001
long long v[MAX_N];
long long c[MAX_N];

vector<int> cols;
vector<long long> s;

int main() {
  int n = 0, q = 0;
  long long maxS = 0, a = 0, b = 0;

  scanf("%d %d", &n, &q);
  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }

  for (int i = 0; i < n; i++) {
    cin >> c[i]; 
  }

  for (int i = 0; i < q; i++) {
    cin >> a >> b;

    s = vector<long long>(MAX_N, INF);

    for (int j = 0; j < n; j++) {
      long long cMax = b * v[j];

      for (int k = 0; k < cols.size(); k++) {
        if (cols[k] == c[j]) {
          cMax = max(cMax, s[cols[k]] + a * v[j]);
        } else {
          cMax = max(cMax, s[cols[k]] + b * v[j]);
        }
      }

      if (s[c[j]] == INF) {
        cols.push_back(c[j]);
        s[c[j]] = b * v[j];
      }

      s[c[j]] = max(s[c[j]], cMax);
      maxS = max(maxS, s[c[j]]);
    }

    cout << maxS << endl;
    maxS = 0;
    cols.clear();
  }
}
