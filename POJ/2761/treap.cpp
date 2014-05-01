#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <deque>
using namespace std;

#define MAX 10001 

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

  //printf("test here\n");
  treap.insert(1, 17);
  treap.insert(2, 30);
  treap.insert(3, 47);
  treap.insert(4, 33);
  treap.insert(5, 11);

  treap.print();
  getchar();
  
  treap.del(5);
  treap.print();
  getchar();

  treap.del(1);
  treap.print();
  getchar();

  treap.del(2);
  treap.print();
  //check
}
