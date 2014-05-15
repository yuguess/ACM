#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <list>
using namespace std;

vector<int> mins;
vector<int> maxs;

template<typename T>
class MQueue {

public:
  inline void push_back(int v, int t) {
    while (!l.empty() && cmp(v, l.back().first)) {
      l.pop_back();
    }

    l.push_back(make_pair(v, t));
  }

  inline void update(int tm) {
    while (!l.empty() && l.front().second < tm) {
      l.pop_front();
    }
  }

  inline int top() {
    return l.front().first;
  }

private:
  T cmp;
  list<pair<int, int> > l;
};


void printVec(vector<int> &v) {
  for (int i = 0; i < v.size(); i++) {
    if (i == 0)
      printf("%d", v[i]);
    else
      printf(" %d", v[i]);
  }
}

int main() {
  int ws = 0, n = 0, tmp = 0;

  MQueue<less<int> > minQ;
  MQueue<greater<int> > maxQ;

  scanf("%d %d", &n, &ws);
  for (int i = 0; i < ws; i++) {
    scanf("%d", &tmp);
    //printf("read %d\n", tmp);
    minQ.push_back(tmp, i);
    maxQ.push_back(tmp, i);
    //printf("minTop %d\n", minQ.top());
  }

  //printf("out top %d", minQ.top());
  mins.push_back(minQ.top());
  maxs.push_back(maxQ.top());
  int upperBound = n - ws;
  for (int i = 0; i < upperBound; i++) {

    minQ.update(i + 1);
    maxQ.update(i + 1);
    scanf("%d", &tmp);
    minQ.push_back(tmp, i + ws);
    maxQ.push_back(tmp, i + ws);

    mins.push_back(minQ.top());
    maxs.push_back(maxQ.top());
  }

  printVec(mins);
  printf("\n");
  printVec(maxs);
  printf("\n");
}

