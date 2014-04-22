#include<iostream>
#include<stdio.h>
using namespace std;
const int Max = 1002;
const int branchNum = 26;
 
struct tree_node{
  int count;
  tree_node *next[branchNum];
} root, node[20*Max];

int p = 0;
 
void insert(char *word){
  tree_node *location = &root;
  while (*word) {
    if(location->next[*word-'a'] == NULL){
      node[p].count = 0;
      location->next[*word-'a'] = &node[p ++];
    }
    location = location->next[*word-'a'];
    location->count ++;
    word ++;
  }
}
 
void search(char *word){
  tree_node *location = &root;
  while(*word && location) {
    if(location->count == 1) break;
      printf("%c", *word);
      location = location->next[*word-'a'];
      word++;
    }
  printf("\n");
}
 
int main(){

  char word[Max][21];
  int i, k = 0;

  while(scanf("%s", word[k]) != EOF){
    insert(word[k]);
    k++;
  }

  for (i = 0; i < k; i ++){
    printf("%s ", word[i]);
    search(word[i]);
  }

  return 0;
}
