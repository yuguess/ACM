#include <stdio.h>
int roman2num(char c) {
    switch(c) {
        case 'I': return 1;
        case 'V': return 5;
    }
}

int main () {
    printf("%d\n", roman2num('I'));    
}
