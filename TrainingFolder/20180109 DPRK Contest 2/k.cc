#include<bits/stdc++.h>

using namespace std;

struct edg
{
	int x;
	long long w;
	bool operator <(const edg &e) const
	{
		return w > e.w;
	}
};

vector<edg> arr[100010];
long long dis[100010][2];
const long long INF = 1e15;

priority_queue<edg> pq;

int main()
{
	int n, m, x, y, i;
	long long w, nw;
	scanf("%d%d", &n, &m);
	for(i=0;i<m;i++)
	{
		scanf("%d%d%lld", &x, &y, &w);
		arr[x].push_back({y, w});
		arr[y].push_back({x, w});
	}
	
	for(i=1;i<=n;i++)
		dis[i][0] = dis[i][1] = INF;
	dis[1][0] = 0;
	pq.push({1, 0});
	while(!pq.empty())
	{
		x = pq.top().x;
		w = pq.top().w;
		pq.pop();
		
		for(auto &e : arr[x])
		{
			y = e.x;
			nw = w + e.w;
			
			if(nw <= dis[y][0])
			{
				dis[y][1] = dis[y][0];
				dis[y][0] = nw;
				pq.push({y, nw});
			}
			else if(nw < dis[y][1])
			{
				dis[y][1] = nw;
				pq.push({y, nw});
			}
		}
	}
	
	printf("%lld", dis[n][1]);
    return 0;
}
