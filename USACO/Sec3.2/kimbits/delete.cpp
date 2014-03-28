#include <stdio.h>
using namespace std;

unsigned onebits(unsigned n) {
  unsigned num = 0;
  while (n) {
    num++;
    n &= (n - 1);
  }
  return num;
}

void bprintf(unsigned n, int k) {
  if (k == 0) {
    return;
  }
  
  if (n & 1) {
    bprintf(n >> 1, k - 1); 
    printf("1");
  } else {
    bprintf(n >> 1, k - 1);
    printf("0");
  }
}

int main() {
  bprintf(123134234, 28);
  printf("\n");
}
