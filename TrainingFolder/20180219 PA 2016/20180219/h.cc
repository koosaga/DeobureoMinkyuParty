#include<bits/stdc++.h>
using namespace std;
int Q;
vector<int> primes;
const int MAXN = 1000100;
bool isPrime[MAXN];
int primeLT[MAXN];
void Init()
{
    memset(isPrime, true, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;
    for(int i=2; i<MAXN; ++i)
    {
        if(!isPrime[i]) continue;
        for(int j=2*i; j<MAXN; j += i)
            isPrime[j] = false;
    }
    for(int i=1; i<MAXN; ++i)
    {
        primeLT[i] = primeLT[i-1];
        if(isPrime[i])
        {
            ++primeLT[i];
            primes.push_back(i);
        }
    }
    return;
}
const int BUCKET = 50;
long long Solve(int a, int b)
{
    //sum x(x-1)/2 where x = b/p - (a-1)/p 
    long long ans = 0;
    for(int bp = 2; bp<BUCKET; ++bp)
    {
        for(int amp = 0; amp<=bp-2; ++amp)
        {
            pair<int, int> range1
            = make_pair(b/(bp+1)+1, b/bp); //incl
            pair<int, int> range2 
            = make_pair((a-1)/(amp+1)+1, amp==0?MAXN:(a-1)/amp); //incl
            pair<int, int> range3 = make_pair(
            max(range1.first, range2.first), min(range1.second, range2.second));
            
            
            
            int nop = primeLT[range3.second] - primeLT[range3.first-1];
            //printf("%d %d %d %d %d\n", bp, amp, range3.first, range3.second, nop);
            if(range3.first > range3.second) continue;
            ans += 1LL * nop * (bp-amp)*(bp-amp-1)/2;
        }
    }
    for(int i=0;primes[i]<=b/BUCKET; ++i)
    {
        int x = b/primes[i] - (a-1)/primes[i];
        ans += 1LL*x*(x-1)/2;
    }
    return ans;
}
int main()
{
    Init();
    int t; scanf("%d", &t);
    while(t--)
    {
        int a, b; scanf("%d%d", &a, &b);
        printf("%lld\n", Solve(a, b));
        fflush(stdout);
    }
    return 0;
}











