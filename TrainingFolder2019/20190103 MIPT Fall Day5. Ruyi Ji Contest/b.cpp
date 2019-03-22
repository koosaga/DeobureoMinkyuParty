#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = (1<<22);
const int mod = 998244335;

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x < MAXN){
			tree[x] += v;
			while(tree[x] >= mod) tree[x] -= mod;
			x += x & -x;
		}
	}
	int query(int x){
		lint ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret % mod;
	}
}bit;

int n, m, k;
int dp[MAXN];
char buf[2222];

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		vector<pi> v;
		scanf("%d %d %d",&n,&m,&k);
		for(int i=0; i<n; i++){
			scanf("%s", buf);
			for(int j=1; buf[j]; j++){
				if(buf[j-1] != buf[j]){
					int x = i * k;
					int y = j;
					v.emplace_back(x - y, x + y);
				}
			}
		}
		sort(v.begin(), v.end(), [&](const pi &a, const pi &b){
			return pi(a.first, -a.second) < pi(b.first, -b.second);
		});
		lint dap = 1;
		for(int i=0; i<v.size(); i++){
			dp[i] = 1 + bit.query(v[i].second - 1);
			bit.add(v[i].second, dp[i]);
			dap += dp[i];
		}
		dap %= mod;
		for(int i=0; i<v.size(); i++) bit.add(v[i].second, mod - dp[i]);
		printf("%lld\n", dap);
	}
}
