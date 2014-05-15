#include<stdio.h>
using namespace std;
const int maxn=1000005;
int x[maxn],y[maxn],a[maxn],n,k,i,tail,now;
int main()
{
  scanf("%ld%ld",&n,&k);
  for (i=1;i<=n;i++) scanf("%ld",&a[i]);
  x[1]=a[1];y[1]=1;tail=1;now=1;
  for (i=2;i<k;i++)
  {
    while (a[i]<x[tail]&&tail>0) tail--;
    x[++tail]=a[i];y[tail]=i;
  }
  for (i=k;i<=n;i++)
  {
    while (a[i]<x[tail]&&tail>0) tail--;
    x[++tail]=a[i];y[tail]=i;if (now>tail) now=tail;
    while (y[now]<i-k+1) now++;
    if (i<n) printf("%ld ",x[now]);else printf("%ld\n",x[now]);
  }
  x[1]=a[1];y[1]=1;tail=1;now=1;
  for (i=2;i<k;i++)
  {
    while (a[i]>x[tail]&&tail>0) tail--;
    x[++tail]=a[i];y[tail]=i;
  }
  for (i=k;i<=n;i++)
  {
    while (a[i]>x[tail]&&tail>0) tail--;
    x[++tail]=a[i];y[tail]=i;if (now>tail) now=tail;
    while (y[now]<i-k+1) now++;
    if (i<n) printf("%ld ",x[now]);else printf("%ld\n",x[now]);
  }
  return 0;
}
