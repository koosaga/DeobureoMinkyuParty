#include<bits/stdc++.h>
using namespace std;


char f[1010];
long long rll()
{
    scanf("%s", f);

    long long ans = 0;
    for(int i=0; f[i]; ++i)
    {
        ans = ans*2;
        ans += f[i] - '0';
    }
    return ans;
}
inline int dist(long long a, long long b)
{
    return __builtin_popcountll(a^b);
}
int N, K;
long long arr[1010101];
set<long long> black;
set<long long> gray;
bool fromto(long long s, long long e)
{
    black.clear(); gray.clear();
    for(int i=0; i<K; ++i) black.insert(arr[i]);
    gray.insert(s);
    while(black.size() + gray.size() <= N*K && !gray.empty())
    {
        long long v = *gray.begin(); gray.erase(v); black.insert(v);
        if(v==e)
        {
            puts("TAK");
            exit(0);
        }
        for(int i=0; i<N; ++i)
        {
            long long targ = v^(1LL<<i);
            if(black.find(targ) == black.end() && gray.find(targ) == gray.end())
                gray.insert(targ);
        }
    }
    if(black.size() + gray.size() > N*K) return true;
    return false;
}

int main()
{
    long long s, e;
    scanf("%d%d",&N,&K);
    s = rll(); e = rll();
    if(s==e)
    {
        puts("TAK"); return 0;
    }
    for(int i=0; i<K; ++i)
        arr[i] = rll();
    if(fromto(s, e) && fromto(e, s)) puts("TAK");
    else puts ("NIE");
    return 0;
}

