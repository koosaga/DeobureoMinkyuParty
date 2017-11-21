#include<bits/stdc++.h>

using namespace std;

struct ord
{
	int id, t, p, v, tv, cv, pr;
	bool operator <(const ord &x) const
	{
		return p != x.p ? p < x.p : pr < x.pr;
	}
};

struct tra
{
	int bid, sid, p, v;
	bool operator <(const tra &x) const
	{
		return bid != x.bid ? bid < x.bid : sid < x.sid;
	}
};

set<int> bp, sp;
vector<ord> bo[100010], so[100010];
vector<tra> res;
vector<ord> book;

long long myrem(long long a, long long b)
{
	return a % b ? a % b : b;
}

int main()
{
	freopen("iceberg.in", "r", stdin);
	//freopen("iceberg.out", "w", stdout);
	
	int n, id, t, p, v, tv, cv, pr, x, tot, i, j, gp;
	long long sum, tmp, tmp2, s, g, m, c;
	scanf("%d", &n);
	gp = 0;
	for(i = 0; i < n; i++)
	{
		printf("i = %d\n", i);
		scanf("%d%d%d%d%d", &id, &t, &p, &v, &tv);
		
		if(t == 2) // SELL
		{
			int itercount = 0;
			while(1)
			{
				cerr <<"ITER:" << ++itercount<<endl;
				auto it = bp.end();
				if(it == bp.begin())
				{
					cv = min(v, tv);
					so[p].push_back({id, t, p, v, tv, cv, gp++});
					sp.insert(p);
					break;
				}
				it--;
				if(*it < p)
				{
					cv = min(v, tv);
					so[p].push_back({id, t, p, v, tv, cv, gp++});
					sp.insert(p);
					break;
				}
				
				x = *it;
				tot = bo[x].size();
				
				printf("xtot %d %d\n", x, tot);
				
				s = 1;
				g = 1LL * v * tot;
				while(s < g)
				{
					m = (s + g) / 2;
					sum = 0;
					for(j = 0; j < tot; j++)
					{
						if(j < m % tot)
							c = m / tot + 1;
						else
							c = m / tot;
						if(c)
						tmp = min(bo[x][j].cv + 1LL*bo[x][j].tv*(c-1), 0LL + bo[x][j].v);
						else tmp = 0;
						assert(bo[x][j].cv <= bo[x][j].tv);
						sum += tmp;
					}
					
					if(sum < v)
						s = m+1;
					else
						g = m;
					cerr << m << " " << sum << endl;
				}
				
				sum = 0;
				for(j = 0; j < tot; j++)
				{
					if(j < s % tot)
						c = s / tot + 1;
					else
						c = s / tot;
					
					if(c)
					tmp = min(bo[x][j].cv + 1LL*bo[x][j].tv*(c-1), 0LL + bo[x][j].v);
					else tmp = 0;
					
					if(j == (s + tot - 1) % tot)
					{
						tmp2 = tmp;
						continue;
					}
					
					res.push_back({bo[x][j].id, id, x, tmp});
					
					//v -= tmp;
					
					if(tmp == bo[x][j].v)
						bo[x][j].v = bo[x][j].cv = 0;
					else if(tmp < bo[x][j].cv)
					{
						bo[x][j].v -= tmp;
						bo[x][j].cv -= tmp;
					}
					else
					{
						bo[x][j].v -= tmp;
						bo[x][j].cv = min(0LL + bo[x][j].v, bo[x][j].tv - (tmp - bo[x][j].cv) % bo[x][j].tv);
					}
					
					sum += tmp;
				}
				cerr << "XX" << s << " " << sum << endl;
				printf("VV %lld\n", v - sum);
				tmp = min(tmp2, v - sum);
				j = (s + tot - 1) % tot;
				
				v -= tmp;				
				
				res.push_back({bo[x][j].id, id, x, tmp});
				
				if(tmp == bo[x][j].v)
					bo[x][j].v = bo[x][j].cv = 0;
				else if(tmp < bo[x][j].cv)
				{
					bo[x][j].v -= tmp;
					bo[x][j].cv -= tmp;
				}
				else
				{
					bo[x][j].v -= tmp;
					bo[x][j].cv = min(0LL + bo[x][j].v, bo[x][j].tv - (tmp - bo[x][j].cv) % bo[x][j].tv);
				}
				
				bp.erase(x);
				
				vector<ord> nv;
				for(j = (s + tot - 1) % tot + 1; j < tot + (s + tot - 1) % tot + 1; j++)
				{
					if(bo[x][j%tot].v)
					{
						bp.insert(x);
						bo[x][j%tot].pr = gp++;
						nv.push_back(bo[x][j%tot]);
					}
				}
				bo[x] = nv;
				
				if(v == 0)
					break;
			}
		}
		
		else if(t == 1) // BUY
		{
			while(1)
			{
				auto it = sp.begin();
				if(it == sp.end())
				{
					cv = min(v, tv);
					bo[p].push_back({id, t, p, v, tv, cv, gp++});
					bp.insert(p);
					break;
				}
				if(*it > p)
				{
					cv = min(v, tv);
					bo[p].push_back({id, t, p, v, tv, cv, gp++});
					bp.insert(p);
					break;
				}
				
				x = *it;
				tot = so[x].size();
				
				printf("xtot %d %d\n", x, tot);
				
				s = 1;
				g = 1LL * v * tot;
				while(s < g)
				{
					m = (s + g) / 2;
					sum = 0;
					for(j = 0; j < tot; j++)
					{
						if(j < m % tot)
							c = m / tot + 1;
						else
							c = m / tot;
						if(c)
						tmp = min(so[x][j].cv + 1LL*so[x][j].tv*(c-1), 0LL + so[x][j].v);
						else tmp = 0;
						sum += tmp;
					}
					
					if(sum < v)
						s = m+1;
					else
						g = m;
				}
				
				sum = 0;
				for(j = 0; j < tot; j++)
				{
					if(j < s % tot)
						c = s / tot + 1;
					else
						c = s / tot;
					if(c)
					tmp = min(so[x][j].cv + 1LL*so[x][j].tv*(c-1), 0LL + so[x][j].v);
					else tmp = 0;
					
					if(j == (s + tot - 1) % tot)
					{
						tmp2 = tmp;
						continue;
					}
					
					res.push_back({id, so[x][j].id, x, tmp});
					
					//v -= tmp;
					
					if(tmp == so[x][j].v)
						so[x][j].v = so[x][j].cv = 0;
					else if(tmp < so[x][j].cv)
					{
						so[x][j].v -= tmp;
						so[x][j].cv -= tmp;
					}
					else
					{
						so[x][j].v -= tmp;
						so[x][j].cv = min(0LL + so[x][j].v, so[x][j].tv - (tmp - so[x][j].cv) % so[x][j].tv);
					}
					
					sum += tmp;
				}
				
				tmp = min(tmp2, v - sum);
				j = (s + tot - 1) % tot;
				
				v -= tmp;
				
				res.push_back({id, so[x][j].id, x, tmp});
				
				if(tmp == so[x][j].v)
					so[x][j].v = so[x][j].cv = 0;
				else if(tmp < so[x][j].cv)
				{
					so[x][j].v -= tmp;
					so[x][j].cv -= tmp;
				}
				else
				{
					so[x][j].v -= tmp;
					so[x][j].cv = min(0LL + so[x][j].v, so[x][j].tv - (tmp - so[x][j].cv) % so[x][j].tv);
				}
				
				sp.erase(x);
				
				vector<ord> nv;
				for(j = (s + tot - 1) % tot + 1; j < tot + (s + tot - 1) % tot + 1; j++)
				{
					if(so[x][j%tot].v)
					{
						
						sp.insert(x);
						so[x][j%tot].pr = gp++;
						nv.push_back(so[x][j%tot]);
					}
				}
				so[x] = nv;
				
				if(v == 0)
					break;
			}
		}
	}
	
	sort(res.begin(), res.end());
	for(i=1;i<=100000;i++)
	{
		for(ord &t : bo[i])
			book.push_back(t);
		for(ord &t : so[i])
			book.push_back(t);
	}
	sort(book.begin(), book.end());
	
	for(tra &t : res)
	{
		printf("%d %d %d %d\n", t.bid, t.sid, t.p, t.v);
	}
	printf("\n");
	for(ord &t : book)
	{
		printf("%d %d %d %d %d %d\n", t.id, t.t, t.p, t.v, t.tv, t.cv);
	}
	
	return 0;
}
















