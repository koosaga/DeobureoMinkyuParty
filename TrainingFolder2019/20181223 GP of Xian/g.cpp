#include <bits/stdc++.h>

using namespace std;

char arr[1000010];
int x[1000010];
int y[1000010];

void solve()
{
	int n, m, k, i;
	scanf("%d%d%d%s", &n, &m, &k, arr);

	int cnt = 0;
	for(i=0; i<n; i++)
		if(arr[i] == 'B')
			cnt++;

	if(cnt < 2 * m || n % k != 0 || 1LL * k * m > n)
	{
		puts("No");
		return;
	}

	if(m == 1)
	{
		for(i=0; i<n; i++)
		{
			if(arr[i] == 'B' && arr[(i + 1) % n] == 'B')
			{
				puts("Yes");
				printf("%d ", n);
				for(i=0; i<n; i++)
					printf("%d ", i);
				puts("");
				return;
			}
		}

		puts("No");
		return;
	}

	puts("Yes");

	set<int> s;
	cnt = 0;
	for(i=0; i<n; i++)
	{
		if(cnt == 2 * m || arr[i] == 'C')
			s.insert(i);
		else
		{
			if(cnt % 2 == 0)
				x[cnt / 2] = i;
			else
				y[cnt / 2] = i;
			cnt++;
		}
	}

	// k = 1 exception??

	for(i=0; i<m-2; i++)
	{
		assert((int)s.size() >= k - 2);

		vector<int> res;

		auto it = s.upper_bound(x[i]);
		while(res.size() + 2 < k)
		{
			if(it == s.end())
				it = s.begin();

			if(x[i] < *it && *it < y[i])
			{
				res.push_back(*it);
				it++;
			}
			else
				break;
		}

		if(res.size() + 2 < k)
		{
			res.clear();
			auto it = s.upper_bound(y[i]);
			while(res.size() + 2 < k)
			{
				if(it == s.end())
					it = s.begin();

				if(!(x[i] < *it && *it < y[i]))
				{
					res.push_back(*it);
					it++;
				}
				else
					break;
			}
		}

		res.push_back(x[i]);
		res.push_back(y[i]);

		assert(res.size() % k == 0);

		sort(res.begin(), res.end());

		printf("%d ", (int)res.size());
		for(int t : res)
		{
			printf("%d ", t);
			if(t != x[i] && t != y[i])
				s.erase(t);
		}
		puts("");
	}

	//x[m - 2], y[m - 2], x[m - 1], y[m - 1]


	vector<int> r1, r2;
	vector<int> a, b, c, d;

	for(int t : s)
	{
		if(x[m-2] < t && t < y[m-2])
			a.push_back(t);
		else if(y[m-2] < t && t < x[m-1])
			b.push_back(t);
		else if(x[m-1] < t && t < y[m-1])
			c.push_back(t);
		else
			d.push_back(t);
	}

	int p1 = x[m-2];
	int p2 = y[m-2];
	int p3 = x[m-1];
	int p4 = y[m-1];

	for(int bb=0;; bb++)
	{
		r1.clear();
		r2.clear();

		for(int t : c)
			r1.push_back(t);
		for(int t : a)
			r2.push_back(t);

		r1.push_back(p1);
		r1.push_back(p2);
		r2.push_back(p3);
		r2.push_back(p4);

		int tmp = 0;
		bool ok = 1;
		while(r1.size() % k != 0)
		{
			if(tmp < b.size())
				r1.push_back(b[tmp]);
			else if(tmp < b.size() + d.size())
				r1.push_back(d[tmp - b.size()]);
			else
			{
				ok = 0;
				break;
			}
			tmp++;
		}

		if(ok)
		{
			while(tmp < b.size() + d.size())
			{
				if(tmp < b.size())
					r2.push_back(b[tmp]);
				else
					r2.push_back(d[tmp - b.size()]);
				tmp++;
			}

			if(r2.size() % k == 0)
			{
				sort(r1.begin(), r1.end());
				sort(r2.begin(), r2.end());

				printf("%d ", (int)r1.size());
				for(int t : r1)
					printf("%d ", t);
				puts("");

				printf("%d ", (int)r2.size());
				for(int t : r2)
					printf("%d ", t);
				puts("");
				return;
			}
		}

		//assert(bb == 0);
		swap(a, b);
		swap(c, d);
		int tt = p1;
		p1 = p2;
		p2 = p3;
		p3 = p4;
		p4 = tt;
	}
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
		solve();
	return 0;
}





