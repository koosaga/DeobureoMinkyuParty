#include <bits/stdc++.h>
using namespace std;

char arr[1010];

void solve()
{
	int n, i, j;
	scanf("%s", arr);
	
	n = strlen(arr);
	int r = 1e9;
	for(i=0; i<n; i++)
		for(j=i+1;j<n;j++)
			if(arr[i] == arr[j])
				r = min(r, j - i);
	
	if(r == 1e9)
		puts("-1");
	else
		printf("%d\n", r);
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=1; i<=t; i++)
	{
		printf("Case #%d: ", i);
		solve();
	}
	return 0;
}
