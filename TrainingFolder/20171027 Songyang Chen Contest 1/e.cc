#include<bits/stdc++.h>
using namespace std;


long long mindist[202020];
long long solve(long long K, vector<long long> V)
{
    if(K<=0) return 0;
    sort(V.begin(), V.end());
    long long mod = V.back();
    V.pop_back();
    memset(mindist, 0x3f, sizeof(mindist));
    
    priority_queue<long long, vector<long long>, greater<long long> > Q;
    Q.emplace(0);
    while(!Q.empty())
    {
        long long x = Q.top(); Q.pop();
        if(mindist[x%mod] != 0x3f3f3f3f3f3f3f3fll)
            continue;
        mindist[x%mod] = x/mod;
        for(long long y: V)
            Q.emplace(x+y);
    }
    for(;;++K)
    {
        //printf("%lld\n", K);
        if(mindist[K%mod]<=K/mod)
            return K;
    }
}

int main()
{
    long long K, a, b, c, d;
    scanf("%lld%lld%lld%lld%lld", &K, &a, &b, &c, &d);
    long long ans = 0x3f3f3f3f3f3f3f3fll;
    
    vector<long long> V;

    V.clear();
    
    
    V.push_back(2*a);
    ans = min(ans, 2*a+solve(K-2*a, V));

    V.push_back(2*d);
    ans = min(ans, 2*a+2*d+solve(K-(2*a+2*d), V));

    V.push_back(2*c);
    ans = min(ans, 2*a+2*d+2*c+solve(K-(2*a+2*d+2*c), V));

    V.clear();
    
    V.push_back(2*b);
    ans = min(ans, 2*b+solve(K-2*b, V));

    V.push_back(2*c);
    ans = min(ans, 2*b+2*c+solve(K-(2*b+2*c), V));

    V.push_back(2*d);
    ans = min(ans, 2*b+2*c+2*d+solve(K-(2*b+2*c+2*d), V));
    
    
    V.push_back(2*a);
    
    V.push_back(a+b+c+d);
    ans = min(ans, a+b+c+d+solve(K-(a+b+c+d), V));
    
    printf("%lld\n", ans);
    return 0;
}

