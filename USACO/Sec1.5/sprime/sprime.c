/*
ID: yuguess1
LANG: C
TASK: sprime 
*/
#include <stdio.h>
#include <math.h>

static int one_digit_prime[4] = {2, 3, 5, 7}; 
static int add_prime[4] = {1, 3, 7, 9};
static int length;

int is_prime(int n) {
    int i;
    int limit = sqrt(n) + 1;
    int count = 0;
    for (i = 3 ; i < limit; i+=2) {
        if (n % i == 0) {
            return 0; 
        }
    }
    return 1; 
}

void gen_prime(int begin_num, int cur_length, FILE *fout) {
    int i;
    int temp;
    for (i = 0; i < 4; i++) {
        temp = begin_num * 10 + add_prime[i];
        if (is_prime(temp)) {
            if (cur_length == length) {
                fprintf(fout, "%d\n", temp);    
            } else {
                gen_prime(temp, cur_length + 1, fout); 
            }
        } 
    }
}

int main () {
    FILE *fin = fopen("sprime.in", "r");
    FILE *fout = fopen("sprime.out", "w");

    int i;

    fscanf(fin, "%d", &length);

    if (length == 1) {
        for (i = 0; i < 4; i++)
            fprintf(fout, "%d\n", one_digit_prime[i]);
    } else {
        for (i = 0; i < 4; i++)
            gen_prime(one_digit_prime[i], 2, fout);  
    }

    fclose(fin);
    fclose(fout);
}
