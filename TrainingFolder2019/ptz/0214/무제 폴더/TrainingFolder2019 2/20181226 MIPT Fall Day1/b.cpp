#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
	{
		int x;
		scanf("%d", &x);
		if(x % 2 == 1)
			puts("Balanced");
		else
			puts("Bad");
	}
	return 0;
}