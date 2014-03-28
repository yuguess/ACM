#include <stdio.h>

int number[39];
int top = 0;

void print_number() {
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

void pick_number(int *data, int N, int identical_value) {
    int i;

    if (identical_value < 0)
        return;
    if (identical_value == 0) {
        print_number();
    }

    for (i = 0; i <= N; i++) {
        push(data[i]);
        pick_number(data + i + 1, N - 1 - i, identical_value - data[i]);
        pop();
    }
    return;
}

int main () {
    int i;
    int data[7];
    for (i = 0; i < 7; i++)
        data[i] = i + 1;

    for (i = 0; i < 39; i++)
        number[i] = i;

    pick_number(data, 7, 14);
}
