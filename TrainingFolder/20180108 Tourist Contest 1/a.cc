#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;

const int MAXN = 200005;
int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
void solve(int n, char *str, int *sfx, int *rev, int *lcp){
    int p = 1;
    memset(ord, 0, sizeof(ord));
    for(int i=0; i<n; i++){
        sfx[i] = i;
        ord[i] = str[i];
    }
    int pnt = 1;
    while(1){
        memset(cnt, 0, sizeof(cnt));
        for(int i=0; i<n; i++) cnt[ord[min(i+p, n)]]++;
        for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
        for(int i=n-1; i>=0; i--)
            aux[--cnt[ord[min(i+p, n)]]] = i;
        memset(cnt, 0, sizeof(cnt));
        for(int i=0; i<n; i++) cnt[ord[i]]++;
        for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
        for(int i=n-1; i>=0; i--)
            sfx[--cnt[ord[aux[i]]]] = aux[i];
        if(pnt == n) break;
        pnt = 1;
        nord[sfx[0]] = 1;
        for(int i=1; i<n; i++){
            if(ord[sfx[i-1]] != ord[sfx[i]] || ord[sfx[i-1] + p] != ord[sfx[i] + p]){
                pnt++;
            }
            nord[sfx[i]] = pnt;
        }
        memcpy(ord, nord, sizeof(int) * n);
        p *= 2;
    }
    for(int i=0; i<n; i++) rev[sfx[i]] = i;
    int h = 0;
    for(int i=0; i<n; i++){
        if(rev[i]){
            int prv = sfx[rev[i] - 1];
            while(str[prv + h] == str[i + h]) h++;
            lcp[rev[i]] = h;
        }
        h = max(h-1, 0);
    }
}

struct seg{
	pi tree[530000];
	int lim;
	void init(int n, int *lcp){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 530000, pi(1e9, 1e9));
		for(int i=1; i<n; i++) tree[i + lim] = pi(lcp[i], i);
		for(int i=lim; i; i--) tree[i] = min(tree[2*i], tree[2*i+1]);
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(1e9, 1e9);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg;

int n, mat[MAXN], dp[MAXN];
char str[MAXN];
int sfx[MAXN], rev[MAXN], lcp[MAXN];
int sum[MAXN];
vector<pi> v;

lint ans;
pi pos;

int sfxlen(int s, int l){
	if(dp[s] <= s + l) return dp[s] - s;
	if(l == 0) return 0;
	auto ll = upper_bound(v.begin(), v.end(), pi(sum[s], s+l)) - v.begin() - 1;
	return v[ll].second - s;
}

void solve(int s, int e){
	if(s == e){
		int len = sfxlen(sfx[s], n - sfx[s]);
		if(ans < len){
			ans = len;
			pos = pi(sfx[s], sfx[s] + len);
		}
		return;
	}
	auto qry = seg.query(s+1, e);
	int len = sfxlen(sfx[s], qry.first);
	if(ans < 1ll * len * (e - s + 1)){
		ans = 1ll * len * (e - s + 1);
		pos = pi(sfx[s], sfx[s] + len);
	}
	solve(s, qry.second - 1);
	solve(qry.second, e);
}

int main(){
	freopen("abyss.in", "r", stdin);
	freopen("abyss.out", "w", stdout);
	stack<int> stk;
	scanf("%s", str);
	n = strlen(str);
	memset(mat, -1, sizeof(mat));
	for(int i=0; i<n; i++){
		if(str[i] == '1'){
			if(!stk.empty()){
				mat[stk.top()] = i;
				stk.pop();
			}
		}
		else stk.push(i);
	}
	dp[n] = n;
	for(int i=n-1; i>=0; i--){
		if(mat[i] == -1) dp[i] = i;
		else dp[i] = dp[mat[i] + 1];
	}
	for(int i=1; i<=n; i++) sum[i] = sum[i-1] + (str[i-1] == '0' ? 1 : -1);
	for(int i=0; i<=n; i++) v.push_back(pi(sum[i], i));
	sort(v.begin(), v.end());
	solve(n, str, sfx, rev, lcp);
	seg.init(n, lcp);
	solve(0, n-1);
	cout << ans << endl;
	for(int i=pos.first; i<pos.second; i++) putchar(str[i]);
}
