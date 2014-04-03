#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <climits>
#include <algorithm>
#include <assert.h>
using namespace std;

#define INF -INT_MAX 
#define MAX_N 100100

int v[MAX_N];
int c[MAX_N];
vector<long long> s;

int main() {
  int n = 0, q = 0, maxC = -1, secMaxC = -1;
  long long a = 0, b = 0;

  scanf("%d %d", &n, &q);
  for (int i = 0; i < n; i++)
    cin >> v[i];

  for (int i = 0; i < n; i++)
    cin >> c[i]; 
  

  for (int i = 0; i < q; i++) {
    cin >> a >> b;

    s = vector<long long>(MAX_N, INF);

    for (int j = 0; j < n; j++) {
      
      if (c[j] != maxC && c[j] != secMaxC) {

        if (s[c[j]] == INF) {
          if (maxC == -1) { 
            s[c[j]] = b * v[j];
            maxC = c[j];
            continue;
          }

          if (secMaxC == -1) {
            s[c[j]] = b * v[j];
            secMaxC = c[j];
          }

          s[c[j]] = max(b * v[j], s[maxC] + b * v[j]);
        } else {
          s[c[j]] = max(max(b * v[j], s[c[j]]),  
              max(s[c[j]] + a * v[j], s[maxC] + b * v[j]));
        }

        if (s[c[j]] > s[maxC]) {
          secMaxC = maxC;
          maxC = c[j];
        } else if (s[c[j]] > s[secMaxC]) {
          secMaxC = c[j];
        }


      } else if (c[j] == maxC) {

        if (secMaxC != -1)
          s[c[j]] = max(max(s[maxC], b * v[j]), 
            max(s[maxC] + a * v[j], s[secMaxC] + b * v[j]));
        else 
          s[c[j]] = max(max(s[maxC], b * v[j]), s[maxC] + a * v[j]);

      } else if (c[j] == secMaxC) {

        s[c[j]] = max(max(s[secMaxC], b * v[j]), 
            max(s[secMaxC] + a * v[j], s[maxC] + b * v[j]));

        if (s[secMaxC] > s[maxC]) {
          swap(maxC, secMaxC);
        }
      }
    }

    cout << max((long long)0, s[maxC]) << endl;

    maxC = -1;
    secMaxC = -1;
    s.clear();
  }

  return 0;
}
