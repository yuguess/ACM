/*
ID: yuguess1
TASK: camelot 
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <map>
#include <limits.h>
#include <queue>
#include <algorithm>
using namespace std;

#define OUT fout
#define IN fin

#define MAX_R 30
#define MAX_C 26

int R, C;
pair<int, int> ki;
vector< pair<int, int> > kns;

queue<int> qs;
queue<pair<int, int> > sp;

short steps[MAX_R * MAX_C][MAX_R][MAX_C];
short ksteps[MAX_R][MAX_C];
int ssum[MAX_R][MAX_C] = {0};

void knight_steps(pair<int, int> &pos, vector<pair<int, int> > &v) {
  if (pos.first - 1 >= 0 && pos.second - 2 >= 0) {
    v.push_back(pair<int, int>(pos.first - 1, pos.second - 2));
  }

  if (pos.first - 2 >= 0 && pos.second - 1 >= 0) {
    v.push_back(pair<int, int>(pos.first - 2, pos.second - 1));
  }

  if (pos.first - 2 >= 0 && pos.second + 1 < C) {
    v.push_back(pair<int, int>(pos.first - 2, pos.second + 1));
  }

  if (pos.first - 1 >= 0 && pos.second + 2 < C) {
    v.push_back(pair<int, int>(pos.first - 1, pos.second + 2));
  }

  if (pos.first + 1 < R && pos.second + 2 < C) {
    v.push_back(pair<int, int>(pos.first + 1, pos.second + 2));
  }

  if (pos.first + 2 < R && pos.second + 1 < C) {
    v.push_back(pair<int, int>(pos.first + 2, pos.second + 1));
  }

  if (pos.first + 2 < R && pos.second - 1 >= 0) {
    v.push_back(pair<int, int>(pos.first + 2, pos.second - 1));
  }

  if (pos.first + 1 < R && pos.second - 2 >= 0) {
    v.push_back(pair<int, int>(pos.first + 1, pos.second - 2));
  }
}

void king_steps(pair<int, int> &pos, vector<pair<int, int> > &v) {
  if (pos.second - 1 >= 0) {
    v.push_back(pair<int, int>(pos.first, pos.second - 1));
  }

  if (pos.first - 1 >= 0 && pos.second - 1 >= 0) {
    v.push_back(pair<int, int>(pos.first - 1, pos.second - 1));
  }

  if (pos.first - 1 >= 0) {
    v.push_back(pair<int, int>(pos.first - 1, pos.second));
  }

  if (pos.first - 1 >= 0 && pos.second + 1 < C) {
    v.push_back(pair<int, int>(pos.first - 1, pos.second + 1));
  }

  if (pos.second + 1 < C) {
    v.push_back(pair<int, int>(pos.first, pos.second + 1));
  }

  if (pos.first + 1 < R && pos.second + 1 < C) {
    v.push_back(pair<int, int>(pos.first + 1, pos.second + 1));
  }

  if (pos.first + 1 < R) {
    v.push_back(pair<int, int>(pos.first + 1, pos.second));
  }

  if (pos.first + 1 < R && pos.second - 1 >= 0) {
    v.push_back(pair<int, int>(pos.first + 1, pos.second - 1));
  }
}

void data_init() {
  for (int i = 0; i < MAX_R * MAX_C; i++)
    for (int j = 0; j < MAX_R; j++) 
      for (int k = 0; k < MAX_C; k++)
        steps[i][j][k] = -1;

  for (int i = 0; i < MAX_R; i++)
    for (int j = 0; j < MAX_C; j++)
      ksteps[i][j] = -1;
}

void generate_steps(pair<int, int> init, 
          void (*p)(pair<int, int> &inip, vector<pair<int, int> > &v), 
          short m[][MAX_C]) {
  sp.push(init);
  qs.push(0);

  pair<int, int> ptm;
  int depth = 0;

  while (!sp.empty()) {
    ptm = sp.front();
    sp.pop();
    depth = qs.front(); 
    qs.pop();

    if (m[ptm.first][ptm.second] == -1) {
      m[ptm.first][ptm.second] = depth;
      vector<pair<int, int> > psteps;
      p(ptm, psteps);
      for (int i = 0; i < psteps.size(); i++) {
        if (m[psteps[i].first][psteps[i].second] == -1) {
          sp.push(psteps[i]);
          qs.push(depth + 1);
        }
      }
    }
  }
}

int merge(int n, int range) {
  int min_stp = INT_MAX;
  int sum_stp = 0;

  for (int i = 0; i < MAX_R; i++) {
    for (int j = 0; j < MAX_C; j++) {
      for (int k = 1; k < range + 1; k++) {
        if (k == n)
          continue;
        if (steps[k][i][j] == -1) {
          sum_stp = INT_MAX;
          break;
        } else {
          sum_stp += steps[k][i][j];
        }
      }
      min_stp = min(min_stp, sum_stp);
      sum_stp = 0;
    }
  }
 
  return min_stp;
}

int cancel(int n) {
  int min_stp = INT_MAX;
  for (int i = 0; i < MAX_R; i++)
    for (int j = 0; j < MAX_C; j++) {
      if (steps[0][i][j] != -1 && steps[n][i][j] != -1) {
        min_stp = min(min_stp, steps[0][i][j] + steps[n][i][j]);
      }
    }

  return min_stp;
}

bool is_valid(int r, int c) {
  if (r < 0 || r >= R)
    return false;
  if (c < 0 || c >= C)
    return false;

  return true;
}

int pick_k(int r, int c, int ksize) {
  int kmin = INT_MAX;
  int k = INT_MAX; 
  for (int i = 0; i < ksize; i++) 
    if (steps[i][r][c] != -1 && steps[i][r][c] < kmin) {
      kmin = steps[i][r][c];
      k = i;
    }

  return k == INT_MAX ? -1 : k;
}

int merge_stp(int n, int ksize, short nsp[][MAX_C]) {
  int min_stp = INT_MAX;
  int sum_stp = 0;
  int mr, mc, nspp, sump;
  for (int i = 0; i < MAX_R; i++) {
    for (int j = 0; j < MAX_C; j++) {
      for (int k = 0; k < ksize; k++) {
        if (k == n)
          continue;
        if (nsp[i][j] == -1 || steps[k][i][j] == -1) {
          sum_stp = INT_MAX;
          break;
        } else {
          sum_stp += steps[k][i][j];
          if (sum_stp < 0) {
            getchar();
          }
        }
      }

      if (sum_stp != INT_MAX) {
        if (sum_stp + nsp[i][j] < min_stp) {
          min_stp =  sum_stp + nsp[i][j];
          mr = i;
          mc = j;
          nspp = nsp[i][j];
          sump = sum_stp; 
        }
      }
      sum_stp = 0;
    }
  }
 
  //printf("merge r %d, c %d, nsp %d, sump %d\n", mr, mc, nspp, sump);
  return min_stp;
}

int main() {
  char tp;
  int tmp;

  data_init();

  FILE *fin = fopen("camelot.in", "r");
  FILE *fout = fopen("camelot.out", "w");

  fscanf(IN, "%d %d", &R, &C);
  fscanf(IN, "%c", &tp);
  fscanf(IN, "%c %d", &(tp), &(ki.first));
  ki.second = tp - 'A'; 
  ki.first = R - ki.first;

  while (fscanf(IN, "%c", &tp) != EOF) {
    if (tp != '\n' && tp != ' ') {
      fscanf(IN, "%d", &tmp);
      kns.push_back(pair<int, int>(R - tmp, tp - 'A'));
    }
  }

  generate_steps(ki, king_steps, ksteps);
  for (int i = 0; i < kns.size(); i++) {
    generate_steps(kns[i], knight_steps, steps[i]);

    for (int m = 0; m < R; m++)
      for (int n = 0; n < C; n++) {
        if (ssum[m][n] != -1) {
          if (steps[i][m][n] == -1) {
            ssum[m][n] = -1;
          } else {
            ssum[m][n] += steps[i][m][n];
          }
        }
      }
  }

  int sr = 4;
  int kth = 0; 
  int min_stp = INT_MAX;
  int ms, ns, _ssum, ps, is, js, _nsp, rest, _k;
  int pick_step;
  short nsp[MAX_R][MAX_C];
  
  for (int i = ki.first - sr; i <= ki.first + sr; i++)
    for (int j = ki.second - sr; j <= ki.second + sr; j++) {
      if (!is_valid(i, j) || ssum[i][j] == -1) {
        continue;
      }

    for (int m = 0; m < R; m++)
      for (int n = 0; n < C; n++)
        nsp[m][n] = -1;

    for (int m = 0; m < R; m++)
      for (int n = 0; n < C; n++) {
        if (ssum[m][n] == -1 || ssum[m][n] > min_stp) {
          continue;
        }

        generate_steps(pair<int, int>(i, j), knight_steps, nsp);

        for (int kth = 0; kth < kns.size(); kth++) {
          if (steps[kth][m][n] == -1 || steps[kth][i][j] == -1 || nsp[m][n] == -1) {
            continue;
          }
          pick_step = steps[kth][i][j]+ ksteps[i][j];
         
          //min_stp = min(min_stp, ssum[m][n] - steps[kth][m][n] + nsp[m][n] + pick_step);
          if (ssum[m][n] - steps[kth][m][n] + nsp[m][n] + pick_step < min_stp) {
            min_stp = ssum[m][n] - steps[kth][m][n] + nsp[m][n] + pick_step;
            //printf("kni %d, pick %d %d pick stp %d, new step %d, assemble %d %d step %d, min_stp %d\n", kth, i, j, pick_step, nsp[m][n], m, n, ssum[m][n] - steps[kth][m][n], min_stp);
          }
        }
      }
    }
    
  if (min_stp == INT_MAX) {
    fprintf(OUT, "%d\n", 0);
  } else {
    fprintf(OUT, "%d\n", min_stp);
  }

  fclose(fin);
  fclose(fout);
}
