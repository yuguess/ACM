/*
ID: yuguess1
TASK: cowtour 
LANG: C++
*/

#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <climits>
using namespace std;

#define OUT fout
#define MAX_V 150

typedef struct {
  int x;
  int y;
} Pos;

int n;
Pos v[MAX_V];
double g[MAX_V][MAX_V];

double dis(Pos &v1, Pos &v2) {
  return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}

bool is_in(int s, vector<int> v) {
  if (v.end() == find(v.begin(), v.end(), s))
    return false;
  else
    return true;
}

void dfs(int s, vector<int> &p, int *flag) {
  if (is_in(s, p))
    return;

  p.push_back(s);
  flag[s] = 1;

  for (int i = 0; i < n; i++) {
    if (g[s][i] != -1) {
      dfs(i, p, flag);
    }
  }
}

int classify(vector< vector<int> >&all_clst) {
  int flag[MAX_V];

  for (int i = 0; i < n; i++) {
    flag[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    if (flag[i] == 0) {
      vector<int> p;
      dfs(i, p, flag);
      all_clst.push_back(p);
    }
  }

  return 0;
}

void floyd_warshall(vector<int> &p) {

  for (int k = 0; k < p.size(); k++)
    for (int i = 0; i < p.size(); i++)
      for (int j = 0; j < p.size(); j++) {
        if (p[i] == p[j])
          continue;
        if (g[p[i]][p[k]] != -1 && g[p[k]][p[j]] != -1) {
          if (g[p[i]][p[j]] == -1) 
            g[p[i]][p[j]] = g[p[i]][p[k]] + g[p[k]][p[j]];
          else if (g[p[i]][p[k]] + g[p[k]][p[j]] < g[p[i]][p[j]]) 
            g[p[i]][p[j]] = g[p[i]][p[k]] + g[p[k]][p[j]];
        }
      }
        
  return;
}

double max_dis(int s) {
  double dis = (*max_element(g[s], g[s] + n));
  if (dis == -1)
    return 0.0;
  return dis;
}

double dia_clus(vector<int> &p1, vector<int> &p2, double field_dia) {
  double dia = INT_MAX; 
  
  for (int i = 0; i < p1.size(); i++) 
    for (int j = 0; j < p2.size(); j++) {
      //printf("%f\n", max_dis(p1[i]));
      //printf("%d, %f\n", p2[j], max_dis(p2[j]));

      double tmp = max_dis(p1[i]) + max_dis(p2[j]) + dis(v[p1[i]], v[p2[j]]);
      tmp = max(field_dia, tmp);
      //printf("%f\n", tmp);
      //getchar();
      if (tmp < dia) {
        dia = tmp; 
      }
    }

  return dia;
}

int max_dis_p(int s) {
  return distance(g[s], max_element(g[s], g[s] + n));
}

double field_dia(vector<int> &clut) {
  double max_dia = 0;
  for (int i = 0; i < clut.size(); i++)
    max_dia = max(max_dia, double(max_dis(clut[i])));
  return max_dia;
}

int main () {
  char c;
  vector< vector<int> > all;

  FILE *fin = fopen("cowtour.in", "r");
  FILE *fout = fopen("cowtour.out", "w");

  fscanf(fin, "%d", &n);

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      g[i][j] = -1;

  for (int i = 0; i < n; i++) {
    fscanf(fin, "%d %d", &(v[i].x), &(v[i].y));
  }

  //skip newline
  fscanf(fin, "%c", &c);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      fscanf(fin, "%c", &c); 
      if (c == '1') {
        g[i][j] = dis(v[i], v[j]);
      }
    }
    fscanf(fin, "%c", &c);
  }

  classify(all);
/*
  printf("%d cluster\n", all.size());
  printf("cluster 1 %d\n", all[0].size());
  printf("cluster 2 %d\n", all[1].size());
  printf("%d\n", all[0].size() + all[1].size());
  */

/*
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      printf("%.01f ", g[i][j]);
    printf("\n\n");
  }
*/
  
  for (int i = 0; i < all.size(); i++)
    floyd_warshall(all[i]);

  vector<double> field;

  for (int i = 0; i < all.size(); i++) {
    double tmp = field_dia(all[i]);
    //printf("cluter %d %f\n", i, tmp);
    field.push_back(tmp);
  }

  double min_dia = INT_MAX;

  for (int i = 0; i < (all.size() - 1); i++)
    for (int j = i + 1; j < all.size(); j++) {
      double tmp = dia_clus(all[i], all[j], max(field[i], field[j]));
        
      min_dia = min(min_dia, tmp);
    }

  //printf("p1 %d\n", dia_p1);
  //printf("p2 %d\n", dia_p2);
  fprintf(OUT, "%.6f\n", min_dia);

  /*
  for (int i = 0; i < p1.size(); i++)
    printf("%d ", p1[i]);
  printf("\n");

  for (int i = 0; i < p2.size(); i++)
    printf("%d ", p2[i]);
  printf("\n");

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      printf("%06.02f ", g[i][j]);
    printf("\n");
  }
 */ 
  fclose(fin);
  fclose(fout);
}
