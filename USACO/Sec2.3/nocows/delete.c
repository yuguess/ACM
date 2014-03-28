#include <stdio.h>
#include <math.h>

int min_level(int N) {
    return ceil(log(N) / log(2));
}

int main () {
    int level = min_level(9);
    printf("level %d\n", level);
}
