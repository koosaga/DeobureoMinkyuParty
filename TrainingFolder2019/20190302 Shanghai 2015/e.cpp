#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
char arr[51];
long long mem[50][4][4][4];

void upd(int &x, long long v)
{
	x = (x + v) % mod;
}

void solve()
{
	int n, k, i, j;
	scanf("%d%s", &n, arr);
	n = strlen(arr);
	
	if(n <= 2)
	{
		puts("0");
		return 0;
	}
	
	int sp;
	for(i=0; i<n; i++)
		if(arr[i] == '*')
			sp = i;
	
	for(i=0; i<n; i++)
	{
		if(i == sp)
			continue;
		
		for(j=i+1; j<n; j++)
		{
			if(j == sp)
				continue;
			
			for(int s=0; s<k; s++)
			{
				for(int a=0; a<4; a++) // i
				{
					for(int b=0; b<4; b++) // j
					{
						if(a == b)
							continue;
					
						for(int c=0; c<4; c++) // *
						{
							if(c == a || c == b)
								continue;
							
							int &cur = mem[s][a][b][c];
						
							if(s == 0)
							{
								if(a == 0 && b == 1 && c == 2)
									cur = 1;
								else
									cur = 0;
								continue;
							}
							
							cur = 0;
							upd(cur, mem[s-1][a][b][c] * (n - 3) * (n - 4) / 2);
							
							
							
							if(a == 3)
							{
								upd(cur, mem[s-1][0][b][c] * 
							}
						}
					}
				}
			}
		}
	}
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
