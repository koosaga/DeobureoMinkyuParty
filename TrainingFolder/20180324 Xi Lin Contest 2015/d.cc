#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 2005;
const int mod = 1e9 + 7;
#define real fuck












static char buf[1<<19];
static int idx = 0;
static int bytes = 0;
static inline int _read()
{
	if(!bytes || idx == bytes)
	{
		bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
		idx = 0;
	}
	return buf[idx++];
}
static inline int _readInt()
{
	int x = 0, s = 1;
	int c = _read();
	while(c<=32) c= _read();
	while(c>32) x = 10*x+(c-'0'), c = _read();
	return x;
}













vector<pi> gph[MAXN];
int n, m;

int arr[MAXN], pa;
lint real[MAXN * MAXN];
int dep[MAXN];

int dfs(int x, int p){
	dep[x] = 0;
	int fuck = -1;
	int ret = 0;
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		dfs(i.second, x);
		if(ret <= dep[i.second] + i.first){
			ret = dep[i.second] + i.first;
			fuck = i.second;
		}
	}
	dep[x] = ret;
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		if(i.second == fuck) continue;
		arr[pa++] = dep[i.second] + i.first;
	}
	return dep[x];
}

int main(){
	int tc = _readInt();
	while(tc--){
		n = _readInt();
		m = _readInt();
		for(int i=1; i<=n; i++) gph[i].clear();
		for(int i=0; i<n-1; i++){
			int s, e, x;
			s = _readInt();
			e = _readInt();
			x = _readInt();
			gph[s].push_back(pi(x, e));
			gph[e].push_back(pi(x, s));
		}
		int ptr = 0;
		for(int i=1; i<=n; i++){
			int W = _readInt();
			pa = 0;
			arr[pa++] = dfs(i, -1);
			for(int j=0; j<pa; j++){
				real[ptr++] = 1ll * W * arr[j];
			}
		}
		lint ans = 0;
		if(ptr <= m){
			for(int i=0; i<ptr; i++) ans += real[i];
		}
		else{
			int kth = ptr - m;
			nth_element(real, real + kth, real + ptr);
			for(int i=0; i<ptr; i++){
				if(real[kth] < real[i]) ans += real[i], m--;
			}
			ans += 1ll * real[kth] * m;
		}
		printf("%lld\n", ans);
	}
}
