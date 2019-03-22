#include <bits/stdc++.h>
using namespace std;

double r;
int a, b, c;

double solve3(double x, double y)
{
	return min({
		hypot(a - x, c + y),
		hypot(y, a + c - x),
		hypot(a + y, c + x),
		hypot(a + b - x, b + c - y)
	});
}

double solve2(double x)
{
	double yl = 0;
	double yr = b;
	for(int i=0; i<100; i++)
	{
		double y1 = (yl * 2 + yr) / 3;
		double y2 = (yl + yr * 2) / 3;
		
		double v1 = solve3(x, y1);
		double v2 = solve3(x, y2);
		
		if(v1 < v2)
			yl = y1;
		else
			yr = y2;
	}
	
	return solve3(x, (yl + yr) / 2);
}

double solve()
{
	double xl = 0;
	double xr = a;
	for(int i=0; i<100; i++)
	{
		double x1 = (xl * 2 + xr) / 3;
		double x2 = (xl + xr * 2) / 3;
		
		double v1 = solve2(x1);
		double v2 = solve2(x2);
		
		if(v1 < v2)
			xl = x1;
		else
			xr = x2;
	}
	
	return solve2((xl + xr) / 2);
}

int main()
{
	scanf("%d%d%d", &a, &b, &c);
	
	r = sqrt(a * a + b * b + c * c + 2 * min({a * b, b * c, c * a}));
	
	//printf("%.15lf\n", r);
	
	int s[3];
	s[0] = a;
	s[1] = b;
	s[2] = c;
	
	sort(s, s + 3);
	do
	{
		a = s[0];
		b = s[1];
		c = s[2];
		r = max(r, solve());
	}
	while(next_permutation(s, s + 3));

	printf("%.15lf\n", r);
	return 0;
}
