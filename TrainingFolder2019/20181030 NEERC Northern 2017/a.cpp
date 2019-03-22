#include <bits/stdc++.h>

using namespace std;

int mem[1000010];
int cnt[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int main()
{
	freopen("auxiliary.in", "r", stdin);
	freopen("auxiliary.out", "w", stdout);
	int n, i, j;
	scanf("%d", &n);
	
	mem[0] = 0;
	for(i = 1; i <= n; i++)
	{
		mem[i] = -1e9;
		for(j = 0; j < 10; j++)
		{
			if(i - cnt[j] >= 0)
				mem[i] = max(mem[i], mem[i - cnt[j]] + j);
		}
	}
	
	printf("%d\n", mem[n]);
	return 0;	
}
