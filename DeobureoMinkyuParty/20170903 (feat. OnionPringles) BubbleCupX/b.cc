#include<bits/stdc++.h>
using namespace std;
int N, L, M;
int s[1010010];
int e[1010010];
int x[1010010];
const int MAXN = 101;
struct mat
{
    long long int arr[MAXN][MAXN];  
};
mat mul(const mat& a, const mat& b)
{
    mat c; memset(&c, 0, sizeof(c));
    for(int k=0; k<MAXN; ++k)
        for(int i=0; i<MAXN; ++i)
            for(int j=0; j<MAXN; ++j)
            {
                c.arr[i][j] += a.arr[i][k]*b.arr[k][j];
                c.arr[i][j] %= ((int)1e9+7);
            }
    return c;
}
mat I()
{
    mat c; memset(&c, 0, sizeof(c));
    for(int i=0; i<MAXN; ++i) c.arr[i][i] = 1;
    return c;
}
mat pow(const mat& a, int x)
{
    if(x==0) return I();
    if(x==1) return a;
    mat c = pow(a, x/2);
    c = mul(c, c);
    if(x%2==1) c = mul(c, a);
    return c;
}
int sacc[101];
int eacc[101];
int xacc[101];
int main()
{
    scanf("%d%d%d", &N, &L, &M);
    for(int i=0; i<N; ++i) scanf("%d", s+i);
    for(int i=0; i<N; ++i) scanf("%d", e+i);
    for(int i=0; i<N; ++i) scanf("%d", x+i);
    L-=2;
    for(int i=0; i<N; ++i) x[i] += e[i];
    for(int i=0; i<N; ++i)
    {
        sacc[s[i]%M]++;
        eacc[e[i]%M]++;
        xacc[x[i]%M]++;
    }
    mat b, p, f;
    memset(&b, 0, sizeof(b));
    memset(&p, 0, sizeof(p));
    memset(&f, 0, sizeof(f));
    for(int i=0; i<M; ++i)
    {
        for(int j=0; j<M; ++j)
        {
            b.arr[j][(i+j)%M] += sacc[i];
            p.arr[j][(i+j)%M] += eacc[i];
            f.arr[j][(i+j)%M] += xacc[i];
        }
    }
    mat fin = mul(f, mul(pow(p, L), b));
    printf("%lld\n",fin.arr[0][0] %((int)1e9+7));
}














