/*
ID: yuguess1
LANG: C
TASK: prefix
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OUTPUT fout
#define HASH_TB_SIZE 200
#define MAX_STR_LEN 200002

typedef struct primitive hash_bk;
struct primitive{
    char buf[11];
    int hash_val;
    hash_bk *next;
};

hash_bk *hash_table[HASH_TB_SIZE];
int table[MAX_STR_LEN];

int hash(char *str) {
    int len = strlen(str);
    int i = 0;
    int sum = 0;
    for (i = len - 1; i >= 0; i--) {
        sum = sum * 6 + str[i];
    }

    return sum;
}

hash_bk *init_hash_block(char *str) {
    hash_bk* temp = (hash_bk*)malloc(sizeof(hash_bk));
    temp->next = NULL;
    
    strcpy(temp->buf, str); 
    
    temp->hash_val = hash(str);
    return temp;
}

int insert_hash_table(hash_bk* bk) {
    int idx = (bk->hash_val % HASH_TB_SIZE);
    hash_bk* tmp = hash_table[idx];
    if (tmp == NULL) {
        hash_table[idx] = bk;
    } else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = bk;
    }
    
}

int build_hash(char *buf) {
    
    hash_bk* bk = init_hash_block(buf);
    insert_hash_table(bk);
}

int process_input(FILE *fin, char *str) {
    char buf[11];
    char line_buf[77];
    
    do {
        fscanf(fin, "%s", buf); 
        build_hash(buf);
    } while (strcmp(buf, "."));

    while (fscanf(fin, "%s", line_buf) > 0) {
        strcat(str, line_buf);
    }
}

int search_hash_table(int val) {
    int idx = (val % HASH_TB_SIZE);
    hash_bk* tmp = hash_table[idx];
    while (tmp != NULL) {
        if (tmp->hash_val == val) { 
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

int is_in_primitive(str, start, step) {
    char *buf = (char*)malloc(sizeof(char) * 11);
    strncpy(buf, (char*)(str + start), step); 
    buf[step] = '\0';
    int hash_val = hash(buf);
    free(buf);
    return search_hash_table(hash_val);
}

int init_data() {
    int i = 0;
    for (i = 0; i < HASH_TB_SIZE; i++) {
        hash_table[i] = NULL;
    }
    
    for (i = 0; i < MAX_STR_LEN; i++) {
        table[i] = 0;
    }
}

int check_table(start) {
    return table[start];
}

int update_table(start, max_length) {
    if (max_length > table[start]) {
        table[start] = max_length;
    }    
    return 0;
}

int long_prefix(char *str, int start, int length) {
    int tmp = 0;
    int max_length = 0;
    int step = 1;

    if (start > (length - 1))
        return 0;

    if ((max_length = check_table(start))) {
        return max_length; 
    }

    for (step = 1; step <= 10 && (start + step <= length); step++) {
        if (is_in_primitive(str, start, step)) {
            tmp = step + long_prefix(str, start + step, length);
            if (tmp > max_length) {
                max_length = tmp;
                tmp = 0;
            }
        }
    }
    update_table(start, max_length);

    return max_length;
}

int main () {
    FILE *fin = fopen("prefix.in", "r");
    FILE *fout = fopen("prefix.out", "w");
    int length = 0;
    char*str = (char*)malloc(sizeof(char) * MAX_STR_LEN);
    
    init_data();
    process_input(fin, str);
    length = long_prefix(str, 0, strlen(str));
    fprintf(OUTPUT, "%d\n", length);

    free(str);
    fclose(fin);
    fclose(fout);
}
