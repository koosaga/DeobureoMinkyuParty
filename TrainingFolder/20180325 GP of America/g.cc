#include<bits/stdc++.h>
using namespace std;

#define left kurgvklu

struct edg
{
    int x, y, w;
    bool operator <(const edg &a) const
    {
        return w < a.w;
    }
};

int n;
const int INF = 1e6;

int par[110];
int root(int x)
{
    return x == par[x] ? x : (par[x] = root(par[x]));
}
bool merge(int x, int y)
{
    x = root(x);
    y = root(y);
    if(x == y)
        return 0;
    par[x] = y;
    return 1;
}

pair<int, int> mst(vector<edg> &RB, vector<edg> &G, vector<edg> &left)
{
    sort(RB.begin(), RB.end());
    
    for(int i=1;i<=n;i++)
        par[i] = i;
    
    int c1 = 0, c2 = 0;
    for(edg &e : G)
    {
        if(merge(e.x, e.y))
            c1++;
    }
    
    int res = 0;
    for(edg &e : RB)
    {
        if(merge(e.x, e.y))
        {
            c2++;
            res += e.w;
        }
        else
            left.push_back(e);
    }
    
    if(c1+c2 != n-1)
        return make_pair(INF * 10, c2);
    
    return make_pair(res, c2);
}

vector<edg> R, G, B;
bool chk[110];

int res[110];
int mem[110];
int cnt[110];
vector<edg> left[110];

int kres[110];

int main()
{
    int m, i, j, k;
    scanf("%d%d", &n, &m);
    for(i=0; i<m; i++)
    {
        int x, y, w;
        char c;
        scanf("%d%d%d %c", &x, &y, &w, &c);
        if(c == 'R')
            R.push_back({x, y, w});
        else if(c == 'G')
            G.push_back({x, y, w});
        else
            B.push_back({x, y, w});
    }
    
    sort(R.begin(), R.end());
    sort(B.begin(), B.end());
    sort(G.begin(), G.end());
    
    int gs = G.size();
    
    for(i=0; i<=gs; i++)
    {
        res[i] = INF;
        for(j=0;j<gs;j++)
        {
            if(chk[j])
                continue;
            
            int sumG = 0;
            vector<edg> newG;
            for(k=0; k<gs; k++)
            {
                if(i == 0 || !chk[k] && k != j)
                {
                    sumG += G[k].w;
                    newG.push_back(G[k]);
                }
            }
            vector<edg> leftR, leftB;
            int resR, resB;
            int cntR, cntB;
            tie(resR, cntR) = mst(R, newG, leftR);
            tie(resB, cntB) = mst(B, newG, leftB);
            
            int newRes = resR + resB + sumG;
            int newCnt = cntR + cntB + newG.size();
            if(newRes < res[i] || newRes == res[i] && newCnt < cnt[i])
            {
                if(i != 0)
                    mem[i] = j;
                
                res[i] = newRes;
                cnt[i] = newCnt;
                
                left[i].clear();
                for(edg &e : leftR)
                    left[i].push_back(e);
                for(edg &e : leftB)
                    left[i].push_back(e);
                sort(left[i].begin(), left[i].end());
            }
        }
        
        if(i != 0)
            chk[mem[i]] = 1;
    }
    
    for(i=1;i<=m;i++)
        kres[i] = INF;
    
    for(i=0;i<=gs;i++)
    {
        if(res[i] == INF)
            continue;
            
        sort(left[i].begin(), left[i].end());
        
        int addSum = 0;
        for(j=cnt[i]; j<=m; j++)
        {
            if(j != cnt[i])
                addSum += left[i][j-cnt[i]-1].w;
            kres[j] = min(kres[j], res[i] + addSum);
        }
    }
    
    for(i=1;i<=m;i++)
    {
        if(kres[i] == INF)
            printf("-1\n");
        else
            printf("%d\n", kres[i]);
    }
    return 0;
}

