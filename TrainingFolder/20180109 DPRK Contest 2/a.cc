#include<bits/stdc++.h>
using namespace std;
int T;
int dx[4] = {-1, -1, 1, 1};
int dy[4] = {-1, 0, 0, 1};
int a[6][6];
int b[6][6];
bool valid(int x, int y)
{
    return !(x<0 || x>=6 || y<0 || y>x);
}
unordered_set<long long> AS[11];
unordered_set<long long> BS[11];
long long serialize(int arr[6][6])
{
    long long ans = 0;
    for(int i=0; i<6; i++)
        for(int j=0; j<=i; j++)
            ans = (ans<<3)+arr[i][j];
    return ans;
}
void solve(int arr[6][6], unordered_set<long long> S[11], int x, int y, int t, int pd)
{
    if(t>10) return;
    S[t].insert(serialize(arr));
    for(int d=0; d<4; ++d)
    {
        if(d+pd == 3) continue;
        if(!valid(x+dx[d], y+dy[d])) continue;
        swap(arr[x][y],arr[x+dx[d]][y+dy[d]]);
        solve(arr, S, x+dx[d], y+dy[d], t+1, d);
        swap(arr[x][y],arr[x+dx[d]][y+dy[d]]);
    }
    return;
}
int tmain()
{
    for(int i=0; i<=10; ++i)
    {
        AS[i].clear(); BS[i].clear();
    }    
    for(int i=0; i<6; ++i)
        for(int j=0; j<=i; ++j)
        {
            a[i][j] = i;
        }
    solve(a, AS, 0, 0, 0, -1);
    int ni, nj;
    for(int i=0; i<6; ++i)
        for(int j=0; j<=i; ++j)
        {
            scanf("%d", &b[i][j]);
            if(!b[i][j]) tie(ni, nj) = tie(i, j);
        }
    solve(b, BS, ni, nj, 0, -1);
   
    for(int i=0; i<=20; ++i)
    {
        for(int j=0; j<=10; ++j)
        {
            int k = i-j; if(k<0 || k>10) continue;
            for(auto x: AS[j])
                if(BS[k].find(x) != BS[k].end())
                    return i;
        }
    }
    return -1;
}
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        int v = tmain();
        if(v==-1) puts("too difficult");
        else printf("%d\n", v); 
    }
    return 0;
}
