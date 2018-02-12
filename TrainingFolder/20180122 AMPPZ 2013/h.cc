#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
vector<pair<int, int> > conn[MAXN];
int N, M;
vector<pair<long long, long long> > freerange[MAXN];
set<int> nonvisit[MAXN];
set<int> realvisit[MAXN];
map<int, int> trap[MAXN];
int getInterval(int target, long long time)
{
    auto it = lower_bound(freerange[target].begin(),
                          freerange[target].end(),
                          make_pair(time, (long long)1e16));
    return it - freerange[target].begin() - 1;
}
long long Dijkstra()
{
    //Allahu Akbar
       
    using pli = pair<long long, int>;
    priority_queue<pli, vector<pli>, greater<pli> > Q;
    Q.emplace(1, 1);
    while(!Q.empty())
    {
        long long dist; int v;
        tie(dist, v) = Q.top(); Q.pop();
        int interval = getInterval(v, dist);
        
        //printf("%lld %d\n", dist, v);
        
        if(realvisit[v].find(interval) 
            == realvisit[v].end()) continue;
        realvisit[v].erase(interval);
        nonvisit[v].erase(interval);
        if(v == N)
            return dist - 1 ;
        for(auto E: conn[v])
        {
            int length, target;
            tie(target, length) = E;
            long long start = dist + length;
            long long end = freerange[v][interval].second + length;
            
            int targetint = getInterval(target, start);
       
            for(auto it = nonvisit[target].lower_bound(targetint); it != nonvisit[target].end(); )
            {
                long long ts = freerange[target][*it].first;
                long long te = freerange[target][*it].second;
                if(te < start)
                {
                    ++it;
                    continue;
                }
                if(ts > end) break;
                if(ts > start)
                {
                    Q.emplace(ts, target);
                    nonvisit[target].erase(it++);
                }
                else // ts <= start
                {
                    Q.emplace(start, target);
                    ++it;
                }
            }
        }
    }    
       
    return -1LL;   
}
void Debug()
{
    return;
    for(int i=1; i<=N; ++i)
    {
        for(auto x: conn[i])
            printf("(%d, %d)", x.first, x.second);
        puts("");
        for(auto x: freerange[i])
            printf("(%lld, %lld)", x.first, x.second);
        puts("");
        
    }
}
int main()
{
    scanf("%d%d", &N, &M);
    for(int i=0; i<M; ++i)
    {
        int s, e, x;
        scanf("%d%d%d", &s, &e, &x);
        conn[s].emplace_back(e, x);
    }
    int Q; scanf("%d", &Q);
    for(int i=0; i<Q; ++i)
    {
        int w, s, k; scanf("%d%d%d", &w, &s, &k);
        trap[w][s] = trap[w][s] + 1;
        trap[w][k+1] = trap[w][k+1] - 1;
    }
    for(int i=1; i<=N; ++i)
    {
        int pt = 0;
        int acc = 0;
        int tp = 0;
        for(auto x: trap[i])
        {
            int v = x.second;
            if(acc == 0 && acc + v != 0)
            {
                freerange[i].emplace_back(pt, x.first-1);
                realvisit[i].insert(tp);
                nonvisit[i].insert(tp++);
            }
            if(acc != 0 && acc + v == 0)
            {
                pt = x.first;
            }
            acc += v;
        }
        freerange[i].emplace_back(pt, (long long)1e15);
        nonvisit[i].insert(tp);
        realvisit[i].insert(tp);
    }
    Debug();
    long long ngm = Dijkstra();
    if(ngm == -1) puts("NIE");
    else printf("%lld\n", ngm);
    
    return 0; 
}
/*
example
                                                 ^
(2, 3)(4, 13)
(0, 1)(5, 7)(9, 1000000000000000)
(3, 1)(4, 2)
(0, 5)(8, 9)(12, 1000000000000000)
(2, 2)
(0, 1000000000000000)
(5, 1)
(0, 5)(8, 1000000000000000)

(0, 1000000000000000)
0 1
2 3
4 2
7 1
8 2
11 1
12 2
NIE

*/
