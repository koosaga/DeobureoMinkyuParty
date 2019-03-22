#include <bits/stdc++.h>

using namespace std;

long long gcd(long long x, long long y)
{
	return x ? gcd(y % x, x) : y;
}

void solve()
{
	long long a, b, c, d, e, f;
	scanf("%lld%lld%lld%lld%lld%lld", &a, &b, &c, &d, &e, &f);

	long long p = a * e + b * f + c * d - a * f - b * d - c * e;
	long long q = a + b + c;

	if(p == 0)
	{
		puts("0");
		return;
	}

	long long g = gcd(p, q);
	p /= g;
	q /= g;
	if(q < 0)
	{
		p = -p;
		q = -q;
	}

	if(q == 1)
		printf("%lld\n", p);
	else
		printf("%lld/%lld\n", p, q);
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
		solve();
	return 0;
}