#include <bits/stdc++.h>
using namespace std;

int a[100010];
int b[100010];

vector<int> v[100010];

int main()
{
	int n, k, i;
	scanf("%d%d", &n, &k);
	for(i=0;i<n;i++)
		scanf("%d", &a[i]);
	for(i=0;i<n;i++)
		scanf("%d", &b[i]);
	
	for(i=0;i<n;i++)
		v[a[i]].push_back(b[i]);
	
	vector<int> sor;
	int cnt = 0;
	for(i=1;i<=k;i++)
	{
		if(v[i].empty())
		{
			cnt++;
			continue;
		}
		
		sort(v[i].begin(), v[i].end());
		for(int j = 0; j<(int)v[i].size()-1; j++)
			sor.push_back(v[i][j]);
	}
	
	sort(sor.begin(), sor.end());
	
	long long res = 0;
	for(i=0; i<cnt; i++)
		res += sor[i];
		
	printf("%lld\n", res);
	return 0;
}
