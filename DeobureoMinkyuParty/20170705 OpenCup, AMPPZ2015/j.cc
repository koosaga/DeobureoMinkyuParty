#include<bits/stdc++.h>
using namespace std;
int N, M, T;
int kyori[20][20];
double p[20];
double dp[1048576][20];
double remp[1048576];
void updateadj(int ind)
{
    for(int i=0; i<N; ++i)
        if(ind & (1<<i))
        {
            for(int j=0; j<N; ++j)
            {
                if(ind & (1<<j)) //old
                {
                    dp[ind][i] = min(dp[ind][i], kyori[i][j] + dp[ind][j]);
                }
                else    //new
                    dp[ind][i] = min(
                        dp[ind][i],
                        
                        kyori[i][j] + 
                        (remp[ind]-p[j])/remp[ind]*(dp[ind|(1<<j)][j])
                    );  
            }

        }
}

void updatejump(int ind)
{
    double ave = 0;
    double lo = 0;
    double hi = T*30;
    for(int cnt=0; cnt<23; ++cnt)
    {
        
        double mi = (lo+hi)/2;
        for(int i=0; i<N; ++i)
            dp[ind][i] = mi;
        
        updateadj(ind);
        double ave = 0;
        for(int i=0; i<N; ++i)
        {
            if(ind & (1<<i))
                ave += dp[ind][i];
            else
                ave += (remp[ind]-p[i])/remp[ind]*(dp[ind|(1<<i)][i]);
        }
        ave = (ave/N)+T;
        if(ave<mi) hi = mi;
        else lo = mi;
    }
    updateadj(ind);
}

int main()
{
    scanf("%d%d%d", &N, &M, &T);
    for(int i=0; i<N; ++i)
        scanf("%lf", p+i);
    
    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
            kyori[i][j] = kyori[j][i] = 1e9;
        kyori[i][i] = 0;
    }   
    for(int i=0; i<M; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b); --a; --b;
        kyori[a][b] = kyori[b][a] = 1;
    }
    for(int k=0; k<N; ++k) for(int i=0; i<N; ++i) for(int j=0; j<N; ++j)
    {
        if(kyori[i][k] +kyori[k][j] < kyori[i][j])
            kyori[i][j] = kyori[i][k] + kyori[k][j];
    }
    //explicit 1<<N as 0
    for(int i=(1<<N)-3; i>=1; i-=2)
    {
        for(int j=0; j<N; ++j)
        {
            dp[i][j] = 1e5;
            if(!(i & (1<<j)))
                remp[i] += p[j];
        }
        if(remp[i]==0) continue;
        updatejump(i);
    }
    printf("%.12f\n", dp[1][0]);   
}
