/*
ID: yuguess1
LANG: C
TASK: hamming 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sequence[8];
int top = 0;

void push(int num) {
    sequence[top] = num;
    top++;
}

void pop() {
    top--;
}

int flip_bit(int num, int index) {
    if (num >> index & 0x1) {
        return (num & ~(0x1 << index));
    } else {
        return (num | (0x1 << index));
    }
}

int reverse_bit(int num) {
    int i;
    for (i = 0; i < top; i++)
        num = flip_bit(num, sequence[i]); 

    return num;
}

void generate_sequence(int *temp, int temp_size, int pick_size, int num, int *data) {
    
    int i, j;
    int distance_num;
    if (pick_size == 1) {
        for (i = 0; i < temp_size; i++) {
            push(temp[i]);
            distance_num = reverse_bit(num);
            data[distance_num] = 1;
            pop();
        }
        return;
    }
    for (i = 0; i <= temp_size - pick_size; i++) {
        push(temp[i]);
        generate_sequence(temp + i + 1, temp_size - i - 1, pick_size - 1, num, data); 
        pop();
    }
}

void delete_within_distance(int *data, int num, int B, int D) {
    int *temp = (int*)malloc(sizeof(int) * B);
    int i;
    for (i = 0; i < B; i++)
        temp[i] = i;

    for (i = 1; i < D; i++) {
        generate_sequence(temp, B, i, num, data);
    }

    free(temp);
    return;
}

int main () {
    int N, B, D;

    FILE *fin = fopen("hamming.in", "r");
    FILE *fout = fopen("hamming.out", "w");

    fscanf(fin, "%d", &N);
    fscanf(fin, "%d", &B);
    fscanf(fin, "%d", &D);

    int num[256];
    int i, j = 0;
    int count = 0;

    for (i = 0; i < 256; i++) {
        num[i] = 0;
    }

    for (i = 0; i < 256; i++) {
        if (num[i] == 0) {
            delete_within_distance(num, i, B, D); 
            count++;
            if (count == N) {
                fprintf(fout, "%d\n", i);
                break;
            }

            if ((count % 10 == 0)) {
                fprintf(fout, "%d\n", i);
            } else {
                fprintf(fout, "%d ", i);
            }
            
        }
    }

    fclose(fin);
    fclose(fout);
}
