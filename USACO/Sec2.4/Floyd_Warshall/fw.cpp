#include <stdio.h> 

#define MAX_V 10

int N;
int graph[MAX_V][MAX_V];

int main () {
  int r, c, w;

  FILE *fin = fopen("test.in", "r");
  FILE *fout = fopen("test.out", "w");

  fscanf(fin, "%d", &N);

  for (int i = 0; i < MAX_V; i++)
    for (int j = 0; j < MAX_V; j++)
      graph[i][j] = -1;

  for (int i = 0; i < N; i++) {
    fscanf(fin, "%d %d %d", &r, &c, &w);
    graph[r][c] = w;    
  }

  for (int i = 1; i <= N; i++)
    for (int j = 1; j <= N; j++) 
      for (int k = 1; k <= N; k++) {
        if (graph[j][i] != -1 && graph[i][k] != -1) {
          if (graph[j][k] == -1)
            graph[j][k] = graph[j][i] + graph[i][k];
          else if (graph[j][i] + graph[i][k] < graph[j][k])
            graph[j][k] = graph[j][i] + graph[i][k];
        }
      }

  for (int i = 0; i < MAX_V; i++) {
    for (int j = 0; j < MAX_V; j++)
      printf("[%d][%d]:%2d ", i, j, graph[i][j]);
    printf("\n");
  }
    
  fclose(fin);
  fclose(fout);
}
