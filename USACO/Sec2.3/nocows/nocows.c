/*
ID: yuguess1
LANG: C
TASK: nocows
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define OUTPUT fout
#define MOD 9901
#define MAX_NODE 200
#define MAX_LEVEL 100

int table[MAX_NODE][MAX_LEVEL];

int under_height(int N, int K) {
  int i;
  int tmp_sum = 0;

  for (i = 1; i <= K; i++) {
    tmp_sum += pedigrees(N, i) % MOD; 
  }

  return tmp_sum % MOD;
}

void init_data() {
  int i, j;
  for (i = 0; i < MAX_NODE; i++)
    for (j = 0; j < MAX_LEVEL; j++)
      table[i][j] = -1;

  for (i = 0; i < MAX_LEVEL; i++)
    table[1][i] = 0;
  table[1][1] = 1;

  for (i = 0; i < MAX_LEVEL; i++) 
    table[3][i] = 0;
  table[3][2] = 1;

  for (i = 0; i < MAX_LEVEL; i++) 
    table[5][i] = 0;
  table[5][3] = 2;
}

int min_level(int N) {
    if (N <= 0) 
        return 0;

    if (N == 1)
        return 1;
    else 
        return ceil(log(N) / log(2));
}

int max_level(int N) {
    if (N <= 0)
        return 0;
    else
        return (N + 1) / 2;
}

int pedigrees(int N, int K) {
  //printf("try N %d, K %d\n", N, K);

  if (table[N][K] != -1) { 
    return table[N][K];
  }

  if (K < min_level(N) || K > max_level(N)) {
    table[N][K] = 0;
    return 0;
  }
  
  long long sum = 0, i;
  int half = (N - 1) / 2;
  if (half % 2 != 0) { 
    int half_high = pedigrees(half, K - 1);
    int half_low = under_height(half, K - 2) % MOD;

    sum += (half_high * half_high) % MOD;
    sum += (half_high * half_low * 2) % MOD;
  } else {
    half--;
  }

  for (i = half + 2; i <= N - 2; i += 2) {
    int less = N - 1 - i;
    int more_high = pedigrees(i, K - 1);
    int less_low = under_height(less, K - 2) % MOD;
    int less_high = pedigrees(less, K - 1);
    int more_low = under_height(i, K - 2) % MOD;

    //printf("more high, N %d, K %d, %d\n", i, K - 1, more_high);
    //printf("less low, N %d, K 1~%d, %d\n", less, K - 2, less_low);
    //printf("\n");
    //printf("less high, N %d, K %d, %d\n", less, K - 1, less_high);
    //printf("more low, N %d, K 1~%d, %d\n", i, K - 2, more_low);
    
    sum += ((more_high * less_low) % MOD) * 2 % MOD  + 
           ((less_high * more_low) % MOD) * 2 % MOD + 
           ((more_high * less_high) % MOD) * 2 % MOD;
    sum %= MOD;
  }

  table[N][K] = sum % MOD; 
  printf("solve N %d, K %d, %d \n", N, K, table[N][K]);
  return (sum % MOD);
}

int main () {
  int N, K, num;
  FILE *fin = fopen("nocows.in", "r");
  FILE *fout = fopen("nocows.out", "w");

  fscanf(fin, "%d", &N); 
  fscanf(fin, "%d", &K); 

  init_data();
  if (N % 2 == 0) {
    num = 0;
  } else {
    num = pedigrees(N, K);
  }
  fprintf(OUTPUT, "%d\n", num % MOD);  

  fclose(fin);
  fclose(fout);
}
