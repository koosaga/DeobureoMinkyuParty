#include <bits/stdc++.h>

using namespace std;

const int mod = 1000000007;
int mem[2510][2510];

int main()
{
	int n, k, i, j;
	scanf("%d%d", &n, &k);
	
	mem[1][1] = k;
	for(i=2;i<=n;i++)
	{
		for(j=1;j<=i;j++)
		{
			mem[i][j] = (1LL * mem[i-1][j-1] * (k - j + 1) + 1LL * mem[i-1][j] * (j-1)) % mod;
			
		}
	}
	
	printf("%d\n", mem[n][k]);
	return 0;
}
