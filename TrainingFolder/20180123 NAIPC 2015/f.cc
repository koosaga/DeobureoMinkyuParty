#include<bits/stdc++.h>
using namespace std;



const int MAXN = 505;
const long double eps = 1e-12;

struct circ
{
	struct edg{
		int pos;
		long double cap;
		int rev;
	};
	vector<edg> gph[MAXN];
	void clear(){
		for(int i=0; i<MAXN; i++)gph[i].clear();
	}
	void add_edge(int s, int e, long double unused, long double x){
		gph[s].push_back({e, x, (int)gph[e].size()});
		gph[e].push_back({s, 0, (int)gph[s].size()-1});
	}
	int dis[MAXN], pnt[MAXN];
	bool bfs(int src, int sink){
		memset(dis, 0, sizeof(dis));
		memset(pnt, 0, sizeof(pnt));
		queue<int> que;
		que.push(src);
		dis[src] = 1;
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(auto &e : gph[x]){
				if(e.cap > eps && !dis[e.pos]){
					dis[e.pos] = dis[x] + 1;
					que.push(e.pos);
				}
			}
		}
		return dis[sink] > 0;
	}
	long double dfs(int x, int sink, long double f){
		if(x == sink) return f;
		for(; pnt[x] < gph[x].size(); pnt[x]++){
			edg e = gph[x][pnt[x]];
			if(e.cap > eps && dis[e.pos] == dis[x] + 1){
				long double w = dfs(e.pos, sink, min(f, e.cap));
				if(w > eps){
					gph[x][pnt[x]].cap -= w;
					gph[e.pos][e.rev].cap += w;
					return w;
				}
			}
		}
		return 0;
	};
	long double solve(int src, int sink){
		long double ret = 0;
		while(bfs(src, sink)){
			long double r;
			while((r = dfs(src, sink, 2e9)) > eps) ret += r;
		}
		return ret;
	}
} circ;
/*
struct circ{
	maxflow mf;
	long double lsum;
	void clear(){
		lsum = 0;
		mf.clear();
	}
	void add_edge(int s, int e, long double l, long double r){
		lsum += l;
		mf.add_edge(s+2, e+2, r-l);
		mf.add_edge(0, e+2, l);
		mf.add_edge(s+2, 1, l);
	}
	bool solve(int s, int e){
		mf.add_edge(e+2, s+2, 1e9);
		return fabs(lsum - mf.match(0, 1)) < 1e-8;
	}
}circ;
*/
long double cap[210];
long double pos[210];
long double vmin[210][210];
long double vmax[210][210];
long double sum[210];
long double width[210];
long double height[210];

int main(){
    int n, m, w, h, i, j;
    cin >> n >> m >> w >> h;
    for(i=1;i<=m;i++)
        cin >> cap[i];
    for(i=1;i<n;i++)
        cin >> pos[i];
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            cin >> vmin[i][j];
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            cin >> vmax[i][j];
    
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            cap[j] -= vmin[i][j];
            vmax[i][j] -= vmin[i][j];
            
            sum[i] += vmin[i][j];
        }
    }
    
    pos[0] = 0;
    pos[n] = w;
    for(i=1;i<=n;i++)
        width[i] = pos[i] - pos[i-1];
    
    for(i=1;i<=n;i++)
        height[i] = sum[i] / width[i];
    
    long double hmax = 0;
    long double hmin = 1e18;
    for(i=1;i<=n;i++)
    {
        hmax = max(hmax, height[i]);
        hmin = min(hmin, height[i]);
    }
    long double s, g, x;
    s = hmin;
    g = hmax;
    while(g - s > 1e-5)
    {
        x = (s+g)/2;
        
        circ.clear();
        
        for(i=1;i<=m;i++)
        {
            circ.add_edge(1, i+1, 0, cap[i]);
            for(j=1;j<=n;j++)
                circ.add_edge(i+1, j+m+1, 0, vmax[j][i]);
        }
        
        long double expect = 0;
        for(i=1;i<=n;i++)
        {
            if(height[i] >= x)
                continue;
            
            circ.add_edge(i+m+1, m+n+2, 0, width[i] * (x - height[i]));
            expect += width[i] * (x - height[i]);
        }
        
        long double ans = circ.solve(1, m+n+2);
        
        if(fabs(ans - expect) < 1e-9 * w)
            s = x;
        else
            g = x;
    }
    
    cout << hmax - (s+g)/2 << endl;
    return 0;
}














