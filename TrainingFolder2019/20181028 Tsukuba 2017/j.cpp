#include <bits/stdc++.h>

using namespace std;

using llf = long double;
using lint = long long;
using pli = pair<lint, int>;
using pii = pair<int, int>;
const llf PI = acos(-1);

int N,A,B,Q;
int X[1050]; char C[1050];
int Y[1050], H[1050];

struct query {
	int x, c;
	bool operator< (const query &q) const {
		return x < q.x;
	}
};

priority_queue<query> pq;
char ans[2050];
map<int, int> pos;

int main() {
	scanf("%d%d%d%d", &N, &A, &B, &Q);
	for(int i = 1; i <= A; i++) {
		int x; char c[2]; scanf("%d%s", &x, c);
		pq.push({x, -*c});
	}
	for(int j = 1; j <= B; j++) {
		int y, h; scanf("%d%d", &y, &h);
		Y[j] = y;
		H[j] = h;
	}
	Y[B+1] = N+1;
	Y[0] = 0;
	for(int i = 1; i <= Q; i++) {
		int x; scanf("%d", &x);
		pq.push({x, i});
	}


	for(int j = B; j >= 0; j--) {
		vector<query> found;
		while(!pq.empty() && pq.top().x >= Y[j]) {
			query q = pq.top(); pq.pop();
			if(H[j] == 0) {
				if(q.c < 0) {
					pos[q.x] = -q.c;
				}else {
					found.push_back(q);
				}
			}else if(H[j] + (Y[j+1] - Y[j]) <= Y[j]) {
				pq.push({q.x - Y[j] + H[j], q.c});
			}else {
				pq.push({H[j] + (q.x - H[j]) % (Y[j] - H[j]), q.c});
			}
		}

		for(query q : found) {
			ans[q.c] = pos.find(q.x) == pos.end() ? '?' : pos[q.x];
		}
	}

	puts(ans+1);
	return 0;
}