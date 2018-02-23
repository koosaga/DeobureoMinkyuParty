#include <bits/stdc++.h>

using namespace std;
typedef long long lint;
const int MAXN = 5055;
struct seg
{
    int l, s, e, p;
    bool operator <(const seg &a) const
    {
        return l != a.l ? l < a.l : s < a.s;
    }
};

int arr[100010];
seg tmp[5010];

int len[5010];
int dp[MAXN][MAXN];
int opt[MAXN][MAXN];
int sta[5010];

long long calc(int x, int y)
{
    int m = y - x + 1;
    for(int i=0; i<=m+3; i++){
        for(int j=0; j<=m+3; j++){
            dp[i][j] = opt[i][j] = 0;
        }
    }
    for(int i=1; i<=m; i++) len[i] = len[i-1] + (tmp[x + i - 1].e - tmp[x + i - 1].s + 1);
    for(int i=1; i<=m; i++) dp[i][i] = len[i] - len[i-1], opt[i][i] = i;
    for(int i=1; i<m; i++){
        for(int j=1; j+i<=m; j++){
            int s = j, e = j + i;
            //for(int k=opt[s][e-1]; k<=opt[s+1][e]; k++){
            //for(int k=s; k<=e; k++){
              for(int k=s; k<=e; k+=e-s){
                int cur = dp[s][k-1] + dp[k+1][e] + len[e] - len[s-1];
                if(dp[s][e] <= cur){
                    dp[s][e] = cur;
                    opt[s][e] = k;
                }
            }
        }
    }
    return dp[1][m];
}

int main()
{
    int n, m, i;
    scanf("%d%d", &n, &m);
    for(i=1;i<=n;i++)
        scanf("%d", &arr[i]);
    
    for(i=1;i<=m;i++)
        tmp[arr[i]].s = 0;
    
    for(i=1;i<=n;i++)
    {
        if(!tmp[arr[i]].s)
            tmp[arr[i]].s = i;
        tmp[arr[i]].e = i;
    }
    
    for(i=1;i<=m;i++)
        assert(tmp[arr[i]].s);
    
    int sz = 1;    
    
    int l = 1;
    for(i=1;i<=n;i++)
    {
        if(tmp[arr[i]].s == i)
        {
            tmp[arr[i]].p = sta[sz-1];
            tmp[arr[i]].l = l;
            sta[sz++] = arr[i];
            l++;
        }
        
        if(tmp[arr[i]].e == i)
        {
            sz--;
            l--;
        }
    }
    
    sort(tmp + 1, tmp + m + 1);
    
    long long res = 0;
    int s = 1;
    for(int i=1;i<=m;i++)
    {
        if(i == m || tmp[i].l != tmp[i+1].l || tmp[i].e + 1 != tmp[i+1].s)
        {
            res += calc(s, i);
            s = i+1;
        }
    }
    
    printf("%lld\n", res);
    return 0;
}






