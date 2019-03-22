#include <bits/stdc++.h>

using namespace std;

char typ[200010];
int len[200010];

int nex[200010];
bool chk[200010];
vector<int> fre[200010];

int main()
{
	int n, d, i;
	scanf("%d%d", &n, &d);
	for(i=0; i<n; i++)
		scanf(" %c%d", &typ[i], &len[i]);

	nex[n - 1] = n - 1;
	for(i=n-2; i>=0; i--)
	{
		if(typ[i] == 'B')
			nex[i] = nex[i + 1];
		else
			nex[i] = i;
	}

	vector<int> sor;
	for(i=0; i<n; i++)
	{
		if(chk[i])
			continue;

		if(typ[i] == 'B')
		{
			if(!chk[nex[i]])
			{
				chk[nex[i]] = 1;
				sor.push_back(nex[i]);
			}
		}

		chk[i] = 1;
		sor.push_back(i);
	}

	int s, g;
	s = 1;
	g = n;
	while(s < g)
	{
		int x = (s + g) / 2;



	}


	return 0;
}