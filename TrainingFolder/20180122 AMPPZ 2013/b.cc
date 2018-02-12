#include <bits/stdc++.h>
using namespace std;

int par[2250000];

int root(int x)
{
    return x == par[x] ? x : (par[x] = root(par[x]));
}

bool merge(int x, int y)
{
    x = root(x);
    y = root(y);
    if(x == y)
        return 0;
    
    par[x] = y;
    return 1;
}

int num[1510][1510];

int n, o;
int f(int x, int y)
{
    if(x == 0 || x == n || y == 0 || y == n)
        return o;
    
    return (x-1)*(n-1) + y;
}

int main()
{
    int k, i, j;
    scanf("%d%d", &n, &k);
    
    o = (n-1)*(n-1) + n;
    for(i=0;i<=n;i++)
        for(j=0;j<=n;j++)
            num[i][j] = f(i, j);
    
    for(i=1;i<=o;i++)
        par[i] = i;
    
    bool ans = 1;
    for(i=0;i<k;i++)
    {
        char d;
        int a, b;
        
        scanf("%d%d %c", &a, &b, &d);
        if(ans)
            scanf("%*d%*d %*c");
        else
            scanf("%d%d %c", &a, &b, &d);
        
        if(d == 'N')
        {
            if(merge(num[a][b], num[a-1][b]))
                ans = 1;
            else
                ans = 0;
        }
        else
        {
            if(merge(num[a][b], num[a][b-1]))
                ans = 1;
            else
                ans = 0;
        }
        
        if(ans)
            printf("TAK\n");
        else
            printf("NIE\n");
    }
    return 0;
}
