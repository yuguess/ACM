#include <stdio.h>

int main() {
  int n = 0;
  scanf("%d", &n);
  int sum = 0;
  int tmp = 0;

  for (int i = 0; i < n; i++) {
    scanf("%d\n", &tmp);
    sum ^= tmp; 
  }
  printf("%d\n", sum ^ 0);
}
