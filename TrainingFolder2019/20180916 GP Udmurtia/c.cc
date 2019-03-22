#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using pi = pair<int, int>;
using lint = long long;

vector<pi> ev;
int n;
lint cnt[MAXN], dnt[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x, l, r;
		scanf("%*d %d %d",&l,&r);
		ev.push_back(pi(l, 1));
		ev.push_back(pi(r, -1));
	}
	sort(ev.begin(), ev.end());
	for(int i=1; i<ev.size(); i++){
		ev[i].second += ev[i-1].second;
		if(ev[i].first != ev[i-1].first){
			cnt[ev[i-1].second] += ev[i].first - ev[i-1].first;
		}
	}
	memcpy(dnt, cnt, sizeof(dnt));
	for(int i=n; i; i--){
		dnt[i] *= i;
		dnt[i] += dnt[i + 1];
		cnt[i] += cnt[i +1];
	}
	int q; scanf("%d",&q);
	while(q--){
		int l, r; scanf("%d %d",&l,&r);
		int x = l + r + 2;
		printf("%lld\n", dnt[x] - cnt[x] * x);
	}
}
