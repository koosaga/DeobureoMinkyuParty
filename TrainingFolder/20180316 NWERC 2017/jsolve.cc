#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+10;
int N;
int a[MAXN];
int s[MAXN];
long long ss[MAXN];
int sum(int f, int e)
{
    return s[e] - s[f-1];
}
long long indsum(int f, int e)
{
    return ss[e] - ss[f-1];
}

inline long long floordiv(long long a, long long b)
{
    long amodb = a % b;
    if(amodb < 0) amodb += b;
    a -= amodb;
    return a / b;
}

pair<pair<int, int>, int> getInterval(int s, int e)
{
    int cnt = sum(s, e);
    long long ind = indsum(s, e);
    long long cnts = ind - cnt*(cnt-1LL)/2;
    int leftend = floordiv(cnts, cnt);
    long long expsum = leftend * (long long)cnt + cnt*(cnt-1LL)/2;
    //printf("%d %lld %lld %d %lld\n", cnt, ind, cnts, leftend, expsum);
    if(expsum == ind) return make_pair(make_pair(leftend, leftend + cnt-1), -1);
    else return make_pair(make_pair(leftend, leftend + cnt), leftend + cnt - (ind-expsum));
}
pair<int, int> getInterval(pair<int, int> X)
{
    return getInterval(X.first, X.second).first;
}
char ansv[MAXN+1];
char buf[MAXN+1];
int main()
{
    scanf("%s", buf);
    N = strlen(buf);
    for(int i=0; i<N; ++i)
    {
        a[1+i] = buf[i] - '0';
        s[1+i] = s[i] + a[1+i];
        ss[1+i] = ss[i] + 1LL*(1+i)*a[1+i];
        ansv[i+1] = '0';
    }
    vector< pair<int, int> > possible_segments;
    for(int i=1; i<=N; ++i)
    {
        if(a[i] == 0) continue;
        int j;
        for(j=i; j<=N; ++j)
            if(a[j] == 0) break;
        possible_segments.emplace_back(i, j-1);
        i = j;
    }
    list<pair<int, int> > L = list<pair<int, int> >(possible_segments.begin(), possible_segments.end());
    auto it = L.begin();
    while(it != L.end())
    {
        auto itn = it; ++itn; if(itn == L.end()) break;
        auto nowint = getInterval(*it);
        auto nexint = getInterval(*itn);
        if(nowint.second >= nexint.first)
        {
            *it = make_pair(it->first, itn->second);
            L.erase(itn);
            if(it != L.begin()) --it;
        }
        else ++it;
    }
    for(auto x: L)
    {
        auto ans = getInterval(x.first, x.second);
        int s = ans.first.first, e = ans.first.second, t = ans.second;
        //printf("%d %d -> %d %d %d\n", x.first, x.second, s, e, t);
        if(s >= 1 && e <= N) //sane
        {
            for(int i=s; i<=e; ++i) ansv[i] = '1';
            if(t != -1) ansv[t] = '0';
        }
        else
        {
            s = max(1, s);
            e = min(e, N);
            long long isum = indsum(x.first, x.second);
            //printf("%lld\n", isum);
            for(int i=s; i<=e; ++i)
            {
                ansv[i] = '1';
                isum -= i;
            }
            //printf("%d %d %lld\n", s, e, isum);
            for(int i=s; i<=e; ++i)
                if((isum + i)%(e+1) == 0) ansv[i] = '0';
        }
    }
    puts(ansv+1);
    return 0;
}








