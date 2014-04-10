#include <stdio.h>

int main() {
  int B[] = {4, 2, 3, 2, 2, 3, 3};
  int    ones = 0;
  int    twos = 0;
  int not_threes;
  int x;

  for (int i=0; i < 7; i++) {
   	x =  B[i];
    twos |= ones & x ;
    ones ^= x ;
    not_threes = ~(ones & twos) ;
    ones &= not_threes ;
    twos &= not_threes ;
  }

  printf("\n unique element = %d \n", ones );
 
  return 0;
}
