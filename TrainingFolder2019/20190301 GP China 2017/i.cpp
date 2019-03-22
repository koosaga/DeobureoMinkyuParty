#include <bits/stdc++.h>
using namespace std;

const long long hp = 1000000007;
const long long hq = 999999999999999989;

long long mul(long long a, long long b)
{
	return (__int128)a * b % hq;
}

long long ipow(long long x, long long k)
{
	if(k == 0)
		return 1;
	if(k % 2)
		return mul(ipow(x, k-1), x);
	long long t = ipow(x, k / 2);
	return mul(t, t);
}

long long inv(long long x)
{
	return ipow(x, hq - 2);
}

long long ppow[1000010];
long long ippow[1000010];

int par[1000010];
vector<int> chi[1000010];
int cpos[1000010];
vector<long long> sum[1000010];
int siz[1000010];
long long hsh[1000010];

vector<int> lis[1000010];
int lisl[1000010];
int lisr[1000010];

void init(int x)
{
	siz[x] = 1;
	for(int y : chi[x])
	{
		init(y);
		siz[x] += siz[y];
	}
	
	sort(chi[x].begin(), chi[x].end(), [&](int a, int b){
		return hsh[a] < hsh[b];
	});
	
	sum[x].clear();
	hsh[x] = 0;
	int i = 0;
	for(int y : chi[x])
	{
		long long t = mul(ppow[i + 1], mul(1000006969, hsh[y]) + 12347182395789123);
		cpos[y] = i;
		hsh[x] = (hsh[x] + t) % hq;
		sum[x].push_back(hsh[x]);
		i++;
	}
	hsh[x] = (hsh[x] + 19023485672) % hq;
	//printf("hsh %d = %lld\n", x, hsh[x]);
}

int tim;
int dis[1000010];
int fin[1000010];

void init2(int x)
{
	dis[x] = ++tim;
	lis[siz[x]].push_back(x);
	for(int y : chi[x])
		init2(y);
	fin[x] = tim;
}

long long get_sum(int x, int l, int r)
{
	if(r < l)
		return 0;
	if(l == 0)
		return sum[x][r];
	return (sum[x][r] - sum[x][l - 1] + hq) % hq;
}

vector<int> cxpos[1000010];

int main()
{
	ppow[0] = 1;
	for(int i = 1; i < 1000010; i++)
		ppow[i] = mul(ppow[i-1], hp);
	
	ippow[0] = 1;
	ippow[1] = inv(ppow[1]);
	for(int i = 2; i < 1000010; i++)
		ippow[i] = mul(ippow[1], ippow[i - 1]);
	
	while(1)
	{
		int n, i;
		if(scanf("%d", &n) != 1)
			return 0;
		
		tim = 0;
		for(i=1; i<=n; i++)
		{
			chi[i].clear();
			lis[i].clear();
		}
		
		par[1] = -1;
		for(i=2; i<=n; i++)
		{
			scanf("%d", &par[i]);
			chi[par[i]].push_back(i);
		}
		
		init(1);
		init2(1);
		
		for(i=1; i<=n; i++)
		{
			lisl[i] = 0;
			lisr[i] = (int)lis[i].size();
		}
		
		int root = 1;
		int tot = n;
		int res = 1;
		for(int d = tot - 1; d > 1; d--)
		{
			if(tot % d)
				continue;
			
			if(lisl[d] == lisr[d])
				continue;
			
			//printf("d = %d\n", d);
			
			int nxtr = lis[d][lisl[d]];
			long long h = hsh[nxtr];
			
			vector<int> v;
			for(int k = d; k <= n; k += d)
				for(int i = lisl[k]; i < lisr[k]; i++)
					v.push_back(lis[k][i]);
			
			for(int x : v)
				cxpos[x].clear();
			
			//printf("h = %lld\n", h);
			
			for(int x : v)
			{
				int p = par[x];
				if(x != root && siz[p] % d == 0)
					cxpos[p].push_back(cpos[x]);
			}

			bool ok = 1;
			for(int x : v)
			{
				sort(cxpos[x].begin(), cxpos[x].end());
				cxpos[x].push_back((int)chi[x].size());
				
				long long curh = 0;
				int pre = -1;
				int cnt = 0;
				for(int p : cxpos[x])
				{
					curh = (curh + mul(get_sum(x, pre + 1, p - 1), ippow[cnt])) % hq;
					pre = p;
					cnt++;
				}
				curh = (curh + 19023485672) % hq;
				
				if(curh != h)
				{
					ok = 0;
					break;
				}
			}
			if(!ok)
				continue;
			
			res++;
			root = nxtr;
			tot = siz[root];
			
			int l = dis[root];
			int r = fin[root];
			for(i = 1; i <= n; i++)
			{
				while(lisl[i] < lisr[i] && dis[lis[i][lisl[i]]] < l)
					lisl[i]++;
				while(lisl[i] < lisr[i] && dis[lis[i][lisr[i] - 1]] > r)
					lisr[i]--;
			}
		}
		
		printf("%d\n", res);
	}
	return 0;
}













