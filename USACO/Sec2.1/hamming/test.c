#include<stdio.h>

int flip_bit(int num, int index) {
    if (num >> index & 0x1) {
        return (num & ~(0x1 << index));
    } else {
        return (num | (0x1 << index));
    }
}

int main () {
    int num = 4;
    printf("%d\n", flip_bit(4, 0));
}
