#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t, i;
	scanf("%d", &t);
	for(int b=0; b<t; b++)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		for(i=0; i<n+m; i++)
			scanf("%*d");

		if(n <= m)
			puts("Yes");
		else
			puts("No");
	}
	return 0;
}