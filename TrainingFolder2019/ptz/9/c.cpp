#include <bits/stdc++.h>

using namespace std;

struct edg
{
	int x, w;
};

vector<edg> chi[1000010];
//edg par[1000010];

int grd[1000010];
int opt[1000010];

void f(int x)
{
	grd[x] = 0;
	for(edg e : chi[x])
	{
		f(e.x);
		grd[x] ^= grd[e.x] + (e.w % 2);
	}
}

vector<int> res;
void g(int x)
{
	for(edg e : chi[x])
	{
		int t = grd[e.x] + (e.w % 2);
		int t2 = grd[x] ^ t ^ opt[x];

		if(e.w > 1)
		{
			if(t2 == grd[e.x] + ((e.w - 1) % 2))
				res.push_back(e.x);
		}
		else
		{
			if(t2 == 0)
				res.push_back(e.x);
		}

		int t3 = t2 - (e.w % 2);
		if(t3 < 0)
			continue;

		opt[e.x] = t3;
		g(e.x);
	}
}

void solve()
{
	int n, i;
	scanf("%d", &n);
	for(i=1; i<=n; i++)
		chi[i].clear();

	for(i=2; i<=n; i++)
	{
		int p, w;
		scanf("%d%d", &p, &w);
		chi[p].push_back({i, w});
		//par[i] = {p, w};
	}

	res.clear();
	f(1);
	g(1);

	sort(res.begin(), res.end());
	printf("%d\n", (int)res.size());
	for(int x : res)
		printf("%d ", x);
	puts("");
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
		solve();
	return 0;
}