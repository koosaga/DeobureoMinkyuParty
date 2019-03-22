#include <bits/stdc++.h>
using namespace std;

int pcnt[1<<20];

int check(vector<int> &ans) {
	int cnt = 0;
	int n = ans.size();
	for(int i=0; i<(1<<n); i++){
		int msk = 0;
		for(int j=0; j<n; j++){
			if((i >> j) & 1){
				msk |= ans[j];
			}
		}
		if(pcnt[msk] < pcnt[i]) cnt++;
	}
	return cnt;
}

vector<int> tb[21][1<<20];

vector<int> go(int n, int k) {
	if(!tb[n][k].empty()) {
		return tb[n][k];
	}

	vector<int> ret(n);
	if(k == 0) {
		for(int i = 0; i < n; i++) ret[i] = (1<<i);
	}else if(k == 1) {
		for(int i = 0; i < n; i++) ret[i] = ((1<<(n-1)) - 1);
	}else if(k % 2 == 0) {
		vector<int> ch = go(n-1, k/2);
		for(int i = 0; i < n-1; i++) ret[i] = ch[i];
		ret[n-1] = 1<<(n-1);
	}else if(k >= (1<<n) - n) {
		for(int i = 0; i < (1<<n) - k - 1; i++) ret[i] = 1;
	}else if(k == (1<<(n-1)) - 1) {
		ret[0] = (1<<n) - 1;
	}else if(k < (1<<(n-1))) {
		ret = go(n-1, k);
		ret.push_back((1<<n)-1);
	}else {
		for(int r = 0; r < k; r++) {
			ret = go(n-1, r);
			ret.push_back(0);
			for(int j = 0; j < (1<<n); j++) {
				ret.back() = j;
				if(check(ret) == k) {
					return ret;
				}
			}
		}
	}
	return ret;
}

int main(){
	for(int i = 1; i < (1<<20); i++) {
		pcnt[i] = pcnt[i/2] + (i % 2);
	}
	for(int n = 1; n <= 10; n++) {
		printf("n = %d\n", n);
		for(int k = 0; k < (1<<n); k++) {
			vector<int> ans = go(n, k);
			int cnt = check(ans);
			if(cnt != k) {
				printf("n=%d, k=%d, cnt=%d\n", n, k, cnt);

				for(int i = 0; i < n; i++) {
					for(int j = 0; j < n; j++) {
						if((ans[i] >> j) & 1) printf("%d %d\n", i+1, j+1);
					}
				}
				return 0;
			}
		}
	}
	puts("all correct");
	return 0;

	int n, k;

	scanf("%d%d", &n, &k);

	vector<int> ans = go(n, k);

	int m = 0;
	for(int i = 0; i < n; i++) {
		m += pcnt[ans[i]];
	}

	int cnt = check(ans);

	printf("%d\n", m);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if((ans[i] >> j) & 1) printf("%d %d\n", i+1, j+1);
		}
	}

	if(cnt != k) {
		printf("k=%d, cnt=%d\n", k, cnt);
	}
	assert(cnt == k);
	return 0;
}
