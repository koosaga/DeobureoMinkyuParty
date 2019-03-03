#include <bits/stdc++.h>
using namespace std;
using lint = long long;

const lint MOD = lint(1e9) + 7;
int main() {
	lint N = 100000000000ll;
	lint a = 1;
	lint m = 2;
	for(lint n = 2; n <= N; n++) {
		m = (m * m) % MOD;
		a = (m * a % MOD - a * a % MOD + MOD) % MOD;
		assert(a < MOD && a >= 0);
		if(a == 0) {
			printf("FUCK!!!!!! n = %lld\n" ,n);
			return 0;
		}
	}
	puts("noo..");
	return 0;
}
