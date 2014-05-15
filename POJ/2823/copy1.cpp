#include<cstdio>
using namespace std;
const int maxn=1000005;
int x[maxn],y[maxn],a[maxn],n,k,i,tail,head;
int main()
{
  scanf("%ld%ld",&n,&k);
  for (i=1;i<=n;i++) scanf("%ld",&a[i]);
  x[1]=a[1];y[1]=1;head=1;tail=1;
  for (i=2;i<k;i++)
  {
    while (a[i]<x[tail]&&tail>=head) tail--;
    x[++tail]=a[i];y[tail]=i;
  }
  for (i=k;i<=n;i++)
  {
    while (a[i]<x[tail]&&tail>=head) tail--;
    x[++tail]=a[i];y[tail]=i;
    while (y[head]<i-k+1) head++;
    if (i<n) printf("%ld ",x[head]);else printf("%ld\n",x[head]);
  }
  x[1]=a[1];y[1]=1;head=1;tail=1;
  for (i=2;i<k;i++)
  {
    while (a[i]>x[tail]&&tail>=head) tail--;
    x[++tail]=a[i];y[tail]=i;
  }
  for (i=k;i<=n;i++)
  {
    while (a[i]>x[tail]&&tail>=head) tail--;
    x[++tail]=a[i];y[tail]=i;
    while (y[head]<i-k+1) head++;
    if (i<n) printf("%ld ",x[head]);else printf("%ld\n",x[head]);
  }
  return 0;
}
