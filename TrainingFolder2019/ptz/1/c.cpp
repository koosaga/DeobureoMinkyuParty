#include <bits/stdc++.h>

using namespace std;

int pa[300010];
int pb[300010];

int ra[300010];
int rb[300010];

int main()
{
	int n, i;
	long long k;
	scanf("%d%lld", &n, &k);
	for(i=1; i<=n; i++)
		scanf("%d", &pa[i]);
	for(i=1; i<=n; i++)
		scanf("%d", &pb[i]);

	for(i=1; i<=n; i++)
		rb[pb[i]] = -(n-i+1);

	long long c = 0;
	for(i=1; i<=n; i++)
	{
		int x = pa[i];

		if(c == k)
		{
			ra[x] = n;
			continue;
		}

		if(n-x + c <= k)
		{
			ra[x] = 0;
			c += n-x;
			continue;
		}

		vector<int> v;
		for(int j=x+1; j<=n; j++)
			v.push_back(rb[j]);

		sort(v.begin(), v.end());

		ra[x] = -v[k - c - 1] - 1;
		c = k;
	}

	assert(c == k);
	for(i=1; i<n; i++)
	{
		assert(ra[pa[i]] <= ra[pa[i+1]]);
		assert(rb[pb[i]] <= rb[pb[i+1]]);
	}

	puts("Yes");
	for(i=1; i<=n; i++)
		printf("%d ", ra[i]);
	puts("");
	for(i=1; i<=n; i++)
		printf("%d ", rb[i]);
	puts("");
	return 0;
}