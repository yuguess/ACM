/*
ID: yuguess1
LANG: C
TASK: sort3
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int * data;

int swap_within_range(int index, int num, int begin, int end) {
    int temp, i;
    for (i = begin; i <= end; i++) {
        if (data[i] == num) {
            temp = data[i];
            data[i] = data[index];
            data[index] = temp;
            return 0;
        }
    }
    return 1;
}

int main () {
    int histogram[3];
    int swap_count = 0;
    int length, i;
    memset(histogram, 0, sizeof(int) * 3);

    FILE *fin = fopen("sort3.in", "r");
    FILE *fout = fopen("sort3.out", "w");

    fscanf(fin, "%d", &length);

    data = malloc(length * sizeof(int));
    for (i = 0; i < length; i++)
        fscanf(fin, "%d", &data[i]);

    for (i = 0; i < length; i++)
        histogram[data[i] - 1]++;

   /* 
    for (i = 0; i < 3; i++)
        printf("%d: %d\n", i, histogram[i]);
*/
    for (i = 0; i < histogram[0]; i++) {
        if (data[i] == 2) {
            if (swap_within_range(i, 1, histogram[0], histogram[0] + histogram[1] - 1) == 0)
                swap_count++;
            continue;
        }

        if (data[i] == 3) {
            if (swap_within_range(i, 1, histogram[0] + histogram[1], length - 1) == 0)
                swap_count++;
            continue;
        }
    }
    //for (i = 0; i < length; i++)
    //    printf("%d\n", data[i]);
  
    for (i = histogram[0]; i < histogram[0] + histogram[1]; i++) {
        //printf("second %d: %d\n", i, data[i]);
        if (data[i] == 3) {
            if (swap_within_range(i, 2, histogram[0] + histogram[1], length - 1) == 0) 
                swap_count++;
        }
    }
    /*
    for (i = 0; i < length; i++)
        printf("%d\n", data[i]);
        */
  
    for (i = 0; i < histogram[0]; i++) {
        if (data[i] != 1) {
            swap_within_range(i, 1, histogram[0], length - 1);
            swap_count++;
        }
    }
   
    for (i = histogram[0] ; i < histogram[0] + histogram[1]; i++) {
        if (data[i] == 3)
            swap_count++;
    }
    
    /*
    for (i = 0; i < length; i++)
        printf("%d\n", data[i]);
        */
    fprintf(fout, "%d\n", swap_count);
    fclose(fin);
    fclose(fout);
}
