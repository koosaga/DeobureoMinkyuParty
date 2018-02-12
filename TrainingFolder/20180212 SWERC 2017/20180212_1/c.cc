#include<bits/stdc++.h>
using namespace std;
const int MAXN = 136;


struct mat
{
    int a[MAXN][MAXN];
};

const int MOD = 1e9;
mat mul(const mat& a, const mat& b)
{
    mat x; memset(&x, 0, sizeof(mat));
    for(int k=0; k<MAXN; ++k)
        for(int i=0; i<MAXN; ++i)
            for(int j=0; j<MAXN; ++j)
                x.a[i][j] = (x.a[i][j] + 1LL*a.a[i][k]*b.a[k][j])%MOD;
    return x;
}
mat I()
{
    mat x;memset(&x, 0, sizeof(mat));
    for(int i=0; i<MAXN; ++i)
        x.a[i][i] = 1;
    return x;
}
mat mpow(mat a, long long b)
{
    mat ans = I();
    while(b)
    {
        if(b&1) ans = mul(ans, a);
        a = mul(a, a);
        b /= 2;
    }
    return ans;
}

vector<int> revs;
int revers[256];

int N;
int getInd(int a)
{
    a = min(a, revers[a]);
    return lower_bound(revs.begin(), revs.end(), a) - revs.begin();
}
void init()
{
    for(int i=0; i<(1<<N); ++i)
    {
        int cpi = i;
        int xx = 0;
        for(int i=0; i<N; ++i)
        {
            xx *= 2;
            xx += (cpi&1);
            cpi /= 2;
        }
        revers[i] = xx;
        revs.push_back(min(i, revers[i]));
    }
    sort(revs.begin(), revs.end());
    revs.resize(unique(revs.begin(), revs.end())-revs.begin());
}
void trans(int x, vector<int>& V, int bp = 0)
{
    for(int i=0; i<N; ++i)
    {
        if((x&(1<<i)) == 0)
        {
            trans(x|(1<<i), V, bp);
            trans(x|(1<<i), V, bp|(1<<i));
        }
        if((x&(1<<i))==0 && i+1<N && (x&(1<<(i+1)))==0)
        {
            trans(x|(1<<i)|(1<<(i+1)), V, bp);
        }
        if((x&(1<<i)) == 0) return;
    }
    if(x==((1<<N)-1)) V.push_back(bp);
}


mat getman()
{
    mat x; memset(&x, 0, sizeof(mat));
    for(int i=0; i<(1<<N); ++i)
    {
        vector<int> V;
        trans(i, V);
        for(int a: V)
        {
            x.a[ getInd(i)][ getInd(a)] = (x.a[ getInd(i)][ getInd(a)]+1)%MOD;
        }
    }
    for(int i=0; i<(1<<N); ++i)
        for(int j=0; j<(1<<N); ++j)
        {
            if(i > revers[i] && j>=revers[j])
            {
                x.a[ getInd(i)][ getInd(j)] /= 2;
            }
        }
    return x;
}

int main()
{
    long long M;
    scanf("%d%lld", &N, &M);
    init();
    mat gen = getman();
    mat p = mpow(gen, M);
    
    printf("%d\n", p.a[0][0]);
    return 0;
}









/*

  2  1  1  1
  1  0  1  0
  1  1  0  0
  1  0  0  0
 71 32 32 22
 32 15 14 10
 32 14 15 10
 22 10 10  7

*/








