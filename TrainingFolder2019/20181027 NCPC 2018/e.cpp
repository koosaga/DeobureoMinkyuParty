#include <bits/stdc++.h>

using namespace std;

using llf = long double;
using lint = long long;
using pli = pair<lint, int>;
using pii = pair<int, int>;

int n, m, d;

map<vector<int>, int> mapping; int TIME;
vector<int> freq[500];
int num_alive[500];
int sum_alive[500];

void gen(int x, int n, int s = 0) {
	static vector<int> cur(6);

	if(mapping.find(cur) == mapping.end()) {
		mapping[cur] = ++TIME;
		freq[TIME] = cur;
		num_alive[TIME] = n;
		sum_alive[TIME] = s;
	}

	if(n == 5) return;
	if(x == 6) return;

	gen(x+1, n, s);

	cur[x] += 1;
	gen(x, n+1, s+x+1);
	cur[x] -= 1;
}

llf prob[500][500];
bool used[500][500];
int init_sum_alive;

llf go(int m, int o) {
	llf &ret = prob[m][o];
	if(!used[m][o]) {
		used[m][o] = true;

		if(init_sum_alive - (sum_alive[m] + sum_alive[o]) > d) {
			ret = 0;
		}else if(num_alive[o] == 0) {
			ret = 1;
		}else {
			vector<int> mc = freq[m];
			vector<int> oc = freq[o];

			llf sum = 0;
			for(int i = 0; i < 6; i++) {
				if(mc[i] > 0) {
					mc[i] -= 1;
					if(i > 0) mc[i-1] += 1;

					llf ch = go(mapping[mc], o);

					mc[i] += 1;
					if(i > 0) mc[i-1] -= 1;

					sum += ch * mc[i];
				}
			}

			for(int i = 0; i < 6; i++) {
				if(oc[i] > 0) {
					oc[i] -= 1;
					if(i > 0) oc[i-1] += 1;

					llf ch = go(m, mapping[oc]);

					oc[i] += 1;
					if(i > 0) oc[i-1] -= 1;

					sum += ch * oc[i];
				}
			}

			ret = sum / (num_alive[m] + num_alive[o]);
			//printf(" [%d %d] %Lf\n", m, o, sum);
		}

	}
	return ret;
}

int main() {
	gen(0, 0);

	scanf("%d%d%d", &n, &m, &d);

	int st;
	{
		vector<int> cnt(6);
		for(int i = 0; i < n; i++) {
			int x; scanf("%d" ,&x);
			cnt[x-1] += 1;
		}
		assert(mapping.find(cnt) != mapping.end());
		st = mapping[cnt];
	}

	int en;
	{
		vector<int> cnt(6	);
		for(int i = 0; i < m; i++) {
			int x; scanf("%d" ,&x);
			cnt[x-1] += 1;
		}
		assert(mapping.find(cnt) != mapping.end());
		en = mapping[cnt];
	}

	init_sum_alive = sum_alive[st] + sum_alive[en];
	printf("%.20Lf\n", go(st, en));
	return 0;
}

/*
0,0,0,0,0,0,(0,0) / 1,0,0,0,0,0,(1,1) / 3 / 
0.000000
0,0,0,0,0,0,(0,0) / 2,0,0,0,0,0,(2,2) / 2 / 
0.000000
0,0,0,0,0,0,(0,0) / 1,0,0,0,0,0,(1,1) / 3 / 
0.000000
1,0,0,0,0,0,(1,1) / 0,0,0,0,0,0,(0,0) / 3 / 
0.000000
1,0,0,0,0,0,(1,1) / 1,0,0,0,0,0,(1,1) / 2 / 
0.000000
1,0,0,0,0,0,(1,1) / 2,0,0,0,0,0,(2,2) / 1 / 
0.000000
1,0,0,0,0,0,(1,1) / 1,0,0,0,0,0,(1,1) / 2 / 
0.000000
0,1,0,0,0,0,(1,2) / 0,0,0,0,0,0,(0,0) / 2 / 
1.000000
0,1,0,0,0,0,(1,2) / 1,0,0,0,0,0,(1,1) / 1 / 
0.500000
0,1,0,0,0,0,(1,2) / 2,0,0,0,0,0,(2,2) / 0 / 
0.083333
0.08333333333333333334
*/