#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
  vector<string> generateParenthesis(int n) {
    vector<string> res;

    if (mem.find(n) != mem.end()) {
      return mem[n];
    }

    for (int inSize = 0; inSize <= n - 1; inSize++) {
      int outSize = n - inSize - 1;
      vector<string> inVec = generateParenthesis(inSize);
      vector<string> outVec = generateParenthesis(outSize);

      if (inVec.size() == 0) inVec.push_back("");
      if (outVec.size() == 0) outVec.push_back("");

      for (int i = 0; i < outVec.size(); i++)
        for (int j = 0; j < inVec.size(); j++)
          res.push_back(outVec[i] + "(" + inVec[j] + ")");
    }

    mem[n] = res; 
    return res;
  }

private:

  map<int, vector<string> > mem;
};

int main() {
  int n = 0;
  scanf("%d", &n);

  Solution sol;
  vector<string> pp = sol.generateParenthesis(n);
  for (int i = 0; i < pp.size(); i++)
    cout << pp[i] << endl;
}
