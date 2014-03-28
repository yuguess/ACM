#include <stdio.h>

int stack[6];
int top = 0;
int count = 0;
void print_stack() {
    int i;
    for (i = 0; i < top; i++) {
        printf("%d ", stack[i]);
    }
}

void push(int num) {
    stack[top] = num;
    top++;
}

void pop() {
    top--;
}

void permutation(int *data, int data_size, int pick_size) {
    
    int i;
    if (pick_size == 1) {
        for (i = 0; i < data_size; i++) {
            push(data[i]);
            print_stack();
            printf("\n");
            pop();
            count++;
        }
        return;
    }
    for (i = 0; i <= data_size - pick_size; i++) {
        push(data[i]);
        permutation(data + i + 1, data_size - i - 1, pick_size - 1); 
        pop();
    }
}

int main () {
    int i;
    int temp[6] = {1, 2, 3, 4, 5, 6};
    permutation(temp, 6, 4);
    printf("count:%d\n", count);
}
