#include <stdio.h>
using namespace std;

void func() {
  static int i = 0;
  i++;
  printf("i %d\n", i);
}

int main() {
  func();
  func();
}
