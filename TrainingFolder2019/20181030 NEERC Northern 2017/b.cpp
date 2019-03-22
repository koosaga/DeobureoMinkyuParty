#include <bits/stdc++.h>

using namespace std;

char arr[1010];
bool chk[2][52];

int main()
{
	freopen("boolean.in", "r", stdin);
	freopen("boolean.out", "w", stdout);
	int n, i;
	scanf("%s", arr);
	
	n = strlen(arr);
	int u = 0;
	for(i=0; i<n; i++)
	{
		if(arr[i] == '|')
			continue;
		
		if(arr[i] == '~')
		{
			u = 1;
			continue;
		}
		
		if(islower(arr[i]))
			chk[u][arr[i] - 'a'] = 1;
		else
			chk[u][arr[i] - 'A' + 26] = 1;
			
		u = 0;
	}
	
	long long r = 1;
	bool t = 0;
	for(i = 0; i<52; i++)
	{
		if(chk[0][i] || chk[1][i])
			r *= 2;
		
		if(chk[0][i] && chk[1][i])
			t = 1;
	}
	
	if(!t)
		r--;
	
	printf("%lld\n", r);
	return 0;
}
