#include<bits/stdc++.h>
using namespace std;
const int MAXN = 25252;
unordered_map<string, int> M;

vector<pair<int, pair<int, int> > > conn[MAXN];
int B, N;
bool visit[MAXN];
int main()
{
    cin.sync_with_stdio(false);
    cin.tie(0);
    cout.sync_with_stdio(false);
    cin >> B >> N;
    set<int> base;
    int tp = 0;
    for(int i=0; i<N; ++i)
    {
        string a, b, percent_star_s;
        int cost, prestidge;
        cin >> a >> b >> percent_star_s >> cost >> prestidge;
        if(M.find(a) == M.end())
        {
            M[a] = tp++;
        }
        if(M.find(b) == M.end())
        {
            base.insert(tp);
            M[b] = tp++;
        }
        base.erase(M[a]);
        conn[M[b]].emplace_back(M[a],make_pair(cost, prestidge));
    }
    
    using plli = pair<pair<long long, long long>, int>; //cost(low), prestidge(high)
    vector<pair<long long, long long> > V;
    priority_queue<plli> Q;
    for(auto x: base)
        Q.emplace(make_pair(-0ll, 0ll), x);
    while(!Q.empty())
    {
        auto tmp = Q.top(); Q.pop();
        long long cost = -tmp.first.first, pres = tmp.first.second;
        int index = tmp.second;
        if(visit[index]) continue; visit[index] = true;
        if(0 < cost && cost <= B) V.emplace_back(cost, pres);
        for(auto x: conn[index])
        {
            long long newcost = cost + x.second.first;
            long long newprest = pres + x.second.second;
            int index = x.first;
            Q.emplace(make_pair(-newcost, newprest), index);
        }
    }
    vector<int> pr(B+1);
    for(auto x: V)
    {
        int cost = x.first, value = x.second;
        for(int i=B; i>=cost; --i)
            pr[i] = max(pr[i], pr[i-cost] + value);
    }
    int ans = max_element(pr.begin(), pr.end()) - pr.begin();
    cout << pr[B] << endl << ans << endl;
}






















