#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <deque>
using namespace std;

#define MAX 100001 

class Treap {

public:
  Treap() : poolIdx(0), root(0) {}

  void clear() {
    poolIdx = 0;
  }

  void insert(int key, int pri) {
    insertImpl(root, key, pri);
  }

  void insertImpl(int prnt, int key, int pri) {
    int child = 0;

    if (poolIdx == 0) {
      root = initNode(-1, key, pri);
      return;
    }

    if (key > pool[prnt].key) {
      if (pool[prnt].right == -1) {
        child = initNode(prnt, key, pri); 
        pool[prnt].right = child; 
      } else {
        insertImpl(pool[prnt].right, key, pri);
      }

      if (pool[pool[prnt].right].priority < pool[prnt].priority) {
        //printf("enter left rotation p %d, c %d\n", pool[prnt].key, pool[pool[prnt].right].key);
        rotate(prnt, pool[prnt].right, 0);
        //printf("after left rotation\n");
        //print();
        //getchar();
      }
    } else if (key < pool[prnt].key) {
      if (pool[prnt].left == -1) {
        child = initNode(prnt, key, pri);
        pool[prnt].left = child; 
      } else {
        insertImpl(pool[prnt].right, key, pri);
      }

      if (pool[pool[prnt].left].priority < pool[prnt].priority) {
        //printf("enter right rotation\n");
        rotate(prnt, pool[prnt].left, 1);

        //printf("after right rotation\n");
        //print();
        //getchar();
      }
    } else {
      printf("Warning insert wiht same key\n");
    }
  }

  void del(int key) {
    delImpl(root, key);
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

        delImpl(p, key);
      }

    } else if (key > pool[p].key) {
      if (pool[p].right != -1) {
        delImpl(pool[p].right, key);
      } else {
        printf("Waring delete non exist key");
      }
    } else if (key < pool[p].key) {
      if (pool[p].left != -1) {
        delImpl(pool[p].left, key);
      } else {
        printf("Waring delete non exist key");
      }
    }
  }

  void print() {
    deque<int> que;
    que.push_back(root);
    while (que.size() != 0) {
      int n = que.front();
      printf("key %d, pri %d, l %d, r %d, parent %d, idx %d\n", pool[n].key, pool[n].priority, pool[n].left, pool[n].right, pool[n].parent, n);
      que.pop_front();
      if (pool[n].left != -1)
        que.push_back(pool[n].left);
      if (pool[n].right != -1)
        que.push_back(pool[n].right);
    }
  }

  void findKth() {

  }


private:
  bool isLeaf(int n) {
    return (pool[n].right == -1 && pool[n].left == -1);
  }

  bool isRoot(int n) {
    return n == root;
  }

  bool isRightChild(int n) {
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
      pool[p].right = pool[child].left;

      pool[pool[child].left].parent = p;
      pool[child].left = p;
    } else {
      pool[p].left = pool[child].right;

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
  } pool[MAX];

  int root;
  int poolIdx; 
};

class AVLTree {

};

class SplayTree {

};

class BTTree {

};

class SegTree {

};

//test function
int main() {
  Treap treap;

  treap.insert(1, 17);
  treap.insert(2, 30);
  treap.insert(3, 47);
  treap.insert(4, 33);
  treap.insert(5, 11);
  
  treap.del(1);
  treap.print();

  //check
}
