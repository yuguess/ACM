#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
using namespace std;

#define MAX 110010
#define TREAP_MAX 120000
#define MAX_Q 50111

int d[MAX];

class Treap {

public:
  Treap() : poolIdx(0), root(0) {}

  void clear() {
    poolIdx = 0;
  }

  void insert(int key) {
    int pri = rand();
    insertImpl(root, key, pri);
  }

  void del(int key) {
    delImpl(root, key);
  }

  int findKth(int k) {
    findKthImpl(root, k);
  }

  void print() {
    deque<int> que;
    que.push_back(root);
    while (que.size() != 0) {
      int n = que.front();
      printf("key %d, pri %d, l %d, r %d, parent %d, size %d, idx %d\n", 
        pool[n].key, pool[n].priority, pool[n].left, pool[n].right, 
        pool[n].parent, pool[n].size, n);
      que.pop_front();
      if (pool[n].left != -1)
        que.push_back(pool[n].left);
      if (pool[n].right != -1)
        que.push_back(pool[n].right);
    }
  }

private:

  void insertImpl(int prnt, int key, int pri) {
  
    int child = 0;

    if (poolIdx == 0) {
      root = initNode(-1, key, pri);
      return;
    }

    if (key >= pool[prnt].key) {
      pool[prnt].size++;
      if (pool[prnt].right == -1) {
        child = initNode(prnt, key, pri); 
        pool[prnt].right = child; 
      } else {
        
        insertImpl(pool[prnt].right, key, pri);
      }

      //print();
      if (pool[pool[prnt].right].priority < pool[prnt].priority) {
        //printf("enter left rotation p %d, c %d\n", 
        //pool[prnt].key, pool[pool[prnt].right].key);
        //print();
        //getchar();
        rotate(prnt, pool[prnt].right, 0);
        //printf("left r return\n");
        //printf("after left rotation\n");
        //print();
        //getchar();
      }
    } else if (key < pool[prnt].key) {
      pool[prnt].size++;
      if (pool[prnt].left == -1) {
        child = initNode(prnt, key, pri);
        pool[prnt].left = child; 
      } else {
        insertImpl(pool[prnt].left, key, pri);
      }
      //print();
      if (pool[pool[prnt].left].priority < pool[prnt].priority) {
        rotate(prnt, pool[prnt].left, 1);
      }
    }
  }

  void delImpl(int p, int key) {
    int next = 0;

    if (pool[p].key == key) {
      if (isLeaf(p)) {
        if (isRoot(p)) {
          poolIdx = 0;
          root = -1;
        } else {
          if (isRightChild(p)) {
            pool[pool[p].parent].right = -1;
          } else {
            pool[pool[p].parent].left = -1;
          }
        }
      } else { 

        if (pool[pool[p].right].priority > pool[pool[p].left].priority) {
          rotate(p, pool[p].right, 0);
        } else {
          rotate(p, pool[p].left, 1);
        }

        //printf("parent %d, size %d\n", pool[p].parent, 
            //pool[pool[p].parent].size);

        pool[pool[p].parent].size--;
        delImpl(p, key);
      }

    } else if (key > pool[p].key) {
      if (pool[p].right != -1) {
        pool[p].size--;
        delImpl(pool[p].right, key);
      } else {
        printf("Waring delete non exist key");
      }
    } else if (key < pool[p].key) {
      if (pool[p].left != -1) {
        pool[p].size--;
        delImpl(pool[p].left, key);
      } else {
        printf("Waring delete non exist key");
      }
    }
  }

  int findKthImpl(int n, int k) {
    if (pool[n].size >= k) {
      if (hasLeftChild(n)) {
        if (k == leftChildSize(n) + 1) {
          return pool[n].key;
        } else if (k <= leftChildSize(n)) {
          return findKthImpl(pool[n].left, k);
        } else {
          return findKthImpl(pool[n].right, k - leftChildSize(n) - 1); 
        }
      } else {
        if (k == 1) {
          return pool[n].key;
        } else {
          return findKthImpl(pool[n].right, k - 1); 
        }
      }
    } else {
      printf("WARNING\n");
    }
  }

  inline int leftChildSize(int n) {
    return pool[pool[n].left].size;
  }

  inline bool hasLeftChild(int n) {
    return !(pool[n].left == -1);
  }

  inline bool hasRightChild(int n) {
    return !(pool[n].right == -1);
  }

  inline bool isLeaf(int n) {
    return (pool[n].right == -1 && pool[n].left == -1);
  }

  inline bool isRoot(int n) {
    return n == root;
  }

  inline bool isRightChild(int n) {
    return pool[pool[n].parent].right == n;
  }

  //dir == 0 for left, == 1 for right
  void rotate(int p, int child, int dir) {

    pool[child].parent = pool[p].parent;
    if (isRoot(p)) {
      root = child;  
    } else {
      if (isRightChild(p)) {
        pool[pool[p].parent].right = child; 
      } else {
        pool[pool[p].parent].left = child;
      }
    }

    pool[p].parent = child;

    if (dir == 0) {
      if (pool[child].left != -1) {
        pool[p].size += (pool[pool[child].left].size - pool[child].size);
        pool[child].size += (pool[p].size - pool[pool[child].left].size);
      } else {
        pool[p].size -= pool[child].size;
        pool[child].size += pool[p].size;
      }

      pool[p].right = pool[child].left;
      if (pool[child].left != -1)
        pool[pool[child].left].parent = p;
      pool[child].left = p;
    } else {
      if (pool[child].right != -1) {
        pool[p].size += (pool[pool[child].right].size - pool[child].size);
        pool[child].size += (pool[p].size - pool[pool[child].right].size);
      } else {
        pool[p].size -= pool[child].size;
        pool[child].size += pool[p].size;
      }

      pool[p].left = pool[child].right;
      if (pool[child].right != -1)
        pool[pool[child].right].parent = p;
      pool[child].right = p;
    }
  }

  int initNode(int p, int k, int pri) {
    pool[poolIdx].parent = p;
    pool[poolIdx].left = -1;
    pool[poolIdx].right = -1;
    pool[poolIdx].size = 1;
    pool[poolIdx].key = k;
    pool[poolIdx].priority = pri;
    return poolIdx++;
  }

  struct Node {
    int parent;
    int left;
    int right;
    int size;
    int key;
    int priority;
  } pool[TREAP_MAX];

  int root;
  int poolIdx; 
};

struct Node {
  int low;
  int upper;
  int res;
  int idx;
  int k;
} query[MAX_Q];

bool cmpLow(const Node &l, const Node &r) {
  return l.low < r.low;
}

bool cmpIdx(const Node &l, const Node &r) {
  return l.idx < r.idx;
}

int main() {
  int m = 0, n = 0;
  scanf("%d %d", &m, &n);

  for (int i = 0; i < m; i++) {
    scanf("%d", d + i);
  }

  for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &(query[i].low), &(query[i].upper), &(query[i].k));
    query[i].idx = i;
  }

  //sort
  sort(query, query + n, cmpLow); 

  Treap *treap = new Treap;

  for (int i = query[0].low - 1; i < query[0].upper; i++) {
    //printf("insert %d, %d\n", i, d[i]);
    treap->insert(d[i]);
  }
  query[0].res = treap->findKth(query[0].k);

  //treap->print();

  for (int i = 1; i < n; i++) {
    for (int j = query[i - 1].low - 1; j < query[i].low - 1; j++) {
      //printf("del %d\n", d[j]);
      treap->del(d[j]);
      //treap->print();
    }

    for (int j = query[i - 1].upper - 1; j >= query[i].upper; j--) {
    //  //printf("del %d\n", d[j]);
      treap->del(d[j]);
    //  //treap->print();
    }

    //printf("after del\n");
    //treap->print();

    for (int j = query[i - 1].upper; j <= query[i].upper - 1; j++) {
      treap->insert(d[j]);
    }

    query[i].res = treap->findKth(query[i].k);
  }

  //sort
  sort(query, query + n, cmpIdx);

  for (int i = 0; i < n; i++) {
    printf("%d\n", query[i].res);
  }
}
