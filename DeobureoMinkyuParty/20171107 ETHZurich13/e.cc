#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 405;

struct mf{
    struct edg{int pos, cap, rev;};
    vector<edg> gph[MAXN];
    void clear(){for(int i=0;i<MAXN;i++)gph[i].clear();}
    void add_edge(int s, int e, int x)
    {
        gph[s].push_back({e, x, (int)gph[e].size()});
        gph[e].push_back({s, 0, (int)gph[s].size() - 1});
    }
    
    int dis[MAXN], pnt[MAXN];
    bool bfs(int src, int sink)
    {
        memset(dis, 0, sizeof dis);
        memset(pnt, 0, sizeof pnt);
        queue<int> que;
        que.push(src);
        dis[src] = 1;
        while(!que.empty())
        {
            int x = que.front();
            que.pop();
            for(auto &e : gph[x])
            {
                if(e.cap > 0 && !dis[e.pos])
                {
                    dis[e.pos] = dis[x] + 1;
                    que.push(e.pos);
                }
            }
        }
        return dis[sink] > 0;
    }
    
    int dfs(int x, int sink, int f)
    {
        if(x == sink) return f;
        for(; pnt[x] < gph[x].size(); pnt[x]++){
            edg e = gph[x][pnt[x]];
            if(e.cap > 0 && dis[e.pos] == dis[x] + 1)
            {
                int w = dfs(e.pos, sink, min(f, e.cap));
                if(w)
                {
                    gph[x][pnt[x]].cap -= w;
                    gph[e.pos][e.rev].cap += w;
                    return w;
                }
            }
        }
        return 0;
    }
    lint match(int src, int sink)
    {
        lint ret = 0;
        while(bfs(src, sink)) {
            int r;
            while((r = dfs(src, sink, 2e9))) ret +=r;
            }
            return ret;
   }    
}mf;

int n, m, k;
struct edg{int s, e, idx;}a[10005];
int chk[MAXN][MAXN];
vector<pi> gph[MAXN];
int lbl[10005];

void solve(vector<int> v){
	int d1[MAXN] = {}, d2[MAXN] = {};
	int p1 = 0, p2 = 0;
	int cnt = ((n + 1) / 2) * k;
	for(auto &i : v){
		int l = a[i].s - 1;
		int r = a[i].e - n / 2 - 1;
		gph[l].push_back(pi(r, a[i].idx));
		d1[l]++;
		d2[r]++;
		cnt--;
	}
	while(cnt > 0){
		while(d1[p1] == k) p1++;
		while(d2[p2] == k) p2++;
		d1[p1]++;
		d2[p2]++;
		gph[p1].push_back(pi(p2, -1));
		cnt--;
	}
	n = (n + 1) / 2;
	for(int i=1; i<=k; i++){
		mf.clear();
		for(int j=0; j<n; j++){
			mf.add_edge(0, j + 1, 1);
			mf.add_edge(j + n + 1, n + n + 1, 1);
			for(auto &k : gph[j]){
				mf.add_edge(j + 1, k.first + n + 1, 1);
			}
		}
		mf.match(0, n + n + 1);
		vector<pi> v;
		for(int i=1; i<=n; i++){
			for(auto &j : mf.gph[i]){
				if(j.cap == 0 && j.pos > n){
					v.push_back(pi(i-1, j.pos-n-1));
					break;
				}
			}
		}
		vector<int> w;
		for(auto &i : v){
			for(int j=0; j<gph[i.first].size(); j++){
				if(gph[i.first][j].first == i.second){
					w.push_back(gph[i.first][j].second);
					gph[i.first].erase(gph[i.first].begin() + j);
					break;
				}
			}
		}
		for(auto &j : w) if(j != -1) lbl[j] = i;
	}
	sort(v.begin(), v.end());
	for(auto &i : v) printf("%d %d\n", i, lbl[i]);
}

int main(){
	vector<int> v;
	cin >> n >> m >> k;
	for(int i=1; i<=m; i++){
		scanf("%d %d",&a[i].s,&a[i].e);
		chk[a[i].s][a[i].e] = i;
		a[i].idx = i;
	}
	for(int i=1; i<=n/2; i++) mf.add_edge(0, i, k);
	for(int i=n/2+1; i<=n; i++) mf.add_edge(i, n+1, k);
	for(int i=1; i<=m; i++){
		mf.add_edge(a[i].s, a[i].e, 1);
	}
	mf.match(0, n + 1);
	vector<int> edg;
	for(int i=1; i<=n/2; i++){
		for(auto &j : mf.gph[i]){
			if(j.pos > n / 2 && j.cap == 0){
				int edg = chk[i][j.pos];
				v.push_back(edg);
			}
		}
	}
	cout << v.size() << endl;
	solve(v);
}
