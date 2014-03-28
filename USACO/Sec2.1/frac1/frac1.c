/*
ID: yuguess1
LANG: C
TASK: frac1 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

struct Node {
    float value;
    char str[10];
    Node *next;
};

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

void build_node(Node *node, int i, int j) {
    node->value = (float)j / i;
    sprintf(node->str, "%d/%d", j, i);
    node->next = NULL;
    return ;
}

Node* malloc_node() {
    Node* temp;
    if ((temp = (Node*)malloc(sizeof(Node))) != NULL)
        return temp;
    else 
        abort();
}

Node *insert_node(Node *list, Node *node) {
    Node* temp;
    float val = node->value;
    if (list == NULL) { 
        list = node;
    } else {
        temp = list;
        if (node->value < temp->value) {
            node->next = temp;
            list = node;
            return list;
        }

        while (temp->next != NULL) {
            if (temp->value < val && temp->next->value > val)
                break;
            temp = temp->next;
        }

        if (node->value > temp->value) {
            node->next = temp->next;
            temp->next = node; 
        } 
    }

    return list;
}

void print_list(Node *list, FILE *file) {
    Node *temp;
    if (list != NULL) {
        temp = list;
        while (temp != NULL) {
            fprintf(file, "%s\n", temp->str);
            temp = temp->next;
        }
    } else {
        printf("error\n");
    }
}

int main () {

    FILE *fin = fopen("frac1.in", "r");
    FILE *fout = fopen("frac1.out", "w");

    int length;
    int i, j;
    Node *list = NULL;
    Node *node;

    fscanf(fin, "%d", &length); 

    fprintf(fout, "0/1\n");

    for (i = 1; i <= length; i++) {
        for (j = 1; j < i; j++) {
            if (gcd(i, j) == 1) {
                node = malloc_node();
                build_node(node, i, j);
                list = insert_node(list, node);
            }
        }
    }
    
    print_list(list, fout);

    fprintf(fout, "1/1\n");

    fclose(fin);
    fclose(fout);
}
