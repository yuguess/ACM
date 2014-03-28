/*
ID: yuguess1
LANG: C
TASK: money 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX 25
#define MAX_NUM 10001
#define FOUT fout

long long table[MAX][MAX_NUM];

int data[MAX];
int N = 0;
/*
int top = 0;

int digit[MAX];

void push(int c) {
    digit[top] = c;
    ++top;
    assert(top <= MAX);
}

void pop() {
    top--;
    assert(top >= 0);
}

void print_stack() {
    int i = 0;
    for (i = 0; i < top; i++) {
        printf("%d ", digit[i]);
    }
}
*/
long long money(int beg, int sum) {
  long long tmp_sum = 0;
  int i = 0;
  //printf("beg %d, sum %d, N %d\n", beg, sum, N);
  if (table[beg][sum] != 0) {
    return table[beg][sum];
  }

  if (beg == N - 1) {
    if ((sum % data[beg]) == 0) {
      //print_stack();
      //printf("%d\n", sum / data[beg]);
      //getchar();
      return 1;
    }
    return 0;
  }

  while (i * data[beg] <= sum) {
    //push(i);
    //printf("i %d, data[beg]:%d\n", i , data[beg]);
    tmp_sum += money(beg + 1, sum - i * data[beg]);
    //pop();
    i++;    
  }

  table[beg][sum] = tmp_sum;

  return tmp_sum;
}

int main () {
  long long num;
  int sum, i, j;

  FILE *fin = fopen("money.in", "r");
  FILE *fout = fopen("money.out", "w");

  for (i = 0; i < MAX; i++) {
    for (j = 0; j < MAX_NUM; j++) {
      table[i][j] = 0;
    }
  }

  fscanf(fin, "%d %d", &N, &sum);

  for (i = 0; i < N; i++) {
    fscanf(fin, "%d", &(data[N - 1 - i]));
  }

  num = money(0, sum);
  fprintf(FOUT, "%lld\n", num);

  return 0;
}
