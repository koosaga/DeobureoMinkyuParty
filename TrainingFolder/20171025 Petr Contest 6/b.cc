#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

int n, l;
int p[MAXN], c[MAXN], d[MAXN];
int nc[MAXN], nxt[MAXN];
lint t;

struct ant{
	int pos, col, del;
}val[MAXN];

vector<ant> proc;
vector<int> idx;

int main(){
	freopen("chameleons.in", "r", stdin);
	freopen("chameleons.out", "w", stdout);
	cin >> n >> l;
	for(int i=0; i<n; i++) idx.push_back(i);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&p[i],&c[i],&d[i]);
	}
	sort(idx.begin(), idx.end(),[&](const int &a, const int &b){
		return p[a] < p[b];
	});
	cin >> t;
	lint sum = 0;
	for(int i=0; i<n; i++){
		if(d[i] == -1){
			lint tmp = (t + l - p[i] - 1) / l;
			sum += n - tmp % n;
		}
		else{
			lint tmp = (t + p[i]) / l;
			sum += tmp % n;
		}
		lint k = p[i] + d[i] * t;
		k = (k % l + l) % l;
		nxt[i] = k;
	}
	sum %= n;
	sum = (n - sum) % n;
	rotate(idx.begin(), idx.begin() + sum, idx.end());
//	cout << sum << endl;
	vector<pi> v, w;
	for(int i=0; i<n; i++){
		nc[i] = c[i];
		if(d[i] == -1){
			v.push_back(pi((int)nxt[i], i));
		}
		else{
			w.push_back(pi((int)nxt[i], i));
		}
	}
	sort(v.begin(), v.end());
	sort(w.begin(), w.end());
	for(int i=0; i<v.size(); i++){
		auto np = lower_bound(w.begin(), w.end(), pi(v[i].first, -1));
		if(np == w.end()){
			if(w.empty()) continue;
			np = w.begin();
		}
		lint delta = np->first - v[i].first + l;
		delta %= l;
		if(delta <= 2 * t){
			nc[v[i].second] = nc[np->second];
		}	
	}
	for(int i=0; i<n; i++){
		proc.push_back({nxt[i], nc[i], d[i]});
	}
	sort(proc.begin(), proc.end(), [&](const ant &a, const ant &b){
		return a.pos < b.pos;
	});
	for(int i=0; i<proc.size(); i++){
		val[idx[i]] = proc[i];
	}
	for(int i=0; i<n; i++){
		printf("%d.0 %d %d\n", val[i].pos, val[i].col, val[i].del);
	}
}
