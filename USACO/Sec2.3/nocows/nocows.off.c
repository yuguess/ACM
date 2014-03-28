/*
ID: cmykrgb1
PROG: nocows
LANG: C++
*/
#include <stdio.h>
FILE *fi,*fo;
long int N,K;
long int dp[201][100];
 
void dynamicp(void)
{
	int i,j,k;
	for (j=1;j<=K;j++)
		for (i=1;i<=N;i+=2)
			for (k=1;k<=i-2;k++)
				dp[i][j]=(dp[i][j]+dp[k][j-1]*dp[i-1-k][j-1])%9901;
}
 
int min_node(int t) {
    if (t <= 0)
        return 0;
    else 
        return 2 * t - 1;
}

int max_node(int t) {
    if (t <= 0)
        return 0;
    else 
        return (1 << t) - 1;
}

int main(void)
{
	int i, j;
    /*
	fi=fopen("nocows.in","r");
	fo=fopen("nocows.out","w");
	fscanf(fi,"%d %d",&N,&K);
	fclose(fi);
    */
    K = 13;
    
    for (N = min_node(K); N <= max_node(K); N = N+2) { 
        for (i=1;i<=K;i++)
            dp[1][i]=1;
        dynamicp();
        printf("N: %d, K: %d, %ld\n", N, K, ((dp[N][K]+9901-dp[N][K-1])%9901));

        for (i = 0; i <= N; i++)
            for (j = 0; j <= K; j++) 
                dp[i][j]=0;
    }
	//fclose(fo);
	return 0;
}
