#include <bits/stdc++.h>

using namespace std;

using ULL = unsigned long long;

int arr[130];
ULL mem[2][1000 * 128 * 10 / 64 + 10];

void solve()
{
	int n, m, i;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &arr[i]);
	scanf("%d", &m);

	priority_queue<int> pq;
	for(i=0; i<n; i++)
		pq.push(-arr[i]);

	vector<pair<int, int>> v;
	while(pq.size() >= 2)
	{
		int x = -pq.top();
		pq.pop();
		int y = -pq.top();
		pq.pop();

		v.push_back({x, y});
		pq.push(-(x + y));
	}

	int mx = 0;
	for(auto &p : v)
		mx += max(p.first, p.second);

	if(m > mx)
	{
		puts("No");
		return;
	}

	mem[0][0] = 1;
	for(i=1; i<=m/64; i++)
		mem[0][i] = 0;

	int c = 1;
	for(auto &p : v)
	{
		for(i=0; i<=m/64; i++)
		{
			mem[c][i] = 0;

			for(int t = p.first;; t = p.second)
			{
				if(t % 64)
				{
					if(i - t / 64 - 1 >= 0)
						mem[c][i] |= mem[1 - c][i - t / 64 - 1] >> (64 - t % 64);
					if(i - t / 64 >= 0)
						mem[c][i] |= mem[1 - c][i - t / 64] << (t % 64);
				}
				else if(i - t / 64 >= 0)
					mem[c][i] |= mem[1 - c][i - t / 64];

				if(t == p.second)
					break;
			}
		}

		c = 1 - c;
	}

	if(mem[1 - c][m / 64] & ((ULL)1 << (m % 64)))
		puts("Yes");
	else
		puts("No");
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
		solve();
	return 0;
}