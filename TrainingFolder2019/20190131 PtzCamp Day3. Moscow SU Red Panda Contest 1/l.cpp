#include<bits/stdc++.h>

using namespace std;

const int t_ = 5050;

struct query {
	int x, k, p, i, a;
};

int ans[t_];
query queries[t_];

int wh[405][405];
int vis[405][405];

int f[50050];

inline int _f(int x) {
	return x * x; // x & 1 ? ((x+1) >> 1) * x : (x >> 1) * (x+1);
}

int main() {
	srand(time(NULL));

	for(int i = 0; i <= 50000; i++) {
		f[i] = _f(i);
	}

	int t;
	scanf("%d", &t);
	for(int i = 0; i < t; i++) {
		query &q = queries[i];
		scanf("%d%d%d", &q.x, &q.k, &q.p);
		q.i = i;
		q.a = -1;
	}

	memset(vis, -1, sizeof vis);


	sort(queries, queries+t, [&](const query &q1, const query &q2) {
		return q1.p < q2.p;
	});

	for(int i = 0; i < t; i++) {
		query &q = queries[i];
		if(q.p == (q.p & -q.p)) {
			q.a = -1;
			continue;
		}

		if(q.k < 3) {
			__int128 x = q.x;
			for(int k = q.k; k > 0; k--) x = _f(x) + k;
			q.a = (x + 1) % q.p;
		}else {
			q.a = 0;
		}
	}

	sort(queries, queries+t, [&](const query &q1, const query &q2) {
		return q1.i < q2.i;
	});
	for(int i = 0; i < t; i++) {
		query &q = queries[i];
		printf("%d\n", q.a);
	}




	return 0;
}