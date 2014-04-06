#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int MAXD = 10010;
bool g[MAXN][MAXN];
int n, seq[MAXD], dp[MAXD], pre[MAXD], num[MAXD];
int row, col;

void solve()
{
    n = 0;
    for (int i = 1; i <= row; ++i)
        for (int j = 1; j <= col; ++j)
            if (g[i][j])
                seq[n++] = (i - 1) * col + j - 1;

    if (seq[n-1] != col * row - 1)
        seq[n++] = row * col - 1;

    memset(pre, -1, sizeof(pre));
    for (int i = 0; i < n; ++i)
    {
        dp[i] = 1, num[i] = 1;

        printf("seq %d %d\n", i, seq[i]);
        for (int j = 0; j < i; ++j) {
          
            if ((seq[i]%col) >= (seq[j]%col))
            {
                if (dp[i] < dp[j] + 1)
                    dp[i] = dp[j] + 1,
                    num[i] = num[j],
                    pre[i] = j;
                else if (dp[i] == dp[j] + 1)
                    num[i] += num[j];
            }
    }
        printf("%d %d\n", i, dp[i]); 
    }        
    if (!g[row][col])
        --dp[n-1];
}

void outpath(int u)
{
    if (pre[u] != -1)
        outpath(pre[u]);
    if (u != n - 1 || g[row][col])
        printf(" %d", seq[u] + 1);
}

int main()
{
    int cases = 0;
    while (scanf("%d %d", &row, &col))
    {
        if (row == -1 && col == -1) 
            break;

        int x, y;
        memset(g, false, sizeof(g));
        while (scanf("%d %d", &x, &y) && x && y)
            g[x][y] = true;

        solve();

        printf("CASE#%d: %d %d", ++cases, dp[n-1], num[n-1]);
        outpath(n - 1);
        printf("\n");
    }
    return 0;
}
