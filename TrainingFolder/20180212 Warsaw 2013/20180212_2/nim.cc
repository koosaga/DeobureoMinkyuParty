#include<bits/stdc++.h>

using namespace std;

char fuck[][20] = {"000", "001", "010", "011", "100", "101", "110", "111"};

const int MAX_N = 8;
int ans[MAX_N + 1][MAX_N + 1][MAX_N + 1][MAX_N + 1][MAX_N + 1][MAX_N + 1];

map<vector<int>, int> M;
int solve(int i, int j, int k, int s, int t, int r)
{
    vector<int> an = {i, j, k, s, t, r};
    sort(an.begin(), an.end());
    i = an[0]; j = an[1]; k = an[2]; s = an[3]; t = an[4]; r = an[5];
    if(!ans[i][j][k][s][t][r])
    {
        vector<int> qq;
        int cnt = 1;
        for(int x=1; x<6; ++x)
        {
            if(an[x] == an[x-1]) ++cnt;
            else
            {
                qq.push_back(cnt);
                cnt = 1;
            }
        }
        qq.push_back(cnt);
        
        int a = 3, x;
        for(x = 1; x <= i; x++)
            a = min(a, 1+solve(i-x, j, k, s, t, r)%3);
        for(x = 1; x <= j; x++)
            a = min(a, 1+solve(i, j-x, k, s, t, r)%3);
        for(x = 1; x <= k; x++)
            a = min(a, 1+solve(i, j, k-x, s, t, r)%3);
        for(x = 1; x <= s; x++)
            a = min(a, 1+solve(i, j, k, s-x, t, r)%3);
        for(x = 1; x <= t; x++)
            a = min(a, 1+solve(i, j, k, s, t-x, r)%3);
        for(x = 1; x <= r; x++)
            a = min(a, 1+solve(i, j, k, s, t, r-x)%3);

        ans[i][j][k][s][t][r] = a;
    }
    return ans[i][j][k][s][t][r];
}

int main()
{
    int i, j, k,s,t,r;
    
    for(i = 0; i<MAX_N ; i++)
    for(j = i; j >= 0; j--)
    for(k = j; k >= 0; k--)
    for(s = k; s >= 0; s--)
    for(t = s; t >= 0; t--)
    for(r = t; r >= 0; r--)
    {
        int v = solve(i, j, k,s,t,r);
        if(i==j && j==k&&k!=0 || j==k&& k==s&&s!=0 || k==s&&s==t&&t!=0 ||s==t&&t==r) continue;
        
        if(v%3==0)
        {
            assert((i+j+k+s+t+r)%3==0);
            assert((i+j+k+s+t+r) != 3);
            assert((i+j+k+s+t+r) != 6);
            assert((i+j+k+s+t+r) != 12);
        }
        if(v==3 ) printf("%s %s %s %s %s %s %3d-> %d\n", fuck[i], fuck[j], fuck[k], fuck[s], fuck[t], fuck[r], (i+j+k+s+t+r), v);
    }
    
    return 0;
}
