#include<bits/stdc++.h>
using namespace std;

bool chk[3];
int seg[3][2];
int sz;

int sta[3][2];

int g(int x, int y)
{
    return x ? g(y%x, x) : y;
}

bool jum(int x, int y)
{
    return g(x, y) == 1;
}

bool nei(int x, int y)
{
    return x == y-1 || x == y+1;
}

int cnt(int x, int y)
{
    if(nei(x, y))
        return 0;
    if(jum(x, y))
        return 1;
    return 100;
}

int res;
int ans[3][2];
int a, b;

void f(int x)
{
    if(x == sz)
    {
        int c = 0;
        c += cnt(a, sta[0][0]);
        for(int i=0;i<sz-1;i++)
            c += cnt(sta[i][1], sta[i+1][0]);
        c += cnt(sta[sz-1][1], b);
        
        if(c >= res)
            return;
        
        res = c;
        for(int i=0;i<sz;i++)
            for(int j=0;j<2;j++)
                ans[i][j] = sta[i][j];
        return;
    }
    
    for(int i=0;i<sz;i++)
    {
        if(chk[i])
            continue;
        
        sta[x][0] = seg[i][0];
        sta[x][1] = seg[i][1];
        chk[i] = 1;
        f(x+1);
        
        sta[x][0] = seg[i][1];
        sta[x][1] = seg[i][0];
        f(x+1);
        
        chk[i] = 0;
    }
}

void process()
{
    res = 100;
    int n;
    scanf("%d%d%d", &n, &a, &b);
    
    if(n == 2)
    {
        printf("0\n%d %d\n", a, b);
        return;
    }
    
    int x, y;
    x = min(a, b);
    y = max(a, b);
    
    sz = 0;
    if(x != 1)
    {
        seg[sz][0] = 1;
        seg[sz][1] = x-1;
        sz++;
    }
    if(y != x+1)
    {
        seg[sz][0] = x+1;
        seg[sz][1] = y-1;
        sz++;
    }
    if(y != n)
    {
        seg[sz][0] = y+1;
        seg[sz][1] = n;
        sz++;
    }
    
    memset(chk, 0, sizeof chk);
    f(0);
    
    if(res >= 50)
        printf("-1\n");
    else
    {
        printf("%d\n", res);
        printf("%d ", a);
        for(int i=0;i<sz;i++)
        {
            if(ans[i][0] <= ans[i][1])
            {
                for(int j=ans[i][0];j<=ans[i][1];j++)
                    printf("%d ", j);
            }
            else
            {
                for(int j=ans[i][0];j>=ans[i][1];j--)
                    printf("%d ", j);
            }
        }
        printf("%d\n", b);
    }
}

int main()
{
    int t, i;
    scanf("%d", &t);
    for(i=0;i<t;i++)
        process();
    return 0;
}
