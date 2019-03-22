#include <bits/stdc++.h>

using namespace std;

int n;

char buf[100];
int bp = 997;
long long hp = 99999999999973LL;

unordered_map<long long, long long> qc;

int qcnt = 0;
long long query(vector<int> &v, int pp)
{
	//assert(v.size() > 2);

	long long h = 0;
	for(int x : v)
	{
		if(x == pp)
			continue;
		h = (h * bp + x) % hp;
	}

	auto it = qc.find(h);
	if(it != qc.end())
		return it->second;

	qcnt++;
	assert(qcnt <= n * (n-1) / 2);

	printf("? %d\n", (int)v.size() - (pp == -1 ? 0 : 1));
	for(int t : v)
	{
		if(t == pp)
			continue;
		printf("%d ", t);
	}
	puts("");
	fflush(stdout);

	scanf("%s", buf);
	long long r1 = 0, r2 = 0;
	bool u = 0;
	for(int i=0; buf[i]; i++)
	{
		if(buf[i] == '.')
			u = 1;
		else if(u)
		{
			r2 = r2 * 10 + (buf[i] - '0');
			break;
		}
		else
			r1 = r1 * 10 + (buf[i] - '0');
	}
	long long r = 2 * r1 + r2 / 5;
	qc[h] = r;
	return r;
}

long long f(vector<int> &v, int pp, int qq)
{
	int sz = (int)v.size();
	if(sz <= 2)
		return 0;

	vector<int> sorted_v = v;
	sort(sorted_v.begin(), sorted_v.end());

	long long tot = query(sorted_v, -1);
	if(tot == 0)
		return 0;
	
	if(sz == 3)
		return tot;

	vector<bool> chk(sz);
	int s = -1;
	for(int i=0; i<sz; i++)
	{
		if(v[i] == pp || v[i] == qq)
		{
			chk[i] = 1;
			s = i;
			continue;
		}

		long long t = query(sorted_v, v[i]);
		//assert(t <= tot);
		if(t < tot)
		{
			chk[i] = 1;
			s = i;
		}
	}
	//assert(s != -1);

	long long res = tot;
	vector<int> nv;
	nv.push_back(v[s]);
	for(int i=s+1; i<=s+sz; i++)
	{
		int idx = i % sz;
		int x = v[idx];
		nv.push_back(x);
		if(chk[idx])
		{
			if(nv.size() >= 3)
				res -= f(nv, x, nv[0]);
			nv.clear();
			nv.push_back(x);
		}
	}
	return res;
}

int main()
{
	scanf("%d", &n);
	vector<int> v;
	for(int i=1; i<=n; i++)
		v.push_back(i);
	long long res = f(v, -1, -1);

	if(res % 2 == 0)
		printf("! %lld\n", res / 2);
	else
		printf("! %lld.5\n", res / 2);
	fflush(stdout);
	return 0;
}