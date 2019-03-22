#include <bits/stdc++.h>
using namespace std;

int A[110];
int B[110];
int C[110];

int P[110];
int Q[110];
int R[110];

int a[110];
int b[110];
int c[110];
int d[100];

char solve()
{
	int n, i;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d", &A[i]);
	for(i=0; i<n; i++)
		scanf("%d", &P[i]);
	for(i=0; i<n; i++)
		scanf("%d", &B[i]);
	for(i=0; i<n; i++)
		scanf("%d", &Q[i]);
	for(i=0; i<n; i++)
		scanf("%d", &C[i]);
	for(i=0; i<n; i++)
		scanf("%d", &R[i]);
	
	for(i=0; i<n; i++)
	{
		a[i] = A[i] + B[i];
		b[i] = (P[i] ? 0 : A[i]) + (Q[i] ? 0 : B[i]);
		c[i] = C[i];
		d[i] = (R[i] ? 0 : C[i]);
		
		if(a[i] > c[i])
		{
			swap(a[i], c[i]);
			swap(b[i], d[i]);
		}
	}
	
	bool ok = 1;
	for(i=0; i<n; i++)
		if(a[i] != c[i])
			ok = 0;
	if(ok)
		return 'A';
	
	for(int x=0; x<2*n; x++)
	{
		if(x % 2 == 0)
		{
			if(a[x / 2] == b[x / 2])
				continue;
			a[x / 2]--;
		}
		else
		{
			if(c[x / 2] == d[x / 2])
				continue;
			c[x / 2]--;
		}
		
		bool fin = 1;
		for(i=0; i<n; i++)
			if(a[i] != c[i])
				fin = 0;
		
		if(fin)
			return 'A';
		
		ok = 1;
		long long s = 0;
		int cnt = 0;
		int c1, a1, c2, a2;
		for(i=0; i<n; i++)
		{
			if(b[i] == d[i])
				s += c[i] - a[i];
			else if(b[i] < d[i] || a[i] == c[i])
			{
				ok = 0;
				break;
			}
			else
			{
				if(cnt >= 2)
				{
					ok = 0;
					break;
				}
				if(cnt == 0)
				{
					c1 = c[i];
					a1 = a[i];
				}
				else if(cnt == 1)
				{
					c2 = c[i];
					a2 = a[i];
				}
				cnt++;
			}
		}
		if(ok)
		{
			if(cnt == 0)
				return 'A';
			else if(cnt == 1)
			{
				if(c1 - a1 >= s)
					return 'A';
				else
					ok = 0;
			}
			else if(cnt == 2)
			{
				if(c1 - a1 != c2 - a2 || s != 0)
					ok = 0;
				else
					return 'A';
			}
			else
				ok = 0;
		}
		
		assert(!ok);
		
		if(x % 2 == 0)
			a[x / 2]++;
		else
			c[x / 2]++;
	}
	return 'B';
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=1; i<=t; i++)
	{
		printf("Case #%d: ", i);
		char r = solve();
		if(r == 'A')
			puts("Tweek");
		else if(r == 'B')
			puts("Craig");
		else
			assert(0);
	}
	return 0;
}
