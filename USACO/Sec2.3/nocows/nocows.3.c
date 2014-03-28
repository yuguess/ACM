#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MOD 9901

int table[101][202],N,K,c;
int smalltrees[101][202];



int main() {
    FILE *fin=fopen("nocows.in","r");
    FILE *fout=fopen("nocows.out","w");
    int i, j, k;
    fscanf (fin,"%d %d",&N,&K);
    table[1][1]=1;
    for (i=2;i<=K;i++) {
        for (j=1;j<=N;j+=2) {
            for (k=1;k<=j-1-k;k+=2) {
                if (k!=j-1-k) c=2; else c=1;

                int left_sum = smalltrees[i-2][k]*table[i-1][j-1-k]; // left subtree smaller than i-1
                int right_sum = table[i-1][k]*smalltrees[i-2][j-1-k]; // right smaller
                int equal_sum = table[i-1][k]*table[i-1][j-1-k]; // both i-1
                if (j == 21 && K == 6) {
                    printf("left sum %d, left %d, right %d\n", left_sum, k, j - 1 -k);
                    printf("right sum %d, left %d, right %d\n", right_sum, k, j - 1 - k);
                    printf("equal sum %d, equal %d\n", equal_sum, k);
                    printf("subsum %d\n", c*(left_sum + right_sum + equal_sum));
                }
                table[i][j]+=c*(left_sum + right_sum + equal_sum);
                //printf("N %d, K %d, left small:%d, right:%d\n", j, i, smalltrees[i-2][k], table[i-1][j-1-k]);
                //printf("N %d, K %d, left :%d, right small %d\n", j, i, table[i-1][k], smalltrees[i-2][j-1-k]);
                table[i][j]%=MOD;
            }
            printf("N %d, K %d, %d\n", j, i, table[i][j]);
        }
        for (k=0;k<=N;k++) {          // we ensure that smalltrees[i-2][j] in the next i
            smalltrees[i-1][k]+=table[i-1][k]+smalltrees[i-2][k]; // iteration contains the number
            smalltrees[i-1][k]%=MOD;           // of trees smaller than i-1 and with j nodes
        }
    }

    fprintf (fout,"%d\n",table[K][N]);
    return 0;
}

