#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

#define dec fuck

int n, a[MAXN];
int dec[MAXN], inc[MAXN];
int dpd[MAXN], dpi[MAXN];
int trd[MAXN], tri[MAXN];

vector<int> incr, decr;

void solvei(int s, int e);
void solved(int s, int e);

void print(){
	puts("YES");
	swap(incr, decr);
	printf("%d ", incr.size());
	for(auto &i : incr) printf("%d ", i);
	puts("");
	printf("%d ", decr.size());
	for(auto &i : decr) printf("%d ", i);
	puts("");
	incr.clear();
	decr.clear();
}

void solvei(int s, int e){
	if(s != 1){
		solved(trd[s-1] + 1, s-1);
	}
	for(int i=s; i<=e; i++) incr.push_back(a[i]);
}

void solved(int s, int e){
	if(s != 1){
		solvei(tri[s-1] + 1, s-1);
	}
	for(int i=s; i<=e; i++) decr.push_back(a[i]);
}

struct seg{
	int tree[270000];
	int lim;
	void init(int n){
		memset(tree, 0, sizeof(tree));
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void upd(int x, int v){
		x += lim;
		tree[x] = max(tree[x], v);
		while(x > 1){
			x >>= 1;
			tree[x] = max(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 0;
		while(s < e){
			if(s%2 == 1) ret = max(ret, tree[s++]);
			if(e%2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg1, seg2;

void solve(){
	seg1.init(n);
	seg2.init(n);
	memset(dpd, 0, sizeof(dpd));
	memset(dpi, 0, sizeof(dpi));
	for(int i=1; i<n; i++){
		if(dec[i] == 1) dpd[i] = 1, trd[i] = 0;
		if(inc[i] == 1) dpi[i] = 1, tri[i] = 0;
		int pos = seg2.query(a[i + 1] + 1, n);
		if(pos >= dec[i] - 1) dpd[i] = 1, trd[i] = pos;
		pos = seg1.query(1, a[i + 1] - 1);
		if(pos >= inc[i] - 1) dpi[i] = 1, tri[i] = pos;
		if(dpd[i]) seg1.upd(a[i], i);
		if(dpi[i]) seg2.upd(a[i], i);
	}
	for(int i=n-1; i>=dec[n]-1; i--){
		if(dpi[i]){
			solved(i+1, n);
			print();
			return;
		}
	}
	for(int i=n-1; i>=inc[n]-1; i--){
		if(dpd[i]){
			solvei(i+1, n);
			print();
			return;
		}
	}
	puts("NO");
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		scanf("%d",&n);
		for(int i=1; i<=n; i++){
			scanf("%d",&a[i]);
			dec[i] = inc[i] = i;
			if(i > 1 && a[i-1] > a[i]) inc[i] = inc[i-1];
			if(i > 1 && a[i-1] < a[i]) dec[i] = dec[i-1];
		}
		if(dec[n] == 1){
			printf("YES\n%d ", n);
			for(int i=1; i<=n; i++) printf("%d ", i);
			puts("\n0");		
		}
		else if(inc[n] == 1){
			printf("YES\n0\n%d ", n);
			for(int i=1; i<=n; i++) printf("%d ",n+1-i);
			puts("");
		}
		else solve();
	}
}
