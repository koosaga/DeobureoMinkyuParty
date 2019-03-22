#include <bits/stdc++.h>

using namespace std;

struct pos
{
	int x, y, z;
};

pos arr[51];
double prob[51];

int main()
{
	int n, i, j, k, l;
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%lf%d%d%d", &prob[i], &arr[i].x, &arr[i].y, &arr[i].z);

	if(n <= 3)
	{
		double r = 0;
		for(i=0; i<n; i++)
			r += prob[i];
		printf("%.10lf\n", r);
		return 0;
	}

	double r = 0;
	for(i=0; i<n; i++)
	{
		for(j=i+1; j<n; j++)
		{
			for(k=j+1; k<n; k++)
			{
				pos v1 = { arr[j].x - arr[i].x, arr[j].y - arr[i].y, arr[j].z - arr[i].z };
				pos v2 = { arr[k].x - arr[i].x, arr[k].y - arr[i].y, arr[k].z - arr[i].z };

				pos h = { v1.y * v2.z - v2.y * v1.z,
				          -(v1.x * v2.z - v2.x * v1.z),
				          v1.x * v2.y - v2.x * v1.y };

				long long d = -(1LL * h.x * arr[i].x + 1LL * h.y * arr[i].y + 1LL * h.z * arr[i].z);

				assert(1LL * h.x * arr[i].x + 1LL * h.y * arr[i].y + 1LL * h.z * arr[i].z + d == 0);
				assert(1LL * h.x * arr[j].x + 1LL * h.y * arr[j].y + 1LL * h.z * arr[j].z + d == 0);
				assert(1LL * h.x * arr[k].x + 1LL * h.y * arr[k].y + 1LL * h.z * arr[k].z + d == 0);

				double p1 = 1;
				double p2 = 1;
				for(l=0; l<n; l++)
				{
					if(l == i || l == j || l == k)
						continue;

					assert(1LL * h.x * arr[l].x + 1LL * h.y * arr[l].y + 1LL * h.z * arr[l].z + d != 0);

					if(1LL * h.x * arr[l].x + 1LL * h.y * arr[l].y + 1LL * h.z * arr[l].z + d > 0)
						p1 *= 1 - prob[l];
					else
						p2 *= 1 - prob[l];
				}

				r += prob[i] * prob[j] * prob[k] * (p1 + p2 - 2 * p1 * p2);
				//printf("%d %d %d: %lf * (%lf + %lf - %lf)  (%lf)\n", i, j, k, prob[i] * prob[j] * prob[k] ,p1 , p2, 2 * p1 * p2, p1 + p2 - 2 * p1 * p2);
			}
		}
	}

	r = 0.5 * r;

	double r0 = 1;
	for(i=0; i<n; i++)
		r0 *= 1 - prob[i];

	double r1 = 0;
	for(i=0; i<n; i++)
	{
		double c = prob[i];
		for(j=0; j<n; j++)
		{
			if(i == j)
				continue;
			c *= 1 - prob[j];
		}

		r1 += c;
	}

	double r2 = 0;
	for(i=0; i<n; i++)
	{
		for(j=i+1; j<n; j++)
		{
			double c = prob[i] * prob[j];
			for(k=0; k<n; k++)
			{
				if(k == i || k == j)
					continue;
				c *= 1 - prob[k];
			}

			r2 += c;
		}
	}

	double r3 = 0;
	for(i=0; i<n; i++)
	{
		for(j=i+1; j<n; j++)
		{
			for(k=j+1; k<n; k++)
			{
				double c = prob[i] * prob[j] * prob[k];
				for(l=0; l<n; l++)
				{
					if(l == i || l == j || l == k)
						continue;
					c *= 1 - prob[l];
				}
				r3 += c;
			}
		}
	}


	double t = 2 * (1 - r0 - r1 - r2 - r3);

	printf("%.10lf\n", r + 1 * r1 + 2 * r2 + 3 * r3 + t);

	return 0;
}







