/*
ID: yuguess1
LANG: C
TASK: lamps
*/

/**
 * 1. the number of pressing button can be treated as even and odd
 * 2. every 6 lamps will repeat
 * 3. every 4 operation will repeat
 * 4. there are 15 patterns c41, c42, c43, c44, taking odd pressing number into
 *    account
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUTPUT fout

int pat1[4][6] = {
    {0, 0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0, 1},
    {0, 1, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 0}
    }; 

int pat2[6][6] = {
    {0, 0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0},
    {1, 0, 1, 0, 1, 0},
    {1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1}
    };

int pat_odd[7][6] = {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0, 1},
    {0, 1, 1, 0, 1, 1},
    {1, 0, 1, 0, 1, 0},
    {1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1}
    };

int pat_even[8][6] = {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0, 1},
    {0, 1, 1, 0, 1, 1},
    {1, 0, 0, 1, 0, 0},
    {1, 0, 1, 0, 1, 0},
    {1, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1}
    };

void reverse(char s[]);
void dec2bin(long decimal, char *binary);

void input(int *table, FILE *fin) {
    int i = 0, N = 0;
    while (N != -1) {
        fscanf(fin, "%d", &N);
        table[i++] = N;
    }
}
/*
void print_data(int *data) {
    int i = 0;
    do {
        fprintf(OUTPUT, "%d ", data[i]); 
    } while (data[i++] != -1);
    fprintf(OUTPUT, "\n");
}*/

void print_temp(int *result) {
    int i = 0;
    for (i = 0; i < 6; i++) {
        printf("[%d]:%d ", i, result[i]);
    }
    printf("\n");
}

int* check(int *on, int *off, int *result) {
    int i = 0, t, c;
    while ((c = on[i++]) != -1) {
        t = c % 6 - 1;
        if (result[t] == -1 || ((result[t] != -1) && (result[t] == 1))) {
            result[t] = 1;
        } else {
            //printf("t %d", t); 
            //printf("result[t] %d", result[t]);
            //printf("here");
            return NULL;
        }
    }

    //print_temp(result);
    //getchar();

    i = 0;
    while ((t = off[i++]) != -1) {
        t = t % 6 - 1;
        if (result[t] == -1|| ((result[t] != -1) && (result[t] == 0))) {
            result[t] = 0;
        } else {
            return NULL;
        }
    }

    //print_temp(result);
    //getchar();
}

int expand_result(int *pat, int N, FILE *output) {
    int count = N / 6;
    int remainder = N % 6;
    int i = 0, j = 0;

    for (i = 0; i < count; i++) {
        for (j = 0; j < 6; j++) { 
            fprintf(output, "%d", pat[j]);
        }
    }

    for (i = 0; i < remainder; i++) {
        fprintf(output, "%d", pat[i]);
    }

    fprintf(output, "\n");
}

int match_pattern(int *result, int (*pat)[6], int pat_len, 
        int N, FILE *output) {
    int i = 0, j = 0;
    for (j = 0; j < pat_len; j++) {
        for (i = 0; i < 6; i++) {
            if (result[i] == -1) {
                continue;
            } else {
                if (result[i] != pat[j][i])
                    break;
            }
        }

        if (i == 6) {
            //printf("find match pattern %d", j);
            //getchar();
            expand_result(pat[j], N, output);
        }
    }
}

int print_result(int *result, int C, int N, FILE *output) {

    if (C % 2 == 0) {
        if (C != 2) {
            //printf("match pattern even\n");
            match_pattern(result, pat_even, 8, N, output); 
        } else {
            //printf("match pattern 2\n");
            match_pattern(result, pat2, 6, N, output); 
        }
    } else {
        if (C != 1) {
            //printf("match pattern odd\n");
            match_pattern(result, pat_odd, 7, N, output);
        } else {
            //printf("match pattern 1\n");
            match_pattern(result, pat1, 4, N, output);
        }
    }
     
}

int check_result(int *result) {
    int i = 0;
    for (i = 0; i < 6; i++) {
        if (result[i] != -1) {
            return 0;
        }
    }
    return 1; 
}

int main () {
    int N, C, i;
    int on[100], off[100];
    int result[6] = {-1, -1, -1, -1, -1, -1};

    FILE *fin = fopen("lamps.in", "r");
    FILE *fout = fopen("lamps.out", "w");

    fscanf(fin, "%d", &N);
    fscanf(fin, "%d", &C);
    input(on, fin);
    input(off, fin); 

    //print_data(on);
    //print_data(off);
    
    if (check(on, off, result) == NULL) {
        fprintf(OUTPUT, "IMPOSSIBLE\n");    
        return 0;
    }

    if (C == 0) {
        if (check_result(result)) { 
            for (i = 0; i < N; i++) {
                fprintf(OUTPUT, "1");
            }
            fprintf(OUTPUT, "\n");
        } else {
            fprintf(OUTPUT, "IMPOSSIBLE\n");    
        }
        return 0;
    }

    print_result(result, C, N, OUTPUT);
    
    fclose(fin);
    fclose(fout);
}
