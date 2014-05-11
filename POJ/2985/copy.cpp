/*
    题意：某人养了很多猫，他会把一些猫合并成一组，并且会询问第k大组有几只猫

    算法：处理集合用并查集，动态更新第K值用树状数组，具体的看注释

    2011-07-21 20:42
*/

#include <stdio.h>

#define MAXN 300000

int a[MAXN], c[MAXN + 5], f[MAXN];
int n, m;

int lowbit(int x)
{
    return x & -x;
}

int find(int x)
{
    if (x != f[x])
        f[x] = find(f[x]);
    return f[x];
}

void add(int x, int num)
{
    for ( ; x <= MAXN; x += lowbit(x))
        c[x] += num;
}

int sum(int x)
{
    int sum = 0;
    for ( ; x > 0; x -= lowbit(x))
        sum += c[x];
    return sum;
}


/*
    求第K小的值。a[i]表示值为i的个数，c[i]当然就是管辖区域内a[i]的和了。

    神奇的方法。不断逼近。每次判断是否包括（ans，ans + 1 << i]的区域，
    不是的话减掉，是的话当前的值加上该区域有的元素。
    注意MAXN是更新到的最大值，如果上面只更新到n的话取n就行了。

    乍一看循环的量是常数，难道是O（1）的吗？实际上i应该遍历到LogN，所以该算法是LogN的。比线段树、平衡树代码量少多了。
*/

int find_kth(int k)
{
    int ans = 0, cnt = 0, i;
    for (i = 20; i >= 0; i--)
    {
        ans += (1 << i);
        if (ans >= MAXN|| cnt + c[ans] >= k)
            ans -= (1 << i);
        else
            cnt += c[ans];
    }
    return ans + 1;
}


int main()
{
    int i, num, cmd, x, y, k, l, r;

    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
        f[i] = i;
    for (i = 1; i <= n; i++)
        a[i] = 1;
    add(1, n);//a[i]表示组内有i只猫的组数
    num = n;
    for (i = 1; i <= m; i++)
    {
        scanf("%d", &cmd);
        if (cmd == 0)
        {
            scanf("%d%d", &x, &y);
            x = find(x);
            y = find(y);
            if (x == y)
                continue;
            add(a[x], -1);
            add(a[y], -1);
            add(a[y] = a[x] + a[y], 1);
            f[x] = y;
            num--;//合并集合
        }
        else
        {
            scanf("%d", &k);
            printf("%d\n", find_kth(num - k + 1));//第k大就是第num - k + 1小的
        }
    }
    return 0;
}
