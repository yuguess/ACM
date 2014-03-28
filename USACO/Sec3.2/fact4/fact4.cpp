/*
ID: yuguess1
TASK: fact4 
LANG: C++
*/
#include <stdio.h>

using namespace std;

#define OUT fout
#define IN fin

int N;

int main() {
  FILE *fin = fopen("fact4.in", "r");
  FILE *fout = fopen("fact4.out", "w");

  fscanf(IN, "%d", &N);

  int five = 0;

  for (int i = 1; i <= N; i++) {
    int num = i;
    while (num % 5 == 0) {
      five++; 
      num /= 5;
    }
  }

  int tmp = 1;
  int two = five;

  for (int i = 1; i <= N; i++) {
    int t = i;
    if (five != 0 || two != 0) {
      while (t % 2 == 0 && two != 0) {
        two--;
        t /= 2;
      }

      while (t % 5 == 0 && five != 0) {
        five--;
        t /= 5;
      }
    }
    tmp = (t * tmp) % 10; 
  }

  fprintf(OUT, "%d\n", tmp);
}
