#include<bits/stdc++.h>
using namespace std;
using lint = int64_t;
namespace miller_rabin
{
    inline lint mul(lint a, lint b, lint p)
    {
        __int128 ab = (__int128)a*b;
        return ab%p;
    }
    lint ipow(lint x, lint y, lint p)
    {
        lint ret = 1, piv = x%p;
        while(y)
        {
            if(y&1) ret = mul(ret, piv, p);
            piv = mul(piv, piv, p);
            y >>= 1;
        }
        return ret;
    }
    bool miller_rabin(lint x, lint a)
    {
        if(x%a==0) return 0;
        lint d = x-1;
        while(true)
        {
            lint tmp = ipow(a, d, x);
            if(d&1) return (tmp != 1 && tmp != x-1);
            else if(tmp==x-1) return 0;
            d >>= 1;
        }
    }
    bool isprime(lint x)
    {
        for(auto &i: {2,3,5,7,11,13,17,19,23,29,31,37})
        {
            if(x==i) return 1;
            if(x>40 && miller_rabin(x, i)) return 0;
        }
        if(x<40) return 0;
        return 1;
    }
}

namespace pollard_rho
{
    lint f(lint x, lint n, lint c)
    {
        return (c+miller_rabin::mul(x, x, n))%n;
    }
    void rec(lint n, vector<lint> &v)
    {
        if(n==1) return;
        if(n%2==0)
        {
            v.push_back(2);
            rec(n/2, v);
            return;
        }
        if(miller_rabin::isprime(n))
        {
            v.push_back(n);
            return;
        }
        lint a, b, c;
        while(1)
        {
            a = rand()%(n-2)+2;
            b = a;
            c = rand()%20 + 1;
            do
            {
                a = f(a, n, c);
                b = f(f(b, n, c), n, c);
            }while(__gcd(abs(a-b), n) == 1);
            if(a!=b) break;
        }
        lint x = __gcd(abs(a-b), n);
        rec(x, v);
        rec(n/x, v);
    }
    vector<lint> factorize(lint n)
    {
        vector<lint> ret;
        rec(n, ret);
        sort(ret.begin(), ret.end());
        return ret;
    }
}

const long long MOD = 998244353;

long long arr[1010101];
long long rem[1010101];
long long sol[1010101];


long long primes[1010101];
int tp = 0;
void init()
{
    for(int i=1; i<=1000000; ++i)
    {
        if(i==2)
        {
            primes[tp++] = i;
            continue;
        }
        if(i==1 || i%2 == 0) continue;
        bool flag = true;
        for(int j=3; j*j <=i; ++j)
        {
            if(j%i==0)
            {
                flag = false;
                break;
            }
        }
        if(flag) primes[tp++] = i;
    }
    //for(int i=0;i<10; ++i) printf("%lld ", primes[i]);
}

void tmain()
{
    long long l, r, k;
    scanf("%lld%lld%lld",&l,&r,&k);
    
    for(int i=0; i<=r-l;++i)
    {
        arr[i] = 1; 
        rem[i] = i+l;
    }
    for(int _i=0; _i<tp; ++_i)
    {
        int i = primes[_i];
        int sti = (i-l%i)%i;
        for(int j=sti; j<=r-l; j += i)
        {
            int cnt = 0;
            while(rem[j] % i == 0)
            {
                rem[j] /= i;
                ++cnt;
            }
            if(cnt!=0)
            {
                arr[j] *= (cnt*k+1);
                arr[j] %= MOD;
            }
        }
    }
    long long ans = 0;
    for(int i=0; i<=r-l; ++i)
    {
        //printf("(%lld, %lld) ", rem[i], arr[i]);
        if(rem[i] != 1)
        {
            arr[i] *= (k+1);
            arr[i] %= MOD;
        }
        ans += arr[i];
        ans %= MOD;
    }
    printf("%lld\n", ans);
    return;
}
int main()
{
    init();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        tmain();
    }   
}

















