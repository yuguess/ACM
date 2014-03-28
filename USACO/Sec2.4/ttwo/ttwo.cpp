/*
ID: yuguess1
TASK: ttwo 
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

#define OUT fout
#define MAX 10
#define THRESHOLD 400

char table[MAX][MAX];

class Step {
public:
  int x;
  int y;
  int face;
  int is_cycle;
  int cnt;
  bool operator==(const Step &p) {
    return (this->x == p.x) && (this->y == p.y) && (this->face == p.face);
  }
};

void func(Step &s) {
  s.is_cycle = 1;
}

int init(Step &step) {
  step.face = 0; 
  step.is_cycle = 0;
  step.cnt = 0;
}

bool is_valid(int x, int y) {
  if (x < 0 || x >= MAX || y < 0 || y >= MAX) {
    return false;
  }

  if (table[y][x] == '*') {
    return false;
  }

  return true;
}

void next_step(vector<Step> &vec, Step &s) {
  int tx = 0, ty = 0;
  tx = s.x;
  ty = s.y;
  switch (s.face) {
  case 0:
    ty--;
    break;
  case 1:
    tx++;
    break;
  case 2:
    ty++;
    break;
  case 3:
    tx--;
    break;
  }

  if (is_valid(tx, ty)) {
    s.x = tx;
    s.y = ty;
    s.cnt++;
    return;
  }

  s.face = ((s.face + 1) % 4);
  s.cnt++;
  return;
}

void search_path(vector<Step> &vec, Step &s) {
  vector<Step>::iterator it;
  if ((it = find(vec.begin(), vec.end(), s)) != vec.end()) {
    for_each(it, vec.end(), func);
    return; 
  }

  vec.push_back(s);

  next_step(vec, s);

  search_path(vec, s);
}

int cycle_len(vector<Step> &v) {
  vector<Step>::iterator it;
  for (it = v.begin(); it != v.end(); it++) {
    if (it->is_cycle == 1) {
      break;
    }
  }

  if (it == v.end())
    return 0;

  Step s = v.back();
  
  return s.cnt - it->cnt + 1;
}

int find_intersect(vector<Step> &v1, vector<Step> &v2) {
  vector<Step>::iterator it1;
  vector<Step>::iterator it2;

  int cycle1 = cycle_len(v1);
  int cycle2 = cycle_len(v2);
  int min_cnt = INT_MAX; 
/*
  printf("cycle1 %d\n", cycle1);
  printf("cycle2 %d\n", cycle2);
*/
  for (it1 = v1.begin(); it1 != v1.end(); it1++) 
    for (it2 = v2.begin(); it2 != v2.end(); it2++) {
      if (it1->x == it2->x && it1->y == it2->y) {
/*
        printf("intersect %d,%d\n", it1->x, it1->y);
        printf("%d, %d, cnt:%d, is_cycle:%d\n", it1->x, it1->y, it1->cnt, it1->is_cycle);
        printf("%d, %d, cnt:%d, is_cycle:%d\n", it2->x, it2->y, it2->cnt, it2->is_cycle);
*/
        if (it1->cnt == it2->cnt) {
          min_cnt = min(it1->cnt, min_cnt); 
        } else {

          if (it1->cnt > it2->cnt && it2->is_cycle == 1) {
            if (((it1->cnt - it2->cnt) % cycle2) == 0) {
              min_cnt = min(it1->cnt, min_cnt);
            }
          } 

          if (it2->cnt > it1->cnt && it1->is_cycle == 1) {
            if (((it2->cnt - it1->cnt) % cycle1) == 0) {
              min_cnt = min(it2->cnt, min_cnt);
            }
          }

          if (it1->is_cycle == 1 && it2->is_cycle == 1) {
            int k = 0;
            while (it1->cnt + k * cycle1 < THRESHOLD) {
              if (it1->cnt + k * cycle1 > it2->cnt) {
                if ((it1->cnt + k * cycle1 - it2->cnt) % cycle2 == 0) {
                  min_cnt = min(it1->cnt + k * cycle1, min_cnt);
                  break;
                }
              }
              k++;
            }
            /*
            int cnt = it1->cnt - it2->cnt; 
            int cyc = cycle2 - cycle1;
            if (cyc != 0) {
              int k = cnt % cyc;
              if (k == 0 && cnt * cyc > 0) {
                min_cnt = min(k * cycle1 + it1->cnt, min_cnt);   
              }
            }
            */
          }
        }
        //printf("min:%d\n", min_cnt);
      }
    }
  //printf("min %d\n", min_cnt);
  if (min_cnt == INT_MAX)
    return 0;
  
  return min_cnt;
}

void print_path(vector<Step> &v) {
  vector<Step>::iterator it;
  for (it = v.begin(); it != v.end(); it++) {
    printf("%d, %d, cnt:%d, face:%d\n", it->x, it->y, it->cnt, it->face);
  }
}

int main () {
  FILE *fin = fopen("ttwo.in", "r");
  FILE *fout = fopen("ttwo.out", "w");

  Step fstart;
  Step cstart;

  vector<Step> fpath;
  vector<Step> cpath;

  for (int i = 0; i < MAX; i++) {
    for (int j = 0; j < MAX; j++) {
      fscanf(fin, "%c", &(table[i][j]));
      if (table[i][j] == 'F') {
        init(fstart);
        fstart.x = j;
        fstart.y = i;
        //printf("beg F %d %d\n", j, i);
      }

      if (table[i][j] == 'C') {
        init(cstart);
        cstart.x = j;
        cstart.y = i;
      }
    }
    //skip newline char
    char c;
    fscanf(fin, "%c", &c);
  }

  search_path(cpath, cstart);
  search_path(fpath, fstart); 
/*  
  print_path(fpath);
  printf("=========\n");
  print_path(cpath);
 */ 
  fprintf(OUT, "%d\n", find_intersect(fpath, cpath));

  fclose(fin);
  fclose(fout);
}
