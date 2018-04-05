#include<bits/stdc++.h>
using namespace std;

int arr[500010];
int idx[2000010];
int bp;

void add(int x, int v)
{
    x += bp;
    while(x)
    {
        idx[x] = max(idx[x], v);
        x /= 2;
    }
}

int que(int x, int y)
{
    x += bp;
    y += bp;
    int r = 0;
    while(x < y)
    {
        if(x % 2 == 1)
            r = max(r, idx[x++]);
        if(y % 2 == 0)
            r = max(r, idx[y--]);
        x /= 2;
        y /= 2;
    }
    if(x == y)
        r = max(r, idx[x]);
    return r;
}

vector<int> com;
int f(int x)
{
    return lower_bound(com.begin(), com.end(), x) - com.begin();
}

int main()
{
    int res = 0;
    for(int b=0;b<2;b++)
    {
        int n, i;
        scanf("%d", &n);
        for(i=0;i<n;i++)
            scanf("%d", &arr[i]);
        
        com.clear();
        for(i=0;i<n;i++)
            com.push_back(arr[i]);
        sort(com.begin(), com.end());
        com.erase(unique(com.begin(), com.end()), com.end());
        
        for(bp = 1; bp <= n; bp *= 2);
        if(b == 1)
            memset(idx, 0, sizeof idx);
        
        int rr = 0;
        for(i=0;i<n;i++)
        {
            int t = 1 + que(0, f(arr[i]));
            rr = max(rr, t);
            add(f(arr[i]), t);
        }
        res += rr;
    }
    printf("%d", res);
    return 0;
}
