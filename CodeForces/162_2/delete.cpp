#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>
#define DBLE 1e-8
#define PI 3.1415926535898
#define INF (1000000000000000LL)
#define MAXN 100010
using namespace std;
long long dp[MAXN];
int on,tw;
int c[MAXN],v[MAXN];
void query(int co,int a,int b,long long va)
{
    long long tmp,t2;
    tmp=dp[co]+va*a;
    tmp=max(tmp,va*b);

    if(co!=on)
        t2=va*b+dp[on];
    else    t2=va*b+dp[tw];
    dp[co]=max(dp[co],max(tmp,t2));
    return ;
}
void change(int co)
{
    if(dp[co]>dp[on])
    {
        if(co!=on)
            tw=on;
        on=co;
    }
    else    if(dp[co]>dp[tw]&&co!=on)
        tw=co;
}
int main()
{
    //freopen("I:\\MyDocument\\Code\\input.txt","r",stdin);
    int n,q,a,b;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i)
        scanf("%d",&v[i]);
    for(int i=1;i<=n;++i)
        scanf("%d",&c[i]);
    while(q--)
    {
        for(int i=0;i<MAXN;++i)
            dp[i]=-INF;
        on=1,tw=0;
        scanf("%d%d",&a,&b);
        for(int i=1;i<=n;++i)
            query(c[i],a,b,v[i]),change(c[i]);
        cout<<max(dp[on],0LL)<<'\n';
    }
    return 0;
}
