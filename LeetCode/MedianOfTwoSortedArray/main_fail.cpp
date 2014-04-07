#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
using namespace std;

#define MAX 100000

int A[MAX];
int B[MAX];

class Solution {
public:
  double findMedianSortedArrays(int A[], int m, int B[], int n) {

    if ((m + n) % 2 == 0) {
      int mid = (m + n) / 2;
      return (findKth(A, m, B, n, mid) + findKth(A, m, B, n, mid + 1)) / 2.0;
    } else
      return findKth(A, m, B, n, (m + n) / 2 + 1); 

    //int idx = 0; 

    
    //
    //if (m == 1 && n == 1)
    //  return (A[0] + B[0]) / 2.0;
    //else if (m == 1) {
    //  return specialMedian(B, n, A[0]);
    //} else if (n == 1) {
    //  return specialMedian(A, m, B[0]);  
    //} else {
    //  if (m % 2 == 0 && n % 2== 0) {
    //    int Am = m / 2 - 1;
    //    int Bm = n / 2 - 1; 

    //    printf("x\n");

    //    if (A[Am] > B[Bm]) {
    //      return findMedianSortedArrays(A, m / 2 + 1, B + Bm + 1, n / 2); 
    //    } else if (A[Am] < B[Bm]) {
    //      return findMedianSortedArrays(A + Am + 1, m / 2, B, n / 2 + 1);
    //    } else {
    //      return A[Am];
    //    }

    //  } else if (m % 2 == 0 && n % 2 != 0) {
    //    return oddAndEven(B, n, A, m);
    //  } else if (m % 2 != 0 && n % 2 == 0) {
    //    return oddAndEven(A, m, B, n);
    //  } else {
    //    int Am = m / 2;
    //    int Bm = n / 2; 

    //    if (A[Am] > B[Bm]) {
    //      return findMedianSortedArrays(A, (m + 1)/2, B + Bm, (n + 1)/2); 
    //    } else if (A[Am] < B[Bm]) {
    //      printf("t\n");
    //      return findMedianSortedArrays(A + Am, m/2, B, n / 2);
    //    } else {
    //      return A[Am];
    //    }
    //  }
    //}
  }

private:
  int findKth(int A[], int m, int B[], int k) {
    if (m == 0) {
      return B[k - 1];
    } else if (n == 0) {
      return A[k - 1];
    } else if (m == 1 && n == 1) {
      return k == 1 ? min(A[0], B[0]) : max(A[0], B[0]);
    } else {

    if (m % 2 == 0 && n % 2== 0) {
      int Am = m / 2 - 1;
      int Bm = n / 2 - 1; 

      printf("x\n");

      if (A[Am] > B[Bm]) {
        if (k >= 1 || k <= (n + m - 1)) {
          findKth(A, m / 2 - 1, B, n, k);
        } else {
          findKth(A, m, B + Bm + 1, n / 2, k - n);
        }
      } else if (A[Am] < B[Bm]) {
        if (k > = 1 || k <= (n + m - 1)) {
          findKth(A, m, B, n /2 - 1, k);
        } else {
          findKth(A + Am + 1, m / 2 , B, n, k - m);
        }
      } else {

      }

    } else if (m % 2 == 0 && n % 2 != 0) {

      return oddAndEven(B, n, A, m);
    } else if (m % 2 != 0 && n % 2 == 0) {
      return oddAndEven(A, m, B, n);
    } else {
      int Am = m / 2;
      int Bm = n / 2; 

      if (A[Am] > B[Bm]) {
        return findMedianSortedArrays(A, (m + 1)/2, B + Bm, (n + 1)/2); 
      } else if (A[Am] < B[Bm]) {
        printf("t\n");
        return findMedianSortedArrays(A + Am, m/2, B, n / 2);
      } else {
        return A[Am];
      }
    }

    }
    //if (m == 1 && n == 1)
    //  return (A[0] + B[0]) / 2.0;
    //else if (m == 1) {
    //  return specialKth(B, n, A[0], k);
    //} else if (n == 1) {
    //  return specialKth(A, m, B[0], k);  
    //} else {

    
    //}
  }

  int oddAndEven(int odd[], int os, int even[], int es) {
    int om = os / 2; 
    int em = es / 2 - 1;

    if (odd[om] > even[em]) {
      return findMedianSortedArrays(odd, (os + 1) / 2, even + em + 1, es / 2);
    } else if (odd[om] < even[em]) {
      return findMedianSortedArrays(odd + om + 1, (os - 1) / 2, even, es / 2);
    } else {
      return odd[om];
    }
  }

  double arrayMedian(int A[], int sz) {
    if (sz % 2 == 0) {
      return  (A[sz / 2 - 1] + A[sz / 2]) / 2.0;
    } else {
      return  A[sz / 2];
    }
  }

  double specialMedian(int A[], int sz, int special, int k) {
    int idx = 0;
    if (sz % 2 == 0) {
      idx = sz / 2 - 1; 
      if (special > A[idx])
        return min(special, A[idx + 1]);
      else
        return A[idx];
    } else {
      idx = sz / 2;
      if (special > A[idx]) {
        return (A[idx] + min(special, A[idx + 1])) / 2.0;
      } else {
        return (A[idx] + max(special, A[idx - 1])) / 2.0;
      }
    }
  }
};

int main() {
  int m = 0, n = 0;
  scanf("%d %d", &m, &n);
  for (int i = 0; i < m; i++)  
    scanf("%d", A + i);

  for (int i = 0; i < n; i++)  
    scanf("%d", B + i);

  Solution sol;
  double med = sol.findMedianSortedArrays(A, m, B, n);
  cout << med << endl;
}
