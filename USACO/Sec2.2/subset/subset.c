/*
ID: yuguess1
LANG: C
TASK: subset
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUTPUT fout

int set_sum(int N) {
    int i;
    int sum = 0;
    for (i = 0; i < N; i++) 
        sum += i + 1;
    if (sum % 2 != 0)
        return -1;
    return sum / 2;
}

int table[781][40] = {0};

void print_table(int N, int sum) {
    int i, j;

    for (j = 1; j <= sum; j++) {
        for (i = 1; i <= N; i++)
            printf("[%d][%d]:%d  ", j, i, table[j][i]); 
        printf("\n");
    }

}

int main () {
    int N, i, j, sum;

    FILE *fin = fopen("subset.in", "r");
    FILE *fout = fopen("subset.out", "w");

    fscanf(fin, "%d", &N);
    if ((sum = set_sum(N)) == -1) {
        fprintf(OUTPUT, "0\n");
        return 0;
    }

    table[0][0] = 1;

    for (i = 1; i <= N; i++) {
        for (j = 1; j <= sum; j++)
            table[j][i] = table[j][i - 1];

        for (j = i; j <= sum; j++) 
            table[j][i] = table[j][i - 1] + table[j - i][i - 1];
    }

    fprintf(OUTPUT, "%d\n", table[sum][N]);
    
    fclose(fin);
    fclose(fout);
}
