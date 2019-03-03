#include <bits/stdc++.h>

using namespace std;

const int mod = 998244353;

long long ipow(int x, int y)
{
	if(y == 0)
		return 1;
	if(y % 2)
		return 1LL * x * ipow(x, y - 1) % mod;
	int t = ipow(x, y/2);
	return 1LL * t * t % mod;
}

void solve()
{
	int a, b, c, d;
	scanf("%d%d%d%d", &a, &b, &c, &d);

	long long res = ipow(2, a + b) + (b + d + 1) * ipow(2, a + c) - (b + 1) * ipow(2, a);
	res = (res % mod + mod) % mod;
	printf("%lld\n", res);
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
		solve();
	return 0;
}