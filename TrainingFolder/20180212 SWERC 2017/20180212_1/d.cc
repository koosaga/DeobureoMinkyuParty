#include<bits/stdc++.h>
using namespace std;
string str;
long long C[52][52];
int N, L;
string child[402];
int cost[402];

long long dp[52][52];
long long calc(string s, int left, int right) // [left, right]
{
    int N = s.size();
    //cout <<right << " " << left << " " << N << endl;
    if(right-left+1 < N ) return -(long long)(1e18);
    memset(dp, 0xdf, sizeof(dp));
    dp[0][left] = 0; // string index, calc, cost
    for(int i=1; i<=N; ++i)
        for(int j=left+1; j<=right+1; ++j)
        {
            if(s[i-1] == str[j-1])
            {
                for(int k=left; k<j; ++k)
                {
                    if((k == left && i==1) || (i!=1 && k!=left && s[i-2] == str[k-1]))
                    {
                        if(k == j-1) dp[i][j] = max(dp[i][j], dp[i-1][k]);
                        else dp[i][j] = max(dp[i][j], dp[i-1][k] + C[k][j-2]);
                    }
                }
            }
            //cout << i << ","<< j << ":"  <<dp[i][j] << endl;
        }
    return dp[N][right+1];
}
int main()
{
    cin >> str;
    cin >> L;
    L *=2;
    int N = str.length();
    for(int i(0); i<L; i += 2)
    {
        cin >> child[i] >> cost[i];
        child[i+1] = string(child[i].rbegin(), child[i].rend());
        cost[i+1] = cost[i];
    }
    memset(C, 0xdf, sizeof(C)); 
    for(int x=1; x<=N; ++x)
    {
        for(int i=0; i<=N-x; ++i)
        {
            int j = i+x-1;
            for(int k=0; k<L; ++k)
                C[i][j] = max(C[i][j], calc(child[k], i, j)+ cost[k]);
            //string d(str.begin()+i, str.begin() + j + 1);
            //if(C[i][j] > 0) cout << d << " " << C[i][j] << endl;
        }
    }
    long long DP[52];
    memset(DP, 0, sizeof(DP));
    for(int i=1; i<=N; ++i)
    {
        DP[i] = DP[i-1];
        for(int j=0; j<i; ++j)
            DP[i] = max(DP[i], DP[j]+C[j][i-1]);
    }
    printf("%lld\n", DP[N]);
    return 0;    
}
