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

void show_mask(int n, int i) {
	memset(adj, 0, sizeof(adj));
	for(int j=0; j<n*n; j++){
		if((i >> j) & 1){
			printf("%d-%d ", j/n, j%n); //adj[j / n] |= (1 << (j % n));
		}
	}
	puts("");
}

int main(){
	for(int n = 1; n <= B; n++) {
		printf("n = %d\n", n);
		for(int i=0; i<(1<<(n*n)); i++){
			memset(adj, 0, sizeof(adj));
			for(int j=0; j<n*n; j++){
				if((i >> j) & 1){
					adj[j / n] |= (1 << (j % n));
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
			masks[n][cnt].push_back(i);
		}
	}

	for(int n = 2; n <= B; n++) {
		vector<int> cur_mask(1<<n, -1);
		for(int k = (1<<n); --k >= 2; ) {
			bool good = false;
			for(int mask : masks[n][k]) {
				if(cur_mask[k] < 0 || cur_mask[k] == mask) {
					int to = k/2;
					for(int submask : masks[n][to]) {
						if(cur_mask[to] < 0 || cur_mask[to] == submask) {
							if((submask & mask) == mask) {
								cur_mask[to] = submask;
								printf("%d -> %d, %d -> %d\n", to, k, submask, mask);
								good = true;
							}
						}
					}
					if(good) {
						break;
					}
				}
			}
			assert(good);
		}
	}

	return 0;
}
