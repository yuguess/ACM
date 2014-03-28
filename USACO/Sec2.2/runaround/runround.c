/*
ID: yuguess1
LANG: C
TASK: runround 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define OUTPUT fout
//#define OUTPUT stdout
#define DIGIT 10

int digits[DIGIT] = {0};
int digit_num = 0;
int temp[10] = {0};
int digit_temp[10] = {0};

void print_digit(FILE *out) {
    int i = 0;

    if (digit_num == 0) {
        fprintf(out, "0\n");
    } else {
        for (i = digit_num - 1; i >= 0; i--) {
            fprintf(out, "%d", digits[i]);
        }
        fprintf(out, "\n");
        //fprintf("\tdigit: %d\n", digit_num);
    }
}

int store_digit(int num) {
    int i = 0;
    int digit = 0;

    while (num != 0) {
        digit = num % DIGIT;
        digits[i++] = digit;
        num = num / DIGIT;

        digit_num++;
    }

    return 0;
}

int digit_increment() {
    int i = 0;

    digits[i]++;
    while (digits[i] == 10) { 
        digits[i] = 0;
        i++;
        assert(i < 10);
        digits[i]++;
    }
    
    if (i == digit_num) {
        digit_num++;
    }
}

int pre_validate_num() {
    int i = 0;
    memset(temp, 0, sizeof(int) * 10);

    for (i = 0; i < digit_num; i++) {
        if (digits[i] == 0 || temp[digits[i]] != 0) {
            return -1;
        } else {
            temp[digits[i]]++;
        }
    }

    return 0;
}

int post_validate_num() {
    int i = 0;

    for (i = 0; i < digit_num; i++) {
        if (digit_temp[i] == 0) 
            return -1;
    }

    return 0;
}

int validate_num() {
    int i = 0;

    if (pre_validate_num() != 0) {
        return 0;
    } 

    memset(digit_temp, 0, sizeof(int) * 10);

    int num  = digit_num - 1;
    for (i = 0; i < digit_num; i++) {
        digit_temp[num] = 1;
        //printf("before num:%d\n", num);
        num = num - digits[num] % digit_num;
        //printf("after num:%d\n", num);
        if (num < 0) {
            num += digit_num;
        }
    }

    if (num == (digit_num - 1)) {
        if (post_validate_num() != 0) {
            return 0;
        }
        return 1;
    } else {
        return 0;
    }
    

    
}

int main () {
    int M;
    FILE *fin = fopen("runround.in", "r");
    FILE *fout = fopen("runround.out", "w");

    fscanf(fin, "%d", &M);

    if (store_digit(M + 1) != 0) {
        fprintf(OUTPUT, "input num error");   
    }

    while (!validate_num()) {
        digit_increment();
    }

    print_digit(OUTPUT);

    fclose(fin);
    fclose(fout);
}
