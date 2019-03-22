#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<int, int>;

lint ipow(int x, int p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x < MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

int n;
vector<int> v;
pi a[MAXN];
lint fact[MAXN], invf[MAXN];

lint bino(int x, int y){
	return fact[x] * (invf[y] * invf[x - y] % mod) % mod;
}

int main(){
	scanf("%d",&n);
	fact[0] = invf[0] = 1;
	for(int i=1; i<MAXN; i++){
		fact[i] = fact[i-1] * i % mod;
		invf[i] = ipow(fact[i], mod - 2);
	}
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
		if(a[i].first > a[i].second){
			swap(a[i].first, a[i].second);
		}
		v.push_back(a[i].first);
		v.push_back(a[i].second);
	}
	v.push_back(-1);
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for(int i=0; i<n; i++){
		a[i].first = lower_bound(v.begin(), v.end(), a[i].first) - v.begin();
		a[i].second = lower_bound(v.begin(), v.end(), a[i].second) - v.begin();
	}
	sort(a, a + n, [&](const pi &a, const pi &b){
		return a.second > b.second;
	});
	multiset<int> s;
	lint dap = 1;
	for(int i=0; i<n;){
		int e = i;
		while(e < n && a[i].second == a[e].second) e++;
		int cnt = bit.query(MAXN - 1) - bit.query(a[i].second);
		if(cnt >= e - i){
			for(int j=i; j<e; j++){
				auto itr = s.lower_bound(a[j].second + 1);
				bit.add(*itr, -1);
				bit.add(a[j].first, 1);
				s.insert(a[j].first);
				s.erase(itr);
			}
			for(int j=i; j<e; j++){
				dap *= cnt;
				dap %= mod;
				cnt--;
			}
		}
		else{
			dap *= bino(e - i, cnt);
			dap %= mod;
			dap *= fact[cnt];
			dap %= mod;
			while(s.size() && *s.rbegin() > a[i].second){
				bit.add(*s.rbegin(), -1);
				s.erase(--s.end());
			}
			for(int j=i; j<e; j++){
				bit.add(a[j].first, 1);
				s.insert(a[j].first);
			}
		}
		i = e;
	}
	cout << dap << endl;
}
