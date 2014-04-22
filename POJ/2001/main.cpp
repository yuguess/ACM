#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX_W 24
#define MAX_N 10010

char d[MAX_N][MAX_W];

#define MAX_EDGE 27

struct Node {
  bool isWord;
  int numEdges; 
  Node *edges[MAX_EDGE]; 
};

Node* createNode() {
  Node* tmp = new Node();
  tmp->isWord = false;
  tmp->numEdges = 0;
  memset(tmp->edges, 0, sizeof(Node *) * MAX_EDGE);
  return tmp;
}

bool insert(Node *node, char *s) {
  if (s[0] == '\0') {
    if (node->isWord)
      return false;
    else {
      return node->isWord = true;
    }

  } else {
    int idx = s[0] - 'a';
    node->numEdges++;

    if (node->edges[idx] == NULL) {
      node->edges[idx] = createNode(); 
    }

    return insert(node->edges[idx], s + 1);
  }

}

int validName(Node *node, char *name) {
  if (name[0] == '\0') {
    return 1;
  } else if (node->numEdges == 1 && !node->isWord) {
    return 0;
  } else {
    int idx = name[0] - 'a';
    return validName(node->edges[idx], name + 1) + 1; 
  }
}

int main() {
  int idx = -1;
  Node *root = createNode();

  while (scanf("%s", d[++idx]) > 0) {
    insert(root, d[idx]);
  }

  for (int i = 0; i <= idx; i++) {
    printf("%s ", d[i]);
    d[i][validName(root, d[i])] = '\0';
    printf("%s\n", d[i]);
  }
}
