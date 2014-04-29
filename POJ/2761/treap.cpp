#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 100001 

class Treap {

public:
  Treap() : poolIdx(0) {

  }

  void clear();

  void insert(key, pri) {
    insertImpl(0, key, pri);
  }

  void insertImpl(int prnt, int key, int pri) {
    int child = 0;

    if (poolIdx == 0) {
      initNode(prnt, key, pri);
      return;
    }

    if (key > pool[prnt].key) {
      if (pool[prnt].right == 0) {
        child = initNode(prnt, key, pri); 
      } else {
        insertImpl(pool[prnt].right, key, pri);
      }

      if (pri > pool[prnt].pri) {
        rotate(p, child, 0);
      }

    } else if (key < pool[prnt].key) {
      if (pool[prnt].left == 0) {
        child = initNode(prnt, key, pri);
      } else {
        insertImpl(pool[prnt].right, key, pri);
      }

      if (pri > pool[prnt].pri) {
        rotate(p, child, 1);
      }
    } else {
      printf("");
    }
  }

  void del(int key) {
    delImpl(0, key);
  }

  void delImpl(int p, int key) {
    int next = 0;

    if (pool[p].key == key) {
      if (isLeaf(p)) {

      }

    } else if (pool[p].key > key) {

    } else if (pool[p].key < key) {

    }

  }

  void findKth() {

  }

private:
  bool isRightChild(int n) {
    return pool[pool[n].parent].right == n;
  }

  //dir == 0 for left, == 1 for right
  void rotate(int p, int child, int dir) {

    pool[child].parent = pool[p].parent;
    
    if (!isRoot()) {
      if (isRightchild(p)) {
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

  int initNode(int p, int k, int p) {
    pool[poolIdx].parent = p;
    pool[poolIdx].left = 0;
    pool[poolIdx].right = 0;
    pool[poolIdx].leftSize = 0;
    pool[poolIdx].rightSize = 0;
    pool[poolIdx].key = k;
    pool[poolIdx].priority = p;
    return poolIdx++;
  }

  struct Node {
    int parent;
    int left;
    int right;
    int leftSize;
    int rightSize;

    int key;
    int priority;
  } pool[MAX];

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
  //check
}
