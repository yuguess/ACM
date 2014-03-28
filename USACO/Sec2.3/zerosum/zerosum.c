/*
ID: yuguess1
LANG: C
TASK: zerosum
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define OUTPUT fout

#define MAX 9
#define LEN 1000

typedef struct {
  int radix_sum;
  char array[MAX]; 
} Result;

char sym_stack[MAX];
int top = 0;

Result to_sort[LEN];
int idx = 0;

int numcat(int a, int b) {
  char array[MAX + 10];

  sprintf(array, "%d%d", a, b);
  return atoi(array);
}

void print_stack() {
    int i = 0;
    for (i = 0; i < top; i++) {
        printf("%c", sym_stack[top - 1 - i]);
    }
    printf("\n");
}

void push(char c) {
    sym_stack[top] = c;
    ++top;
    assert(top <= MAX);
}

void pop() {
    top--;
    assert(top >= 0);
}

int store() {
  int i;
  char c;
  int rd_sum = 0;

  for (i = 0; i < top; i++) {  
    c = sym_stack[top - 1 - i];
    to_sort[idx].array[i] = c; 
    if (c == ' ') {
      rd_sum = rd_sum * 10 + 1;   
    }

    if (c == '+') {
      rd_sum = rd_sum * 10 + 2;
    }

    if (c == '-') {
      rd_sum = rd_sum * 10 + 3;
    }
  }
  
  to_sort[idx].radix_sum = rd_sum;
  idx++;
  assert(idx != LEN);
}

void sub_sum(int *data, int end, int sum) {
  if (end == 0) {
    if (data[end] == sum) {
      store();
    }
    return;
  }
  int array[MAX];
  int i = 0;
  for (i = 0; i < end; i++) {
    array[i] = i + 1;
  }
  array[end - 1] = numcat(data[end - 1], data[end]);

  push(' ');
  sub_sum(array, end - 1, sum);
  pop();

  push('+');
  sub_sum(data, end - 1, sum - data[end]);
  pop();

  push('-');
  sub_sum(data, end - 1, sum + data[end]);
  pop();

  return;
}

int compare(const void*t1, const void *t2) {
  return (((Result*)t1)->radix_sum - ((Result*)t2)->radix_sum);
}

int main() {
  int data[MAX];
  int length;

  FILE *fin = fopen("zerosum.in", "r");
  FILE *fout = fopen("zerosum.out", "w");

  fscanf(fin, "%d", &length);

  int i, j;
  for (i = 0; i < MAX; i++) {
    data[i] = i + 1;
  }

  sub_sum(data, length - 1, 0);
  qsort(to_sort, idx, sizeof(Result), compare);

  for (i = 0; i < idx; i++) {
    for (j = 0; j < length - 1; j++) {
      fprintf(OUTPUT, "%d", j + 1);
      fprintf(OUTPUT, "%c", to_sort[i].array[j]);
    }
    fprintf(OUTPUT, "%d", length);
    fprintf(OUTPUT, "\n");
  }

  return 0;
}
