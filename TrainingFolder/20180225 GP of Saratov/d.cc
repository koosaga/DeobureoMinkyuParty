#include <bits/stdc++.h>
using namespace std;

int t[200010];
int a[200010];
int nxt[200010];
bool unused[200010];

long long idx1[525000];
long long idx2[525000];
int bp;

const long long INF = 1e18;

void init(long long *idx, int n)
{
    for(int i=1; i<2*bp; i++)
        idx[i] = INF;
}

void add(long long *idx, int x, long long v)
{
    x += bp;
    while(x)
    {
        idx[x] = min(idx[x], 0LL + v);
        x /= 2;
    }
}

long long calc(long long *idx, int x, int y)
{
    if(y < x)
        return INF;
    
    long long r = INF;
    x += bp;
    y += bp;
    while(x < y)
    {
        if(x % 2 == 1)
            r = min(r, idx[x++]);
        if(y % 2 == 0)
            r = min(r, idx[y--]);
        x /= 2;
        y /= 2;
    }
    if(x == y)
        r = min(r, idx[x]);
    return r;
}

vector<long long> com;
int tidx(long long x)
{
    return lower_bound(com.begin(), com.end(), x) - com.begin();
}

int main()
{
    while(1)
    {
        int n, i;
        if(scanf("%d", &n) != 1)
            return 0;
        for(i=0;i<n;i++)
            scanf("%d%d", &t[i], &a[i]);
        
        for(i=0;i<n;i++)
            unused[i] = 0;
        
        int mx = a[n-1];
        for(i=n-2;i>=0;i--)
        {
            if(a[i] > mx)
            {
                nxt[i] = mx;
                mx = a[i];
            }
            else
                unused[i] = 1;
        }
        
        com.clear();
        for(i=0;i<n;i++)
            com.push_back(t[i]);
        sort(com.begin(), com.end());
        com.erase(unique(com.begin(), com.end()), com.end());
        
        for(bp = 1; bp<=n+10; bp *= 2);
        init(idx1, n+10);
        init(idx2, n+10);
        
        add(idx1, 0, 2*mx);
        add(idx2, 0, 2*mx);
        
        for(i=0;i<n;i++)
        {
            if(unused[i])
                continue;
            long long mi = min(t[i]+ calc(idx1, 0, tidx(t[i])), calc(idx2, tidx(t[i])+1, com.size()));
            
            if(i == n-1)
            {
                printf("%lld\n", mi);
            }
            else
            {
                add(idx1, tidx(mi), 2*nxt[i]);
                add(idx2, tidx(mi), mi + 2*nxt[i]);
            }
        }
    }
    return 0;
}






