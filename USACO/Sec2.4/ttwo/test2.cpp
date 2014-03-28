#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

class Pos {
public:
  int x;
  int y;
  bool operator==(const Pos &p2) {
    return (this->x == p2.x); 
  }
};

int main () {
  Pos p1;
  p1.x = 1;
  p1.y = 1;

  Pos p2;
  p2.x = 2;
  p2.y = 2;

  Pos p3;
  p3.x = 3;
  p3.y = 3;

  vector<Pos> v;
  v.push_back(p1);
  v.push_back(p2);

  if ((v.end() == find(v.begin(), v.end(), p1))) {
    printf("No\n");
  } else {
    printf("Yes\n");
  }
}
