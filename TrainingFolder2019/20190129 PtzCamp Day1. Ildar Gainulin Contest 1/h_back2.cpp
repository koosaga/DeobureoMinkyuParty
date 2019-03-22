#include <bits/stdc++.h>
using namespace std;

int pcnt(int x){
	int ret = 0;
	while(x){
		x -= x & -x;
		ret++;
	}
	return ret;
}
int adj[5];
vector<int> masks[9][1000];

const int B = 5;

void show_mask(int n, int mask) {
	memset(adj, 0, sizeof(adj));
	for(int i=0;i<n;i++) for(int j=0;j<n;j++) {
		if((mask >> (i+j*n)) & 1) {
			printf("%d-%d ", i, j);
		}
	}
	puts("");
}

int wh[9][1000];

int main(){
	for(int n = 1; n <= B; n++) {
		vector<int> ans(1<<n);
		for(int i=0; i<(1<<(n*n)); i++){
			memset(adj, 0, sizeof(adj));
			for(int j=0; j<n*n; j++){
				if((i >> j) & 1){
					adj[j % n] |= (1 << (j / n));
				}
			}
			int cnt = 0;
			for(int i=0; i<(1<<n); i++){
				int msk = 0;
				for(int j=0; j<n; j++){
					if((i >> j) & 1){
						msk |= adj[j];
					}
				}
				if(pcnt(msk) < pcnt(i)) cnt++;
			}
			ans[cnt] += 1;
			if(ans[cnt] == 1) {
				printf("n = %d, cnt = %d\n  =>", n, cnt);
				show_mask(n, i);
				wh[n][cnt] = i;
			}
		}
		/*
		for(int i = 0; i < (1<<n); i++) {
			printf("%d ", ans[i]);
		}
		puts("");*/
	}


	for(int n = 2; n <= B; n++) {
		for(int k = 1; k < (1<<n); k++) {
			if((wh[n][k] & wh[n-1][k/2]) != wh[n-1][k/2]) {
				printf("n=%d k=%d\n", n,k );
				puts("");
			}
		}
	}



	return 0;
}
