/*
ID: yuguess1
LANG: C
TASK: subset
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int number[39];
int top = 0;
int count = 0;

void print_num() {
    int i;
    for (i = 0; i < top; i++)
        printf("%d ", number[i]);
    printf("\n");
}

void push(int num) {
    number[top] = num;
    top++;
}

void pop() {
    top--;
}

int set_sum(int N) {
    int i;
    int sum = 0;
    for (i = 0; i < N; i++) 
        sum += i + 1;
    return sum / 2;
}

void print_number() {
    int i;
    for (i = 0; i < top; i++)
        printf("%d ", number[i]);
    printf("\n");
}

void pick_number(int *data, int N, int identical_value) {
    int i;

    if (identical_value < 0)
        return;
    if (identical_value == 0) {
        count++;
        print_number();
    }

    for (i = 0; i < N; i++) {
        push(data[i]);
        pick_number(data + i + 1, N - i - 1, identical_value - data[i]);
        pop();
    }

    return;
}

int main () {
    int N, i;

    FILE *fin = fopen("subset.in", "r");
    FILE *fout = fopen("subset.out", "w");

    fscanf(fin, "%d", &N);

    int *data = (int*)malloc(sizeof(int) * N);

    int identical_value = set_sum(N);
    
    //printf("%d\n", identical_value);
    if (identical_value % 2 == 0) {
        for (i = 0; i < 39; i++)
            number[i] = 0;
        for (i = 0; i < N; i++)
            data[i] = i + 1;

        pick_number(data, N, identical_value); 
        fprintf(fout, "%d\n", count / 2);
    } else {
        fprintf(fout, "0\n");
    }

    fclose(fin);
    fclose(fout);
}
