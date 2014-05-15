#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <list>
#include <deque>
using namespace std;

#define MAX 1000010

int mins[MAX];
int maxs[MAX];

template<typename T>
class MQueue {

public:
  MQueue(): qH(0), qT(-1) {}

  inline void push_back(int v, int t) {
    while (qT >= qH && cmp(v, q[qT].first)) {
      qT--;
    }

    q[++qT] = make_pair(v, t);
  }

  inline void update(int tm) {
    while (qT >= qH && q[qH].second < tm) {
      qH++;
    }
  }

  inline int top() {
    return q[qH].first;
  }

  void print() {
    int tail = qT;
    int head = qH;
    printf("head %d, tail %d\nvalue\n", qH, qT);
    while (tail >= head) {
      printf("%d,", q[head++].first);
    }
    printf("\n");
  }

private:
  T cmp;
  pair<int, int> q[MAX];
  int qH;
  int qT;
};


void printArr(int arr[], int upperBound) {

  printf("%d", arr[0]);
  for (int i = 1; i <= upperBound; i++)
    printf(" %d", arr[i]);
  printf("\n");

}

int main() {
  int ws = 0, n = 0, tmp = 0;

  MQueue<less<int> > *minQ = new MQueue<less<int> >;
  MQueue<greater<int> > *maxQ = new MQueue<greater<int> >;

  scanf("%d %d", &n, &ws);
  for (int i = 0; i < ws; i++) {
    scanf("%d", &tmp);
    //printf("read %d\n", tmp);
    minQ->push_back(tmp, i);
    maxQ->push_back(tmp, i);
    //printf("minTop %d\n", minQ.top());
  }

  //printf("min top %d, max top %d\n", minQ->top(), maxQ->top());
  mins[0] = minQ->top();
  maxs[0] = maxQ->top();

  int upperBound = n - ws;
  for (int i = 0; i < upperBound; i++) {

    minQ->update(i + 1);
    maxQ->update(i + 1);
    scanf("%d", &tmp);
    minQ->push_back(tmp, i + ws);
    maxQ->push_back(tmp, i + ws);

    mins[i + 1] = minQ->top();
    maxs[i + 1] = maxQ->top();
  }

  printArr(mins, upperBound);
  printArr(maxs, upperBound);
}
