#include<bits/stdc++.h>

using namespace std;

double me[100];
double opp[100];

void send(int x, double p)
{
	printf("%d %.15lf\n", x, p);
	fflush(stdout);
}

mt19937 rng(9801);

int read(int i)
{
	int x;
	double p;
	scanf("%d%lf", &x, &p);
	//int t = uniform_int_distribution<int>(1, i / 2)(rng);
	//x = 2 * t - 1;
	return x;
}

int main()
{
	int t, n, i, j, k;
	scanf("%d%d", &t, &n);
	//t = 100000;
	//for(int bb=1; bb<=30; bb+=2)
	//{
	//	n = bb;
	for(i=1; i<=t; i++)
	{
		memset(me, 0, sizeof me);
		memset(opp, 0, sizeof opp);

		opp[0] = 1;
		for(j=1; j<=n; j++)
		{
			int x;
			double p;
			if(j % 2 == 1)
			{
				if(j == n)
				{
					x = 0;
					p = 2.0 / 3;
				}
				else if(j == 1)
				{
					x = 0;
					p = 1.0 / 3;
				}
				else
				{
					x = 2;
					p = 2.0 / 3;
					for(k=2; k<=j; k += 2)
					{
						if(opp[k] > opp[x])
							x = k;
					}
				}

				send(x, p);
				me[j] = opp[x] * p;
				opp[x] = opp[x] * (1 - p);
			}
			else
			{
				int x = read(j);
				double p = 2.0 / 3;
				opp[j] = me[x] * p;
				me[x] = me[x] * (1 - p);
			}
		}

		int ans;
		scanf("%d", &ans);
		if(ans == 0)
			return 0;

		/*
		double sum = 0;
		for(j = 1; j <= n; j++)
			sum += me[j];

		if(sum < 0.55 + 1e-9)
		{
			printf("Test # %d fail!\n", i);
		}

		printf("sum = %.10lf\n", sum);
		*/
	}

	return 0;
}



