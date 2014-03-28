#include <stdio.h>
#include <algorithm>
using namespace std;

#define IN stdin
#define MAX 100000

int n, q;

int c[MAX];
int v[MAX];
long long max_v[MAX] = {0};

int main() {
  int a, b;
  FILE *fin = fopen("E.in", "r");
  
  fscanf(IN, "%d %d", &n, &q);
  for (int i = 0; i < n; i++) {
    fscanf(IN, "%d", &(v[i]));
  }

  for (int i = 0; i < n; i++) {
    fscanf(IN, "%d", &(c[i]));
  }

  long long max_r = 0;

  for (int i = 0; i < q; i++) {
    fscanf(IN, "%d %d", &a, &b);
    long long la = a;
    long long lb = b;
    if (v[0] == 82725) {
      printf("a %d, b %d", a, b);
      //printf("%I64d\n", 5008451980);
      /*
      for (int p = 0; p < n; p++)
        printf("%d\n", v[p]);
      printf("\n\n");
      for (int p = 0; p < n; p++)
        printf("%d\n", c[p]);
      printf("\n\n");
      printf("%d %d\n", a, b);
      */
    }
      
    for (int k = 0; k < n; k++) {
      long long tmp1 = lb * v[k];
      max_v[k] = max((long long)0, tmp1);

      for (int j = k - 1; j >= 0; j--) {
        if (c[k] == c[j]) {

          long long tmp = la * ((long long)v[k]);
          max_v[k] = max(max_v[k], max_v[j] + tmp); 
        } else {
          long long tmp = lb * ((long long)v[k]);
          max_v[k] = max(max_v[k], max_v[j] + tmp);
        }
      }
      //printf("k %d, %d\n", k, max_v[k]);
      //getchar();
      max_r = max(max_v[k], max_r); 
    }

    printf("%I64d\n", max_r);
    max_r = 0; 
  }

}
