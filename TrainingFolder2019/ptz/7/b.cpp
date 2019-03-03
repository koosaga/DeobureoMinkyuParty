#include <bits/stdc++.h>

int n;
int a[5][5];
bool chk[100];

void brute(int i) {
	if(i == n * n) {
		int cnt = 0;
		for(int x = 0; x < n; x++) {
			for(int y = 0; y < n; y++) {
				for(int z = 0 ;z < n; z++) {
					if(a[x][a[y][z]] == a[a[x][y]][z]) {
						cnt += 1;
					}
				}
			}
		}
		chk[cnt] = true;
		return;
	}
	int &to  = a[i/n][i%n];
	for(int x = 0; x < n; x++) {
		to = x;
		brute(i+1);
	}
}

int main() {
	for(n = 1; n <= 4; n++) {
		memset(chk, 0, sizeof chk);
		brute(0);
		printf("n = %d: ", n);
		for(int i = 0; i <= n*n*n; i++) {
			if(chk[i]) printf("%3d", i);
		}
		puts("");
		puts("");
	}

	return 0;
}