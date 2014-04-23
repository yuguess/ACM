#include <stdio.h>
#include <string.h>

#define MAX_S 15 
#define MAX_W 1000000 
#define MAX_EDGE 11

char s[MAX_S];

struct Node {
  int isWord; 
  int cnt;
  struct Node* edges[MAX_EDGE];
} pool[MAX_W]; 

int p = 1;

int insert(char *d) {
  Node *n = pool;
  int idx = 0;
  
  while (*d) {
    idx = *d - '0';
    if (n->edges[idx] == NULL) {
      n->edges[idx] = (&pool[p++]);
    }
    n = n->edges[idx];
    n->cnt++;
    d++;

    if (n->isWord)
      return 0;
  }

  if (n->cnt != 1)
    return 0;
  else
    return n->isWord = 1;
}

int main() {
  int nc = 0, n = 0, i = 0;
  int flag = 1, k = 0;
  scanf("%d", &nc);
  while (nc--) {
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
      scanf("%s", s);
      if (flag && !insert(s)) {
        printf("NO\n");
        flag = 0;
      }
    }

    if (flag) 
      printf("YES\n");

    memset(pool, 0, sizeof(Node) * (n + 1));
    flag = 1;
  }
}
