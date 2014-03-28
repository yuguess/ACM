/*
ID: yuguess1
LANG: C
TASK: numtri 
*/
#include <stdio.h>
#include <stdlib.h>

inline int max(int a, int b) {
    return a > b ? a : b;
}

int main () {
    int i, j;
    FILE *fin = fopen("numtri.in", "r");
    FILE *fout = fopen("numtri.out", "w");
    int ** data;
    int ** table;
    int bound = 0;
    
    fscanf(fin, "%d", &bound); 
    
    if ((data = (int **)malloc(bound * sizeof(int *))) == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    for (i = 0; i < bound; i++) {
        if ((data[i] = (int *)malloc(bound * sizeof(int))) == NULL) {
            fprintf(stderr, "malloc error\n");
            exit(1);
        }   
    }
    
    if ((table = (int **)malloc(bound * sizeof(int *))) == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    for (i = 0; i < bound; i++) {
        if ((table[i] = (int *)malloc(bound * sizeof(int))) == NULL) {
            fprintf(stderr, "malloc error\n");
            exit(1);
        }   
    }

    for (i = 0; i < bound; i++) {
        for (j = 0; j < bound; j++) {
            table[i][j] = 0;
        }
    }

    for (i = 0; i < bound; i++)
        for (j = 0; j < i + 1; j++) {
            fscanf(fin, "%d", &(data[i][j]));
        }
   
    if (bound == 1) {
        fprintf(fout, "%d\n", data[0][0]);
        exit(0);
    } else {
        for (i = 0; i < bound; i++)
            table[bound - 1][i] = data[bound - 1][i];

        for (i = bound - 1; i > 0; i--)
            for (j = 0; j < i; j++) {
                table[i - 1][j] = max(table[i][j], table[i][j + 1]) + data[i - 1][j]; 
            }
        
        //printf("%d\n", table[0][0]);
    }
    fprintf(fout, "%d\n", table[0][0]);

    for (i = 0; i < bound; i++) {
            free(data[i]);
            free(table[i]);
    }

    free(data);
    free(table);

    fclose(fin);
    fclose(fout);
}
