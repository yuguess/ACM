/*
ID: yuguess1
TASK: rockers 
LANG: C++
*/
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <list>
#include <vector>
#include <map>

using namespace std;

#define OUT fout
#define IN fin
#define MAX 21

void printMap(map<int, int> &m) {
  for (map<int, int>::iterator it = m.begin(); it != m.end(); it++) {
    printf("[%d]->%d\n", it->first, it->second);
  }
}

int maxSongs(vector<int> &discs, list<int> songs) {
  if (songs.size() == 0)
    return 0;

  int song = songs.front();
  songs.pop_front();

  int maxCount = 0;

  for (int i = song; i < MAX; i++) {
    if (discs[i] == 0)
      continue;

    discs[i]--;
    discs[i - song]++;
    maxCount = max(maxCount, maxSongs(discs, songs) + 1);
    //roll back
    discs[i]++;
    discs[i - song]--;
  }

  return max(maxCount, maxSongs(discs, songs));
}

int main() {
  int N = 0, T = 0, M = 0;
  int tmp = 0;
  list<int> songs;
  vector<int> discs(MAX, 0);

  FILE *fin = fopen("rockers.in", "r");
  FILE *fout = fopen("rockers.out", "w");

  fscanf(fin, "%d", &N);
  fscanf(fin, "%d", &T);
  fscanf(fin, "%d", &M);

  discs[T] = M;

  for (int i = 0; i < N; i++) {
    fscanf(fin, "%d", &tmp); 
    songs.push_back(tmp);
  }

  fprintf(OUT, "%d\n", maxSongs(discs, songs));

  fclose(fin);
  fclose(fout);
}
