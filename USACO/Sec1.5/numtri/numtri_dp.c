/*
ID: yuguess1
LANG: C
TASK: numtri 
*/
#include <stdio.h>
#include <stdlib.h>

int **table;

inline int max(int a, int b) {
    return a > b ? a : b;
}

int maxValue(int startRow, int startCol, int ** data, int bound) {
    int maxLowLevelVal = 0;
    int leftVal = 0;
    int rightVal = 0;
    int val = 0;

    if (startCol < 0 || startCol > startRow || startRow > (bound - 1)) 
        return 0;

    if (table[startRow][startCol] != 0) {
        return table[startRow][startCol];
    } else {
        printf("row %d\n", startRow);
        leftVal = maxValue(startRow + 1, startCol, data, bound);
        rightVal = maxValue(startRow + 1, startCol +1, data, bound);
        maxLowLevelVal = max(leftVal, rightVal);
        table[startRow][startCol] = data[startRow][startCol] + maxLowLevelVal;
        return table[startRow][startCol];
    }
}

int main () {
    int i, j;
    int bound = 0;
    int **data;

    FILE *fin = fopen("numtri.in", "r");
    FILE *fout = fopen("numtri.out", "w");
    
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

    int val = maxValue(0, 0, data, bound);


    for (i = 0; i < bound; i++) {
        free(data[i]);
        free(table[i]);
    }

    fprintf(fout, "%d\n", val);

    free(data);
    free(table);

    fclose(fin);
    fclose(fout);
}
