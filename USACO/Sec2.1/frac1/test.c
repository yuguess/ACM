#include <stdio.h>
int gcd(int a, int b) {
    int c;
    while (1) {
  	    c = a % b;
        if (c == 0)
          return b;
        a = b;
        b = c;
    }
}

int main () {
    int a = 1;
    int b = 10;
    char temp[100];
    sprintf(temp, "%d/%d", a, b);
    printf("%s\n", temp);
}
