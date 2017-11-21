#include<bits/stdc++.h>
using namespace std;
long long ipow(long long a, long long b, long long p)
{
    long long ans = 1;
    while(b)
    {
        if(b&1) ans = (ans*a)%p;
        a = (a*a)%p;
        b >>= 1;
    }
    return ans;
}

int prr(int p)
{
    vector<int> factors;
    int phip = p-1;
    for(int i=2; i*i<=phip; ++i)
    {
        if(phip%i == 0)
        {
            factors.push_back(i);
            while(phip%i==0)
                phip /= i;  
        }
    }
    if(phip != 1) factors.push_back(phip);
    for(int i=2;i<p; ++i)
    {
        bool isans = true;
        for(int x: factors)
        {
            if(ipow(i,(p-1)/x,p)==1)
            {
                isans = false;
                break;
            }
        }
        if(isans)
        {
            //printf("%d %d\n", p, i);
            return i;
            }
    }
    assert(0);
}

int arr[1010101];

pair<int, int> solve(int n, int p)
{
    const long long xn = prr(p);
    const long long x = ipow(xn, n, p);
    long long xpn = 1;
    long long xp = 1;
    pair<int, int> ans = make_pair(-1, -1);
    int cnt = 0;
    do
    {
        ++cnt;
        arr[xp] = xpn;
        if(arr[xp-1] != 0)
        {
            ans = make_pair(arr[xp-1], arr[xp]);
            break;
        }
        if(arr[xp+1] != 0)
        {
            ans = make_pair(arr[xp], arr[xp+1]);
            break;
        }
        
        xp *= x;
        xpn *= xn;
        xp %= p;
        xpn %= p; 
    }while(xp!=1);
    /*
    memset(arr, 0, sizeof(arr));
    if(false){*/
        xp = 1;
        for(int i=0; i<cnt; ++i)
        {
            arr[xp] = 0;
            xp *= x;
            xp %= p;
        }
    //}
    return ans;
}


map<pair<int, int>, pair<int, int> > M;
int main()
{
    freopen("fermat.in", "r", stdin);
    freopen("fermat.out", "w", stdout);
    int T;
    scanf("%d", &T);
    memset(arr, 0, sizeof(arr));
    while(T--)
    {
        int n, p;
        scanf("%d%d", &n, &p);
        if(p==2)
        {
            puts("-1"); continue;
        }
        if(M.find(make_pair(n, p)) == M.end())
            M[make_pair(n, p)] = solve(n, p);
        
        auto ans = M[make_pair(n, p)];
        if(ans.first==-1) puts("-1");
        else printf("1 %d %d\n", ans.first, ans.second);
    }
}
