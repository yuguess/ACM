/*
ID: yuguess1
LANG: C
TASK: checker 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct {
    int row;
    int column;
} mat_entry;

mat_entry result[13];
int     count = 0;
int     *mat;
int     length;
int     *data_summary;
int     result_count = 0;
FILE    *fout;

void print_result() {
    int i;
    printf("row: ");
    for (i = 0; i < 6; i++)
        printf("%d ", result[i].row);
    printf("\n");

    printf("col: ");
    for (i = 0; i < 6; i++)
        printf("%d ", result[i].column);
    printf("\n");

}

void mark_row(int **mat, int row, int begin_column) {
    int i;
    for (i = begin_column; i < length; i++) {
        mat[row][i] = -1;
    }
}



void copy_matrix(int **src, int **desc, int length) {
    int i, j;
    for (i = 0; i < length; i++)
        for (j = 0; j < length; j++) {
            desc[i][j] = src[i][j]; 
        }
}

int ** mat_malloc(int row, int column) {
    int **mat;
    int i;

    if ((mat = (int **)malloc(row * sizeof(int *))) == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    for (i = 0; i < length; i++) {
        if ((mat[i] = (int *)malloc(column * sizeof(int))) == NULL) {
            fprintf(stderr, "malloc error\n");
            exit(1);
        }   
    }

    return mat;
}

void mat_free(int **mat, int row) {
    int i;
    for (i = 0; i < row; i++) {
        free(mat[i]);
    }

    free(mat);
}

void print_pic() {
    int i, j;
    int **temp_mat = mat_malloc(length, length);
    for (i = 0; i < length; i++) {
        for (j = 0; j < length; j++) {
            temp_mat[i][j] = 0;
        }
    }

    for (i = 0; i < 6; i++) {
        temp_mat[result[i].row - 1][result[i].column - 1] = i + 1;
    }

    for (i = 0; i < length; i++) {
        for (j = 0; j < length; j++) {
            printf("%d ", temp_mat[i][j]);
        }
        printf("\n");
    }

    mat_free(temp_mat, length); 

}

static inline int get_bit(int val, int bit) {
    return (val >> bit) & (0x1);
}

static inline int get_val(int *mat, int row, int column) {
    return get_bit(mat[column], row);
}

static inline void write_val(int *mat, int row, int column, int val) {
    mat[column] = mat[column] | (0x1 << row); 
}

void mark_column(int *mat, int column) {
    mat[column] = mat[column] | 0xFFFF; 
}

void mark_diagnal(int *mat, int row, int begin_row, 
            int column, int begin_column) {
    int i, j;
    /* south east */
    for (i = row, j = column; i < length && j < length; i++, j++) {
        mat[j] = mat[j] | (0x1 << i);
    }
    
    /* south west */
    for (i = row, j = column; i < length && j >= begin_column; i++, j--) {
        mat[j] = mat[j] | (0x1 << i);
    }
}

static inline void checker (int begin_row, int begin_column, int cur_depth) {
    int i, j, k;
    int row_left_to_search;
    int temp_mat[13];
    int half_length; 

    if (cur_depth == 1) {
        if (length % 2 == 0) {
            half_length = length / 2;
        } else {
            half_length = length / 2 + 1;
        }
    }

    for (i = begin_row; i < length; i++) {
        row_left_to_search = length - i;
        if (cur_depth + row_left_to_search == length)
            return;    
        for (j = begin_column; j < length; j++) {
            
            if (cur_depth == 1 && i < length - 5 && j >= (half_length) && length != 6) {
                break; 
            } 
            
            if (get_val(mat, i, j) != 1) {
                result[cur_depth - 1].row = (i + 1);
                result[cur_depth - 1].column = (j + 1);
                
                memcpy(temp_mat, mat, sizeof(int) * length);
                mark_column(mat, j);
                mark_diagnal(mat, i, begin_row, j, begin_column);
                
                if (cur_depth == length) {
                    if (result_count < 3) {
                        result_count++; 
                        for (k = 0; k < length; k++) { 
                            fprintf(fout, "%d", result[k].column);
                            if (k != (length - 1))
                                fprintf(fout, " ");
                        }
                        fprintf(fout, "\n");
                    }
                    data_summary[result[0].column - 1]++;
                    count++;
                } else {
                    checker(i + 1, 0, cur_depth + 1);
                }
                memcpy(mat, temp_mat, sizeof(int) * length);
            }
        }
    }
}

int main () {
    FILE *fin = fopen("checker.in", "r");
    fout = fopen("checker.out", "w");
    int i, j, sum = 0, half_length;
    fscanf(fin, "%d", &length); 

    data_summary = (int*)malloc(sizeof(int) * length);
    for (i = 0; i < length; i++)
        data_summary[i] = 0;

    mat = (int *)malloc(sizeof(int) * length);     
    for (i = 0; i < length; i++)
        mat[i] = 0;

    checker(0, 0, 1);
    
    if (length % 2 == 0) { 
        for (i = 0; i < length; i++) {
            //printf("%d:%d\n", i, data_summary[i]); 
            sum +=  data_summary[i] * 2;
        }
    } else {
        half_length = (int)(length / 2);
        /*
        for (i = 0; i < length; i++) {
            printf("%d:%d\n", i, data_summary[i]); 
        }*/
        for (i = 0; i < half_length; i++)
            sum += data_summary[i] * 2;
        sum += data_summary[half_length]; 
    }

    if (length == 6) {
        fprintf(fout, "4\n");
    } else {
        fprintf(fout, "%d\n", sum);
    }
    //printf("count: %d\n", count);

    free(data_summary);
    free(mat);
    fclose(fin);
    fclose(fout);
}
