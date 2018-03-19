#include<bits/stdc++.h>
using namespace std;
const int ITER = 10;
const int MAXN = 300;
const int MOD = 1e9+7;
int mat[ITER][MAXN][MAXN];
int matT[ITER][MAXN][MAXN];
__int128 tmp[MAXN][MAXN];
int res[MAXN][MAXN];
int res2[MAXN][MAXN];
int now[MAXN][MAXN];
int N;
bool ze(int a[MAXN][MAXN])
{
    for(int i=0; i<MAXN; ++i)
        for(int j=0; j<MAXN; ++j)
            if(a[i][j])
            {
                return false;
            }
    return true;
}
void mult(int a[MAXN][MAXN], int b[MAXN][MAXN], int c[MAXN][MAXN], int d[MAXN][MAXN])
{
    memset(tmp, 0, sizeof(tmp));
    for(int i=0; i<MAXN; ++i)
        for(int j=0; j<MAXN; ++j)
            for(int k=0; k<MAXN; ++k)
            {
                tmp[i][j] = tmp[i][j] + 1LL*a[i][k]*b[j][k];
            }
    for(int i=0; i<MAXN; ++i)
        for(int j=0; j<MAXN; ++j)
        {
            d[j][i] = c[i][j] = tmp[i][j]%MOD;
        }
}
int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i)
        for(int j=0; j<N; ++j)
        {
            int t; scanf("%d", &t);
            now[i][j] = mat[0][i][j] = matT[0][j][i] = t;
        } 
    if(ze(now))
    {
        puts("1");
        return 0;
    }
    for(int i=0; i<ITER-1; ++i)
    {
        mult(mat[i], matT[i], mat[i+1], matT[i+1]);
        if(ze(mat[i+1])) break;
    }
    if(!ze(mat[ITER-1]))
    {
        puts("Infinity");
        return 0;
    }
    long long int ansv = 1;
    for(int i=ITER-1; i>=0; --i)
    {
        if(ze(matT[i])) continue;
        mult(now, matT[i], res, res2);
        if(!ze(res))
        {
            ansv += (1ll<<i);
            for(int i=0; i<MAXN; ++i)
                for(int j=0; j<MAXN; ++j)
                    now[i][j] = res[i][j];
        }
    }
    printf("%lld\n", ansv+1);
}






