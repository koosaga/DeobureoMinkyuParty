#include <bits/stdc++.h>

using llf = long double;

using namespace std;

llf log_comb(int n, int r) {
	llf bunja = 0, bunmo = 0;
	for(int i = 1; i <= r; i++) {
		bunja += log(n - i + 1);
		bunmo += log(i);
	}
	return bunja - bunmo;
}

map<int, char> asked;

char ask (int x) {
	if(asked.find(x) != asked.end()) {
		return asked[x];
	}

	printf("%d\n", x);
	fflush(stdout);
	static char tmp[2];
	scanf("%s", tmp);
	asked[x] = tmp[0];
	return tmp[0]; 
}

int n, k;
int a[105];

int main() {
	scanf("%d%d", &n, &k);

	for(int i = 1; i <= n; i++) {

		llf tot = log_comb(k - a[i-1], n - i + 1);
		llf low = 0, high = 1;

		asked.clear();
		for(int rep = 0; ; rep++) {
			llf mid = (low + high) / 2;

			llf cur_ways = tot + log(mid);
			//printf("%Lf %Lf\n", exp(tot), exp(cur_ways));

			int low2 = a[i-1] + 1, high2 = k - (n - i);
			int pos = -1;
			//printf(" > %d %d\n", low2, high2);
			while(low2 <= high2) {
				int mid2 = (low2 + high2) / 2;
				llf val = log_comb(k - mid2 + 1, n - i + 1);
				//printf("  > %d %Lf %Lf\n", mid2, exp(val), exp(cur_ways));
				if(val >= cur_ways || fabs(val - cur_ways) < 1e-10) {
					pos = mid2;
					low2 = mid2 + 1;
				}else {
					high2 = mid2 - 1;
				}
			}
			
			char ret = ask(pos);
			if(ret == '=') {
				a[i] = pos;
				break;
			}else if(ret == '>') {
				high = mid;
			}else {
				low = mid;
			}
		}

	}


	return 0;
}