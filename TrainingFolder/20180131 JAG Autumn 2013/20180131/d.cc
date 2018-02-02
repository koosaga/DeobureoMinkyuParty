#include<bits/stdc++.h>
using namespace std;

vector<int> arr[100010];
bool chk[100010];
vector<int> siz;

int dfs(int x)
{
    int r = 1;
    chk[x] = 1;
    for(int y : arr[x])
        if(!chk[y])
            r += dfs(y);
    return r;
}

const int mod = 1000000007;

int pw(int a, int x)
{
    if(!x)
        return 1;
    if(x%2)
        return 1LL * pw(a, x-1) * a % mod;
    int t = pw(a, x/2);
    return 1LL * t * t % mod;
}

int main()
{
    int n, m, x, y, i;
    scanf("%d%d", &n, &m);
    for(i=0;i<m;i++)
    {
        scanf("%d%d", &x, &y);
        arr[x].push_back(y);
        arr[y].push_back(x);
    }
    
    for(i=1;i<=n;i++)
        if(!chk[i])
            siz.push_back(dfs(i));
    
    int c = siz.size();
    int res;
    
    if(c == n)
        res = pw(2, c);
    else
        res = (pw(2, c) + 1) % mod;
    printf("%d\n", res);
    
    return 0;
}
