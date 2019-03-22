#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<int, int>;

int n, a[MAXN], pos[MAXN];
vector<int> p;

lint bino(int x, int y){
	lint ret = 1;
	for(int i=1; i<=y; i++) ret *= x + 1 - i, ret /= i;
	return ret % mod;
}

void case1_1234(){
	int cnt = 0;
	int mx = 0;
	for(int i=1; i<n; i++){
		mx = max(mx, a[i]);
		if(mx == i) cnt++;
	}
	printf("%lld\n", bino(cnt, 3));
}

void case2_crawler(){
	int mxp = max_element(a + 1, a + n + 1) - a;
	for(int i=1; i<=n; i++) pos[a[i]] = i;
	int lst = 0;
	for(int i=1; i<=n; i++){
		if(pos[i] >= mxp){
			lst = i - 1;
			break;
		}
	}
	if(lst == 0){
		puts("0");
		return;
	}
	if(*max_element(a + 1, a + lst + 1) > lst){
		puts("0");
		return;
	}
	reverse(a + lst + 1, a + n + 1);
	if(p[0] == 2) reverse(a + 1, a + lst + 1);
	int mx = 0;
	int cnt1 = 0, cnt2 = 0;
	for(int i=1; i<lst; i++){
		mx = max(mx, a[i]);
		if(mx == i) cnt1++;
	}
	mx = max(mx, a[lst]);
	for(int i=lst+1; i<n; i++){
		mx = max(mx, a[i]);
		if(mx == i) cnt2++;
	}
	printf("%lld\n", 1ll * cnt1 * cnt2 % mod);
}

struct disj{
	int pa[MAXN];
	int chk[MAXN], sz[MAXN];
	int received_min;
	int received_max;
	int compCnt;
	void init(int n){
		iota(pa, pa + n + 3, 0);
		fill(chk, chk + n + 3, 0);
		fill(sz, sz + n + 3, 1);
		received_min = 1e9;
		received_max = 0;
		compCnt = 0;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	int uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p;
		sz[p] += sz[q];
		return 1;
	}
	void mark(int p){
		chk[p] = 1;
		compCnt++;
		if(chk[p-1]) compCnt -= uni(p-1, p);
		if(chk[p+1]) compCnt -= uni(p, p + 1);
		received_min = min(received_min, p);
		received_max = max(received_max, p);
	}
	int getcomp(pi *store){
		if(compCnt == 2){
			store[0] = pi(received_min, received_min + sz[find(received_min)] - 1);
			store[1] = pi(received_max - sz[find(received_max)] + 1, received_max);
		}
		return compCnt;
	}
}disj;

pi intv_left[MAXN][2];
pi intv_right[MAXN][2];
bool okL[MAXN], okR[MAXN];
int pfxMin[MAXN], pfxMax[MAXN];
int sfxMin[MAXN], sfxMax[MAXN];

void case3_general_split(){
	for(int i=0; i<=n+3; i++){
		okL[i] = okR[i] = 0;
	}
	pfxMin[0] = 1e9; pfxMax[0] = 0;
	sfxMin[n+1] = 1e9; sfxMax[n+1] = 0;
	disj.init(n);
	for(int i=1; i<=n; i++){
		disj.mark(a[i]);
		if(disj.getcomp(intv_left[i]) == 2) okL[i] = 1;
		pfxMin[i] = min(pfxMin[i-1], a[i]);
		pfxMax[i] = max(pfxMax[i-1], a[i]);
	}
	disj.init(n);
	for(int i=n; i; i--){
		disj.mark(a[i]);
		if(disj.getcomp(intv_right[i]) == 2) okR[i] = 1;
		sfxMin[i] = min(sfxMin[i+1], a[i]);
		sfxMax[i] = max(sfxMax[i+1], a[i]);
	}
	auto inside = [&](int p, pi v){
		return v.first <= p && p <= v.second;
	};
	auto canon = [&](vector<int> v){
		vector<int> nxt = v;
		sort(v.begin(), v.end());
		for(auto &i : nxt){
			i = lower_bound(v.begin(), v.end(), i) - v.begin() + 1;
		}
		return nxt;
	};
	int ret = 0;
	for(int i=1; i<n; i++){
		if(okL[i] && okR[i + 1]){
			if(!inside(a[1], intv_left[i][0])) swap(intv_left[i][0], intv_left[i][1]);
			if(!inside(a[n], intv_right[i+1][1])) swap(intv_right[i+1][0], intv_right[i+1][1]);
			int length_left = intv_left[i][0].second - intv_left[i][0].first + 1;
			int length_right = intv_right[i+1][1].second - intv_right[i+1][1].first + 1;
			bool ok = true;
			if(pfxMax[length_left] - pfxMin[length_left] != length_left - 1) ok = false;
			if(sfxMax[n + 1 - length_right] - sfxMin[n + 1 - length_right] != length_right - 1) ok = false;
			if(!ok) continue;
			vector<int> v = {intv_left[i][0].first, intv_left[i][1].first, intv_right[i+1][0].first, intv_right[i+1][1].first};
			v = canon(v);
			if(v == p) ret++;
		}
	}
	printf("%d\n", ret);
}

void case4_1432(){
	int mxp = max_element(a + 1, a + n + 1) - a;
	for(int i=1; i<=n; i++) pos[a[i]] = i;
	int lst = 0;
	for(int i=1; i<=n; i++){
		if(pos[i] >= mxp){
			lst = i - 1;
			break;
		}
	}
	if(lst == 0){
		puts("0");
		return;
	}
	if(*max_element(a + 1, a + lst + 1) > lst){
		puts("0");
		return;
	}
	reverse(a + lst + 1, a + n + 1);
	int mx = 0;
	int cnt = 0;
	for(int i=lst + 1; i<n; i++){
		mx = max(mx, a[i]);
		if(mx == i) cnt++;
	}
	printf("%lld\n", bino(cnt, 2));
}

int main(){
	while(~scanf("%d",&n)){
		for(int i=1; i<=n; i++) scanf("%d",&a[i]);
		p.resize(4);
		for(auto &i : p) scanf("%d",&i);
		auto REV = [&](){
			reverse(p.begin(), p.end());
			reverse(a + 1, a + n + 1);
		};
		auto NEG = [&](){
			for(auto &i : p) i = 5 - i;
			for(int i=1; i<=n; i++) a[i] = n + 1 - a[i];
		};
		auto INV = [&](){
			int rev[5] = {};
			for(int i=1; i<=4; i++) rev[p[i-1]] = i;
			vector<int> v(n+1);
			for(int i=1; i<=n; i++) v[a[i]] = i;
			for(int i=1; i<=4; i++) p[i-1] = rev[i];
			for(int i=1; i<=n; i++) a[i] = v[i];
		};
		if(p > vector<int>(p.rbegin(), p.rend())){
			REV();
		}
		auto eq = [&](vector<int> p, vector<int> q){
			return p == q;
		};
		if(eq(p, {3, 2, 1, 4})){
			NEG(); REV();
		}
		if(eq(p, {3, 1, 2, 4})){
			NEG(); REV();
		}
		if(eq(p, {3, 1, 4, 2})){
			NEG(); REV();
		}
		if(eq(p, {2, 1, 3, 4})){
			NEG(); REV();
		}
		if(eq(p, {2, 3, 1, 4})){
			NEG(); REV();
		}
		if(eq(p, {1, 4, 2, 3})){
			INV();
		}
		if(eq(p, {1, 2, 3, 4})){
			case1_1234();
		}
		if(eq(p, {1, 2, 4, 3})){
			case2_crawler();
		}
		if(eq(p, {1, 3, 2, 4})){
			case3_general_split();
		}
		if(eq(p, {1, 3, 4, 2})){
			case3_general_split();
		}
		if(eq(p, {1, 4, 3, 2})){
			case4_1432();
		}
		if(eq(p, {2, 1, 4, 3})){
			case2_crawler();
		}
		if(eq(p, {2, 4, 1, 3})){
			case3_general_split();
		}
	}
}
