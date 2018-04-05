#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 200005;
const int mod = 1e9 + 7;

struct node{
	int l, r;
	lint dist;
	bool operator<(const node &n)const{
		return dist > n.dist;
	}
};

int n;
lint dist[MAXN];
int r[MAXN], s[MAXN], t[MAXN];

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d",&n);
		for(int i=1; i<=n; i++) scanf("%d",&s[i]);
		for(int i=1; i<=n; i++) scanf("%d",&t[i]);
		for(int i=1; i<=n; i++) scanf("%d",&r[i]);
		set<int> st;
		priority_queue<node> pq;
		for(int i=1; i<=n; i++) st.insert(i), dist[i] = -1;
		st.erase(1);
		dist[1] = 0;
		pq.push({s[1] + 1, t[1] + 1, r[1]});
		while(!pq.empty()){
			auto x = pq.top();
			pq.pop();
			auto it = st.lower_bound(x.l);
			while(it != st.end() && *it <= x.r){
				dist[*it] = x.dist;
				pq.push({*it - t[*it], *it - s[*it], x.dist + r[*it]});
				pq.push({*it + s[*it], *it + t[*it], x.dist + r[*it]});
				it = st.erase(it);
			}
		}
		for(int i=1; i<=n; i++) printf("%lld ", dist[i]);
	}
}
