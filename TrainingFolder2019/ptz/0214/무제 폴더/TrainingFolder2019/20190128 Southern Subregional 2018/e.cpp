#include <bits/stdc++.h>

using namespace std;

int a[110];
int d[110];

struct str
{
	int p, i, t;
	bool operator <(const str &a) const
	{
		return p != a.p ? p < a.p : (i != a.i ? i > a.i : t < a.t);
	}
};

int bef[110];

int sco[110];

int main()
{
	int n, i, j;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d%d", &a[i], &d[i]);

	vector<str> v;
	for(i=0; i<n; i++)
	{
		v.push_back({ a[i], i, 1 });
		v.push_back({ a[i]+d[i], i, 2});
	}
	sort(v.begin(), v.end());

	vector<pair<int, int>> inc;
	vector<pair<int, int>> dec;

	memset(bef, -1, sizeof bef);
	for(i=0; i<2*n; i++)
	{
		if(bef[v[i].i] == -1)
			bef[v[i].i] = i;
		else
		{
			if(v[i].t == 2)
				inc.push_back({bef[v[i].i], v[i].i});
			else
				dec.push_back({i, v[i].i});
		}
	}

	sort(inc.begin(), inc.end());
	sort(dec.rbegin(), dec.rend());

	vector<int> ord;
	for(auto p : inc)
		ord.push_back(p.second);
	for(auto p : dec)
		ord.push_back(p.second);

	assert((int)ord.size() == n);

	for(i=0; i<n; i++)
		sco[i] = a[i];

	int res = 0;
	for(i=0; i<n; i++)
	{
		int x = ord[i];

		int r1 = 1;
		for(j=0; j<n; j++)
			if(sco[j] > sco[x] || sco[j] == sco[x] && j < x)
				r1++;

		sco[x] += d[x];

		int r2 = 1;
		for(j=0; j<n; j++)
			if(sco[j] > sco[x] || sco[j] == sco[x] && j < x)
				r2++;

		res += abs(r1 - r2);
	}

	printf("%d\n", res);
	return 0;
}






