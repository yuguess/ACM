#include <stdio.h>
#include <stdlib.h>

int main () {
    int *data = (int*)calloc(sizeof(int) * 10);
    int i;
    for (i = 0; i < 10; i++)
        printf("%d\n", data[i]);
    
}
