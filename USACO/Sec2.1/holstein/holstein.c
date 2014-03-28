/*
ID: yuguess1
LANG: C
TASK: holstein
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int find_critical_require(int **feed, int *require, 
        int vitamin_count, int feed_count) {
    int *max;
    int i, j;
    max = (int*)malloc(sizeof(int) * vitamin_count);
    memset(max, 0, sizeof(int) * vitamin_count);
    for (j = 0; j < feed_count; j++) { 
        for (i = 0; i < vitamin_count; i++) {
            if (feed[j][i] > max[i]) {
                max[i] = feed[j][i];
            }
        }
    }

    float max_ratio = 0.0;
    float temp = 0.0;
    int critical_require;
    for (i = 0; i < vitamin_count; i++) {
        temp = (float)require[i] / (float)max[i];
        if (temp > max_ratio) {
            max_ratio = temp;     
            critical_require = i; 
        }
    }

    return critical_require;
}

int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int initial_minimum_require(int **feed, int *vitamin, 
        int critical_require, int feed_count) {
    int *temp = (int*)malloc(sizeof(int) * feed_count);
    int i;
    for (i = 0; i < feed_count; i++) 
        temp[i] = feed[i][critical_require];

    qsort(temp, feed_count, sizeof(int), compare);

    int sum = 0;

    for (i = 0; sum < vitamin[critical_require]; i++) {
        sum += temp[i];
    }
    free(temp);
    return i;
}

int top = 0;
int count = 0;
int sequence[25];
FILE *fout;

void push(int num) {
    sequence[top] = num;
    top++;
}

void pop() {
    top--;
}

int validify_sequence(int **feed, int *require, int vitamin_count) {
    int *temp = (int*)malloc(sizeof(int) * vitamin_count);
    memset(temp, 0, sizeof(int) * top); 
    int i, j;
    for (i = 0; i < top; i++) 
        for (j = 0; j < vitamin_count; j++) 
            temp[j] += feed[sequence[i] - 1][j];
    
    for (i = 0; i < vitamin_count; i++) {
        if (temp[i] < require[i])
            return 1;
    }

    free(temp);
    return 0;
}

int pick_scoop(int *data, int data_size, int pick_size, int **feed, 
        int *require, int vitamin_count) {
    
    int i;
    if (pick_size == 1) {
        for (i = 0; i < data_size; i++) {
            push(data[i]);
            if (validify_sequence(feed, require, vitamin_count) == 0) {
                fprintf(fout, "%d", top);
                for (i = 0; i < top; i++) {
                    fprintf(fout, " %d", sequence[i]);
                }
                fprintf(fout, "\n");
                exit(0);
            }
            pop();
            count++;
        }
        return 1;
    }

    for (i = 0; i <= data_size - pick_size; i++) {
        push(data[i]);
        pick_scoop(data + i + 1, data_size - i - 1, pick_size - 1, feed, require, vitamin_count); 
        pop();
    }
    return 1;
}

int main () {
    int vitamin_count;
    int feed_count;
    int *require;
    int **feed;
    int i, j;

    FILE *fin = fopen("holstein.in", "r");
    fout = fopen("holstein.out", "w");

    fscanf(fin, "%d", &vitamin_count);
    require = (int*)malloc(sizeof(int) * vitamin_count);
    for (i = 0; i < vitamin_count; i++)
        fscanf(fin, "%d", &require[i]);

    fscanf(fin, "%d", &feed_count);
    feed = (int **)malloc(sizeof(int *) * feed_count);
    for (i = 0; i < feed_count; i++)
        feed[i] = (int *)malloc(sizeof(int) * vitamin_count);

    for (i = 0; i < feed_count; i++)
        for (j = 0; j < vitamin_count; j++)
            fscanf(fin, "%d", &feed[i][j]);

    int critical_require = find_critical_require(feed, require, 
            vitamin_count, feed_count);
    //printf("%d\n", critical_require);
    int initial_minimum = initial_minimum_require(feed, require, 
            critical_require, feed_count);
    //printf("mini:%d\n", initial_minimum);

    int *data = (int*)malloc(sizeof(int) * feed_count);
    for (i = 0; i < feed_count; i++) {
        data[i] = i + 1; 
    }

    for (i = initial_minimum; i <= feed_count; i++) {
        if (pick_scoop(data, feed_count, i, feed, require, vitamin_count) == 0) {
            break;
        }    
    }

    free(data);
    free(require);
    for (i = 0; i < feed_count; i++)
        free(feed[i]);
    free(feed);
    fclose(fin);
    fclose(fout);
}
