 /*
ID:138_3531
LANG:C++
TASK:humble
*/


#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
using namespace std;

ifstream fin("humble.in");
ofstream fout("humble.out");
int n,k;
int a[101];
int h[100005];
int pre[101];
void input() {
    fin>>k>>n;
    for (int i=0;i<k;i++) {
        fin>>a[i];
    }
}

int main() {
    input();
    h[0]=1;
    for (int i = 1; i <= n; i++) {
      int minn=0x7FFFFFFF;
      for (int j = 0; j < k; j++)
        for (int p = pre[j]; p < i; p++) {
          printf("p %d\n", p);
          getchar();
          if (h[p] * a[j] > h[i-1]) {
              if (h[p] * a[j] < minn)
                  minn = h[p] * a[j];
              pre[j] = p;
              break;
          }
        }

      h[i]=minn;
    }
    fout<<h[n]<<endl;
    return 0;
}
