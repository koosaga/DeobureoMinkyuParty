#include<bits/stdc++.h>
using namespace std;
int N, K; // N-K match
int bulb[505050];
int room[505050];
int prv[1000005], nxt[1000005];
typedef pair<int, int> pi;

vector<pi> FUCK;

int fl(int x){
	return prv[x] = (prv[x] == x ? x : fl(prv[x]));
}

int fr(int x){
	return nxt[x] = (nxt[x] == x ? x : fr(nxt[x]));
}

int getprv(int x){
	x++;
	if(fl(x-1) == 0) return -1;
	return fl(x-1) - 1;
}

int getnxt(int x){
	x++;
	if(fr(x+1) == FUCK.size() + 1) return -1;
	return fr(x+1) - 1;
}

int erase(int x){
	x++;
	prv[x] = fl(x - 1);
	nxt[x] = fr(x + 1);
}

int main()
{
    scanf("%d%d", &N, &K);
    for(int i=1; i<=N; ++i)
        scanf("%d", bulb+i);
    for(int i=1; i<=N; ++i)
        scanf("%d", room+i);
    for(int i=1; i<=N; ++i)
    {
        FUCK.push_back(make_pair(bulb[i], i));
        FUCK.push_back(make_pair(room[i], -i));
    }
    sort(FUCK.begin(), FUCK.end());
    iota(prv, prv + FUCK.size() + 2, 0);
    iota(nxt, nxt + FUCK.size() + 2, 0);
    using pii = pair<int, int>;
    priority_queue<pii,vector<pii>, greater<pii> > Q;
    for(int i=0; i+1<FUCK.size(); i++){
    	auto it = FUCK[i];
    	auto it2 = FUCK[i+1];
    	if(it.second < 0 && it2.second > 0){
    		Q.emplace(it2.first - it.first, -it.second);
		}
	}
    long long ans = 0;
    for(int i=1; i<=N; ++i) ans += room[i];
    int cnt = 0;
    while(!Q.empty() && cnt < N-K)
    {
        //for(auto p: S)
        //{
        //    cout << p.first << " " << p.second << endl;
        //}
        //cout << endl; //
        int cost, rno; tie(cost, rno) = Q.top(); Q.pop();
        //cout << rno << endl; //
        ans += cost;
        int it = lower_bound(FUCK.begin(), FUCK.end(), pi(room[rno], -rno)) - FUCK.begin();
        int it0 = getprv(it);
        int it2 = getnxt(it);
        int it3 = getnxt(it2);
        if(it0 != -1 && it3 != -1){
        	if(FUCK[it0].second < 0 && FUCK[it3].second > 0){
        		Q.emplace(FUCK[it3].first - FUCK[it0].first, -FUCK[it0].second);
			}
		}
		erase(it);
		erase(it2);
        ++cnt;
    }
    if(cnt<N-K)
    {
        puts("NIE");
        return 0;
    }
    printf("%lld\n", ans);
}







