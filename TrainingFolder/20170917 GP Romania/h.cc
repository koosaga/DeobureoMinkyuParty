#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;
const int MAXN = 70707;

int digit[10];
long long K;


const long long MOD2 = 10000000000037LL;
double factd[70707];
long long fact[70707];
long long facti[70707];
long long logs[70707];
long long inv[70707];

long long pow(long long int a, long long int b, long long int p)
{
    if(b==0) return 1%p;
    if(b==1) return a%p;
    __int128 ans = pow(a, b/2, p);
    ans *= ans; ans %= p;
    if(b&1) ans = (ans*a)%p;
    return (long long)ans;
}
void init()
{
    for(int i=1; i<MAXN; ++i) 
    {
        logs[i] = log(i)/log(10);
        factd[i] = factd[i-1] + logs[i];
    }
    fact[0] = facti[0] = 1;
    for(int i=1; i<MAXN; ++i)
        fact[i] = fact[i-1] * i % MOD2;
    facti[MAXN-1] = pow(fact[MAXN-1], MOD2-2, MOD2);
    for(int i=MAXN-2; i>=1; --i)
        facti[i] = facti[i+1] * (i+1) % MOD2;
    for(int i=1; i<MAXN; ++i)
        inv[i] = (__int128)facti[i]*fact[i-1]%MOD2;
//    puts("Init End
}
int gN = 0;
double gans = 0.0;
__int128 gans1 = 0;
long long solve()
{
    if(gans>12.5) return (long long)1e15;
    return gans1;
    /*
    int N = 0; for(int i=0; i<10; ++i) N += digit[i];
    
    //over 1e15
    double ans = factd[N]; for(int i=0; i<10; ++i) ans -= factd[digit[i]];
    if(ans > 12.5) return (long long)(1e15);
    
    __int128 ans1 = fact[N];
    for(int i=0; i<10; ++i)
    {
        ans1 = (ans1*facti[digit[i]])%MOD2;
    }
    return ans1;
    */
    
}
int tmain()
{
    int N = 0;
    gN = 0;
    gans1 = 1;
    gans = 0.0;
    
    for(int i=0; i<10; ++i)
    {
        scanf("%d", digit+i);
        N += digit[i];
        gans -= factd[digit[i]];
        gans1 = (gans1*facti[digit[i]])%MOD2;
    }
    
    scanf("%lld", &K);
    
    //start here
    gN = N;
    gans += factd[N];
    gans1 = (gans1*fact[N])%MOD2;
    
    
    int no = 0;
    for(int i=0; i<N; ++i)
    {
        for(int k=0; k<10; ++k)
            if(digit[k])
            {
                double pgans = gans;
                __int128 pgans1 = gans1;
                gans -= logs[gN];
                gans += logs[digit[k]];
                gans1 = (gans1*digit[k]);
                gans1 = (gans1*inv[gN])%MOD2;
                digit[k]--;
                gN--;
                
                
                long long v = solve();
                if(K>v)
                {
                    K -= v;
                    ++digit[k];
                    ++gN;
                    gans = pgans;
                    gans1 = pgans1;
                }
                else
                {
                    no = (1LL*no*10 + k)%MOD;
                    break;
                }
            }
    }
    return no;
}

int main()
{
    init();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        printf("%d\n", tmain());
    }
}   
