#include <bits/stdc++.h>
using namespace std;

int gcd(int x, int y)
{
	return x ? gcd(y % x, x) : y;
}

struct pos
{
	int x, y;
	long long c;
	bool operator <(const pos &a) const
	{
		return x != a.x ? x < a.x : y < a.y;
	}
};

void solve()
{
	int ex, ey;
	scanf("%d%d", &ex, &ey);
	
	priority_queue<pos> pq;
	pq.push({ex, ey, 1});
	
	long long r = 0;
	while(!pq.empty())
	{
		pos p = pq.top();
		pq.pop();
		
		while(!pq.empty() && pq.top().x == p.x && pq.top().y == p.y)
		{
			p.c += pq.top().c;
			pq.pop();
		}
		
		r += p.c;
		
		int g = gcd(p.x, p.y);
		int x2 = p.x / g;
		int y2 = p.y / g;
		if(x2 % (y2 + 1) == 0)
			pq.push({p.x / (y2 + 1), p.y, p.c});
		if(y2 % (x2 + 1) == 0)
			pq.push({p.x, p.y / (x2 + 1), p.c});
	}
	
	printf("%lld\n", r);
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=1; i<=t; i++)
	{
		printf("Case #%d: ", i);
		solve();
	}
	return 0;
}
