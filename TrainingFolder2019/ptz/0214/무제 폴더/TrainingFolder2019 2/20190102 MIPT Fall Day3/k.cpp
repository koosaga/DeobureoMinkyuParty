#include <bits/stdc++.h>

using namespace std;
using lint = long long;
using pii = pair<int ,int>;

namespace suffixarray{
	const int MAXN = 500005;
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];

	void solve(int n, char* str, int *sfx, int *rev, int *lcp) {
		int p = 1;
		for(int i = 0; i < n; i++) {
			sfx[i] = i;
			ord[i] = str[i] - 'a' + 1;
		}

		int pnt = 1;
		while(true) {
			for(int i=0;i<=n||i<30;i++) cnt[i] = 0;
			for(int i=0;i<n;i++) cnt[ord[min(i+p, n)]]++;
			for(int i=1;i<=n || i<30; i++) {
				cnt[i] += cnt[i-1];
			}
			for(int i=n-1; i>=0; i--) {
				aux[--cnt[ord[min(i+p,n)]]] = i;
			}
			for(int i=0;i<=n||i<30;i++) cnt[i] = 0;
			for(int i=0;i<n;i++) cnt[ord[i]]++;
			for(int i=1;i<=n || i<30; i++) {
				cnt[i] += cnt[i-1];
			}
			for(int i=n-1; i>=0; i--) {
				sfx[--cnt[ord[aux[i]]]] = aux[i];
			}
			if(pnt == n) break;
			pnt = 1;
			nord[sfx[0]] = 1;
			for(int i=1;i<n;i++) {
				if(ord[sfx[i-1]] != ord[sfx[i]] || ord[sfx[i-1]+p] != ord[sfx[i]+p]) {
					pnt += 1;
				}
				nord[sfx[i]] = pnt;
			}
			memcpy(ord, nord, sizeof(int) * n);
			p *= 2;
		}

		for(int i =0 ;i < n; i++) {
			rev[sfx[i]] = i;
		}
		int h = 0;
		for(int i = 0; i < n; i++) {
			if(rev[i]) {
				int prv = sfx[rev[i] - 1];
				while(str[prv + h] == str[i + h]) h++;
				lcp[rev[i]] = h;
			}
			h = max(h-1, 0);
		}
		for(int c = 0; c <= n || c < 30; c++) ord[c] = 0;
	}
};


const int N_ = 105500;

int N, M, Q;
char S[N_], T[N_];

char U[N_ * 3];
int lcp[N_ * 3], rev[N_ * 3], sfx[N_ * 3];
vector<int> queries[N_];

lint ans[N_];
int X[N_];
lint Y[N_];

int tree[N_ * 3];

inline void upd_tree(int x, int v) {
	x += 1;
	while(x <= 3*N) {
		tree[x] += v;
		x += x & -x;
	}
}

inline int get_tree(int x) {
	int ret = 0;
	x += 1;
	while(x > 0) {
		ret += tree[x];
		x -= x & -x;
	}
	return ret;
}

int uf[3*N_], ufl[3*N_], ufr[3*N_];
vector<int> lcp_pos[3*N_];
bool activated[3*N_];
int get_uf (int x) {
	return uf[x] == x ? x : (uf[x] = get_uf(uf[x]));
}

inline void merge_uf(int x, int y) {
	x = get_uf(x);
	y = get_uf(y);
	if(x != y) {
		if(x > y) swap(x, y);
		// x < y
		uf[y] = x;
		ufr[x] = ufr[y];
	}
}


void solve() {
	scanf("%d%d%d", &N, &M, &Q);
	scanf("%s%s", S, T);
	for(int q = 0; q < Q; q++) {
		int x; lint y; scanf("%d%lld", &x, &y);
		x -= 1;
		queries[y % M == 0 ? M : y % M].push_back(q);
		X[q] = x; Y[q] = y; ans[q] = 0;
	}

	sprintf(U, "%s|%s%s", S, T, T);

	int UN = N + 1 + M + M;
	memset(tree, 0, sizeof(int) * (UN + 1));
	suffixarray::solve(UN, U, sfx, rev, lcp);

	UN -= 1;

	memset(activated, 0, sizeof(bool) * (UN + 2));
	for(int i = 1; i < UN; i++) {
		lcp_pos[lcp[i]].push_back(i);
		uf[i] = i;
		ufl[i] = ufr[i] = i;
	}

	for(int i = UN; i >= M; i--) {
		for(int x : lcp_pos[i]) {
			activated[x] = true;
			if(x > 0 && activated[x-1]) {
				merge_uf(x, x-1);
			}
			if(x+1 < UN && activated[x+1]) {
				merge_uf(x, x+1);
			}
		}
/*
		printf("lcp = %3d:\n", i);
		for(int x = 0; x < UN; x++) {
			printf("%3d", get_uf(x));
		}
		puts("");
		for(int x = 0; x < UN; x++) {
			printf("%3d", ufl[get_uf(x)]);
		}
		puts("");
		for(int x = 0; x < UN; x++) {
			printf("%3d", ufr[get_uf(x)]);
		}
		puts("");
		*/
	}
/*
	for(int i = 0; i < UN; i++) {
		if(sfx[i] > N+1 && sfx[i] <= N+1+M) {
			printf("!");
		}else {
			printf("@");
		}
		// lcp[i] = lcp(sfx[i], sfx[i-1])

		printf("i=%3d %3d %3d: ", i, sfx[i], lcp[i]);
		printf("%-10s", U + sfx[i]);
		printf("  [%d, %d]", ufl[get_uf(i)], ufr[get_uf(i)]);
		
		puts("");
	}*/


	for(int pref = 1; pref <= M; pref++) {
		int i = N+pref+1;

//		printf("pref = %d\n", pref);
		{
			int l = min(ufl[get_uf(rev[i])], ufl[get_uf(rev[i]+1)]);
			int r = max(ufr[get_uf(rev[i])], ufr[get_uf(rev[i]+1)]);
			//fprintf(stderr, "%d %d\n", l,r);
			if(l <= r) {
			upd_tree(l, +1);
			upd_tree(r+1, -1);}
			//printf("  add [%d, %d] +1\n", l, r);
		}

		for(int q : queries[pref]) {
			//printf("  %d %d %d\n", q, X[q], rev[X[q]]);
			//fprintf(stderr, "%d %d\n" ,rev[X[q]],get_tree(rev[X[q]]));
			ans[q] += get_tree(rev[X[q]]);
		}
	}


	for(int i = 0; i <= UN; i++) {
		lcp_pos[i].clear();
	}
	for(int i = 0; i <= M; i++) {
		queries[i].clear();
	}

	for(int q = 0; q < Q; q++) {
		ans[q] += (lint)get_tree(rev[X[q]]) * ((Y[q] - 1) / M);
		printf("%lld\n", ans[q]);
	}
}

int main() {
	int TC;
	scanf("%d", &TC);
	while(TC--) solve();
	return 0;
}