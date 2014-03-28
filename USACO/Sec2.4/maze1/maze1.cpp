/*
ID: yuguess1
TASK: maze1 
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

//#define DEBUG

#define OUT fout
#define MAX_W 77
#define MAX_H 201

class Pos {
public:
  Pos(): h(-1), w(-1), d(1) {}
  Pos(int ih, int iw, int id): h(ih), w(iw), d(id){}
  int w;
  int h;
  int d;
};

vector<Pos> vec;

void print_maze(int w, int h, int m1[][MAX_W]) {
  for (int i = 0; i < 2 * h + 1; i++) {
    for (int j = 0; j < 2 * w + 1; j++) {
      printf("%03d ", m1[i][j]);
    }
    printf("\n");
  }
}

bool is_dup(int h, int w) {
  vector<Pos>::iterator it;

  for (it = vec.begin(); it != vec.end(); it++) {
    if (it->h == h && it->w == w)
      return true;
  }

  return false;
}

int search_path(int hbd, int wbd, int m[][MAX_W]) {

  while (!vec.empty()) {

    Pos p = vec.front();

    m[p.h][p.w] = p.d;
    vec.erase(vec.begin());

#ifdef DEBUG
    printf("check %d %d %d\n", p.h, p.w, p.d);
    //getchar();
#endif

    if (p.w >= 0 && p.w < wbd && p.h - 2 >= 0 && p.h - 2 < hbd && m[p.h - 1][p.w] == 0
        && m[p.h - 2][p.w] == 0) {
      if (!is_dup(p.h - 2, p.w))
        vec.push_back(Pos(p.h - 2, p.w, p.d + 1));
    }

    if (p.w + 2 >= 0 && p.w + 2 < wbd && p.h >= 0 && p.h < hbd && m[p.h][p.w + 1] == 0 
        && m[p.h][p.w + 2] == 0) {
      if (!is_dup(p.h, p.w + 2))
        vec.push_back(Pos(p.h, p.w + 2, p.d + 1));
    }

    if (p.w >= 0 && p.w < wbd && p.h + 2 >= 0 && p.h + 2 < hbd && m[p.h + 1][p.w] == 0
        && m[p.h + 2][p.w] == 0) {
      if (!is_dup(p.h + 2, p.w))
        vec.push_back(Pos(p.h + 2, p.w, p.d + 1));
    }

    if (p.w - 2 >= 0 && p.w - 2 < wbd && p.h >= 0 && p.h < hbd && m[p.h][p.w - 1] == 0 
        && m[p.h][p.w - 2] == 0) {
      if (!is_dup(p.h, p.w - 2))
        vec.push_back(Pos(p.h, p.w - 2, p.d + 1));
    }
  }

}

void save_start(Pos &s1, Pos &s2, int h, int w) {
  if (s1.w == -1) {
    s1.h = h;
    s1.w = w;
  } else {
    s2.h = h;
    s2.w = w;
  }
}

int merge_result(int m1[][MAX_W], int m2[][MAX_W], int h, int w) {
  int minmax = 0;
  for (int i = 0; i < 2 * h + 1; i++)
    for (int j = 0; j < 2 * w + 1; j++) {
      if (m1[i][j] == -1 || m1[i][j] == 0) 
        continue;
      minmax = max(minmax, min(m1[i][j], m2[i][j]));
    }

  return minmax;
}

int main () {

  FILE *fin = fopen("maze1.in", "r");
  FILE *fout = fopen("maze1.out", "w");

  int w, h;
  char c;
  Pos s1, s2; 

  fscanf(fin, "%d", &w);
  fscanf(fin, "%d", &h);
  //skip newline
  fscanf(fin, "%c", &c);

  int m1[MAX_H][MAX_W];
  int m2[MAX_H][MAX_W];

  for (int i = 0; i < 2 * h + 1; i++) { 
    for (int j = 0; j < 2 * w + 1; j++) {
      fscanf(fin, "%c", &c);
      if (c != ' ') {
        m1[i][j] = -1;
        m2[i][j] = -1;
      } else {
        m1[i][j] = 0;
        m2[i][j] = 0;
      }

      if (i == 0 && c == ' ') {
        save_start(s1, s2, i + 1, j);
      }

      if (j == 0 && c == ' ') {
        save_start(s1, s2, i, j + 1);
      }

      if (i == 2 * h && c == ' ') {
        save_start(s1, s2, i - 1, j);
      }

      if (j == 2 * w && c == ' ') {
        save_start(s1, s2, i, j - 1);
      }
    }
    //skip newline
    fscanf(fin, "%c", &c);
  }
  //print_maze(w, h, m1);
  vec.push_back(s1); 
  search_path(2 * h + 1, 2 * w + 1, m1);
#ifdef DEBUG
  print_maze(w, h, m1);
#endif

  vec.push_back(s2); 
  search_path(2 * h + 1, 2 * w + 1, m2);
#ifdef DEBUG
  print_maze(w, h, m2);
#endif

  fprintf(OUT, "%d\n", merge_result(m1, m2, h, w));

  fclose(fin);
  fclose(fout);
}
