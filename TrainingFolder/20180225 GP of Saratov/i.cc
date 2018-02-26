#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 400005;

namespace sfxarray{
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
	void solve(int n, char *str, int *sfx, int *rev, int *lcp){
		int p = 1;
		memset(ord, 0, sizeof(ord));
		for(int i=0; i<n; i++){
			sfx[i] = i;
			ord[i] = str[i];
		}
		int pnt = 1;
		while(true){
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++) cnt[ord[min(i + p, n)]]++;
			for(int i=1; i<=n || i<=255; i++){
				cnt[i] += cnt[i-1];
			}
			for(int i=n-1; i>=0; i--){
				aux[--cnt[ord[min(i + p, n)]]] = i;
			}
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++) cnt[ord[i]]++;
			for(int i=1; i<=n || i<=255; i++){
				cnt[i] += cnt[i-1];
			}
			for(int i=n-1; i>=0; i--){
				sfx[--cnt[ord[aux[i]]]] = aux[i];
			}
			if(pnt == n) break;
			pnt = 1;
			nord[sfx[0]] = 1;
			for(int i=1; i<n; i++){
				if(ord[sfx[i-1]] != ord[sfx[i]] || 
					ord[sfx[i-1] + p] != ord[sfx[i] + p]){
					pnt++;
				}
				nord[sfx[i]] = pnt;
			}
			memcpy(ord, nord, sizeof(int) * n);
			p <<= 1;
		}
		for(int i=0; i<n; i++) rev[sfx[i]] = i;
		int h = 0;
		for(int i=0; i<n; i++){
			if(rev[i]){
				int prv = sfx[rev[i] - 1];
				while(str[prv + h] == str[i + h]) h++;
				lcp[rev[i]] = h;
			}
			if(h) h--;
		}
	}
}

int n, q;
char str[MAXN];
int sfx[MAXN], rev[MAXN], lcp[MAXN];
int spt[19][MAXN], lg[MAXN];

int query(int s, int e){
	int l = lg[e-s+1];
	return min(spt[l][s], spt[l][e-(1<<l)+1]);
}

int glcp(int s, int e){
	if(s == e) return n - s;
	s = rev[s];
	e = rev[e];
	if(s > e) swap(s, e);
	return query(s + 1, e);
}

bool cmp(pi s, pi e){
	if(s.second - s.first > e.second - e.first){
		return !cmp(e, s);
	}
	int lc = glcp(s.first, e.first);
	if(lc >= s.second - s.first + 1){
		if(e.second - e.first == s.second - s.first){
			return false;
		}
		return true;
	}
	return str[s.first + lc] < str[e.first + lc];
}

bool prefix(pi s, pi e){
	if(s.second - s.first > e.second - e.first){
		return false;	
	}
	int lc = glcp(s.first, e.first);
	return lc >= s.second - s.first + 1;
}

bool same(pi s, pi e){
	return prefix(s, e) && e.second - e.first == s.second - s.first;
}

int k, mod, par[MAXN], cnt[MAXN];
vector<int> gph[MAXN];

lint dfs(int x){
	lint ret = 1;
	for(auto &i : gph[x]){
		ret *= dfs(i);
		ret %= mod;
	}
	ret += cnt[x];
	ret %= mod;
	return ret;
}

int solve(int n){
	for(int i=1; i<=n; i++){
		if(~par[i]) gph[par[i]].push_back(i);
	}
	int ans = dfs(0);
	for(int i=0; i<=n; i++) gph[i].clear();
	return ans;
}

int main(){
	scanf("%d %d",&n,&q);
	scanf("%s", str);
	sfxarray::solve(n, str, sfx, rev, lcp);
	for(int i=1; i<n; i++) spt[0][i] = lcp[i];
	for(int i=1; i<19; i++){
		for(int j=1; j<n; j++){
			spt[i][j] = spt[i-1][j];
			if(j + (1<<(i-1)) < n){
				spt[i][j] = min(spt[i][j], spt[i-1][j + (1<<(i-1))]);
			}
		}
	}
	int p = 0;
	for(int i=1; i<n; i++){
		while((2 << p) <= i) p++;
		lg[i] = p;
	}
	while(q--){
		scanf("%d %d",&k,&mod);
		vector<pi> iv(k);
		for(auto &i : iv){
			scanf("%d %d",&i.first, &i.second);
			i.first--;
			i.second--;
		}
		sort(iv.begin(), iv.end(), cmp);
		stack<int> stk;
		fill(par + 1, par + iv.size() + 1, 0);
		fill(cnt + 1, cnt + iv.size() + 1, 0);
		for(int i=0; i<iv.size(); i++){
			while(!stk.empty() && !prefix(iv[stk.top()], iv[i])){
				stk.pop();
			}
			if(stk.size() && same(iv[stk.top()], iv[i])){
				cnt[stk.top() + 1]++;
				par[i + 1] = -1;
				continue;
			}
			par[i + 1] = (stk.empty() ? -1 : stk.top()) + 1;
			cnt[i + 1]++;
			stk.push(i);
		}
		printf("%d\n",solve(iv.size()));
	}
}
