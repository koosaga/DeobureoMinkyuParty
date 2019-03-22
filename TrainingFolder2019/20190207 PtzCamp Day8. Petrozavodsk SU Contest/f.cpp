#include <bits/stdc++.h>

using namespace std;

struct pos
{
	long long x, y;
};

struct frac
{
	long long p, q;
	frac(long long ap = 0, long long aq = 0)
	{
		p = ap;
		q = aq;
		if(q < 0)
		{
			p = -p;
			q = -q;
		}
	}
	bool operator <(const frac &a) const
	{
		return 1LL * p * a.q < 1LL * a.p * q;
	}
};

vector<pos> pot[51];

int main()
{
	int lim, n, i, j, k;
	pos fr, fl, bl, br;
	scanf("%d", &lim);
	scanf("%lld%lld", &fr.x, &fr.y);
	scanf("%lld%lld", &fl.x, &fl.y);
	scanf("%lld%lld", &bl.x, &bl.y);
	scanf("%lld%lld", &br.x, &br.y);
	scanf("%d", &n);
	for(i=0; i<n; i++)
	{
		int m;
		scanf("%d", &m);
		for(j=0; j<m; j++)
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			if(z == 0)
				pot[i].push_back({x, y});
		}
	}

	
	long long dx = fr.x - br.x;
	long long dy = fr.y - br.y;

	vector<pair<frac, double>> sor;
	for(i=0; i<n; i++)
	{
		int sz = (int)pot[i].size();
		frac fir(-1, 0);
		double bd;
		for(j=0; j<sz; j++)
		{
			for(k=j+1; k<sz; k++)
			{
				pos p1 = pot[i][j];
				pos p2 = pot[i][k];
				{
					long long a, b, c, d, e, f;
					a = fr.y - br.y;
					b = -(fr.x - br.x);
					c = fr.x * br.y - br.x * fr.y;

					d = p2.y - p1.y;
					e = -(p2.x - p1.x);
					f = p2.x * p1.y - p1.x * p2.y;

					if(a * e != b * d)
					{
						long long p, q, r, s;
						p = b * f - c * e;
						q = a * e - b * d;
						if(q < 0)
						{
							p = -p;
							q = -q;
						}
						r = c * d - a * f;
						s = a * e - b * d;
						if(s < 0)
						{
							r = -r;
							s = -s;
						}

						if(min(p1.x, p2.x) * q <= p && p <= max(p1.x, p2.x) * q &&
						   min(p1.y, p2.y) * s <= r && r <= max(p1.y, p2.y) * s)
						{
							if(dx != 0)
							{
								frac t(p - fr.x * q, q * dx);
								if(t.p >= 0 && (fir < frac(0, 1) || t < fir))
								{
									//printf("ipq %d (%.5lf / %.5lf)\n", i, 1.0 * p / q, 1.0 * r / s);
									fir = t;
									bd = hypot(1.0 * p / q - fr.x, 1.0 * r / s - fr.y);
								}
							}
							else
							{
								frac t(r - fr.y * s, s * dy);
								if(t.p >= 0 && (fir < frac(0, 1) || t < fir))
								{
									fir = t;
									bd = hypot(1.0 * p / q - fr.x, 1.0 * r / s - fr.y);
								}
							}
						}
					}
				}
				{
					long long a, b, c, d, e, f;
					a = fl.y - bl.y;
					b = -(fl.x - bl.x);
					c = fl.x * bl.y - bl.x * fl.y;

					d = p2.y - p1.y;
					e = -(p2.x - p1.x);
					f = p2.x * p1.y - p1.x * p2.y;

					if(a * e != b * d)
					{
						long long p, q, r, s;
						p = b * f - c * e;
						q = a * e - b * d;
						if(q < 0)
						{
							p = -p;
							q = -q;
						}
						r = c * d - a * f;
						s = a * e - b * d;
						if(s < 0)
						{
							r = -r;
							s = -s;
						}

						if(min(p1.x, p2.x) * q <= p && p <= max(p1.x, p2.x) * q &&
						   min(p1.y, p2.y) * s <= r && r <= max(p1.y, p2.y) * s)
						{
							if(dx != 0)
							{
								frac t(p - fl.x * q, q * dx);
								if(t.p >= 0 && (fir < frac(0, 1) || t < fir))
								{
									//printf("ipq %d (%.5lf / %.5lf)\n", i, 1.0 * p / q, 1.0 * r / s);
									fir = t;
									bd = hypot(1.0 * p / q - fl.x, 1.0 * r / s - fl.y);
								}
							}
							else
							{
								frac t(r - fl.y * s, s * dy);
								if(t.p >= 0 && (fir < frac(0, 1) || t < fir))
								{
									fir = t;
									bd = hypot(1.0 * p / q - fl.x, 1.0 * r / s - fl.y);
								}
							}
						}
					}
				}
			}
		}

		if(frac(0, 1) < fir)
		{
			sor.push_back({fir, bd});
			//printf("i bd %d %.10lf\n", i, bd);
		}
	}

	int sz = (int)sor.size();
	if(sz <= lim)
	{
		puts("oo");
		return 0;
	}

	sort(sor.begin(), sor.end());
	printf("%.10lf\n", sor[lim].second);
	return 0;
}




