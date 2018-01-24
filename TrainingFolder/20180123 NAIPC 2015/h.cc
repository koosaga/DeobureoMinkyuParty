#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+10;

int N;

int parent[MAXN];
int buyprice[MAXN];
int minbuyprice[MAXN];
int totalminbuyprice[MAXN];
int sellprice[MAXN];
int number[MAXN];
bool visit[MAXN];
bool incycle[MAXN];

vector<vector<int> > cycles;
long long calcCycleRemovedPrice()
{
    long long ans = 0;
    for(auto& cycle: cycles)
    {
        if(cycle.size() == 1) continue;
        int mindec = 0x3f3f3f3f;
        for(auto x: cycle)
            mindec = min(minbuyprice[x] - totalminbuyprice[x], mindec);
        
        ans += mindec;
    }
    return ans;
}
long long calcExpectedPrice()
{
    for(int i=1; i<=N; ++i)
    {
        totalminbuyprice[parent[i]] = 
            min(totalminbuyprice[parent[i]], buyprice[i]);
        if(!incycle[i])
        {
            minbuyprice[parent[i]] = 
                min(minbuyprice[parent[i]], buyprice[i]);
        }
    }
    long long ans = 0;
    for(int i=1; i<=N; ++i)
    {
        ans += 1LL * (sellprice[i] - totalminbuyprice[i])
                   * number[i];
    }
    return ans;
}
void getCycle()
{
    for(int i=1; i<=N; ++i)
    {
        if(!visit[i])
        {
            set<int> S;
            int s = i;
            while(!visit[s])
            {
                S.insert(s);
                visit[s] = true;
                s = parent[s];
            }
            if(S.find(s) == S.end()) continue;
            //s is in cycle
            vector<int> cycle;
            cycle.push_back(s);
            incycle[s] = true;
            int ts = parent[s];
            while(ts != s)
            {
                cycle.push_back(ts);
                incycle[ts] = true;
                ts = parent[ts];
            }
            cycles.push_back(cycle);
        }
    }
    return;
}

int main()
{
    
    scanf("%d", &N);
    for(int i=1; i<=N; ++i)
    {
        scanf("%d", parent+i);
        scanf("%d", buyprice+i);
        scanf("%d", sellprice+i);
        scanf("%d", number+i);
        minbuyprice[i] = totalminbuyprice[i] = sellprice[i];
    }
    
    getCycle();
    long long ret = calcExpectedPrice() - calcCycleRemovedPrice();
    printf("%lld\n", ret);
}
