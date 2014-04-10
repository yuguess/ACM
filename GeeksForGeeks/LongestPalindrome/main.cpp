#include <stdio.h>

#define MAX 10010

char s[MAX];
bool a[MAX][MAX];

int main() {

  int n = strlen(s);
  int odd = -1;
  int even = 0;
  int maxL = 0;

  while (scanf("%s", s) && strcmp(s, "END")) {
    
    int n = strlen(s);

    //for (int i = 0; i < n; i++) {
    //  if ((i - (odd + 1) >= 0) && s[i - (odd + 1)] == s[i])
    //    odd += 2;
    //  else 
    //    odd = 1;
    // 

    //  if ((i - (even + 1)) && s[i - (even + 1)] == s[i])
    //    even += 2;
    //  else
    //    even = 0;

    //  maxL = (maxL, max(odd, even)); 
    //}
    //odd = -1;
  }
}
