#include<bits/stdc++.h>
using namespace std;
long long nCk(long long n, long long k)
{
    __int128 ans = 1;
    for(int i=1; i<=k; ++i)
    {
        ans *= n-i+1;
        ans /= i;
    }
    return ans;
}#include<bits/stdc++.h>
bool nCkLTEQx(long long n, long long k, long long x)
{
    __int128 ans = 1;
    for(int i=1; i<=k; ++i)
    {
        ans *= n-i+1;
        ans /= i;
        if(ans>x) return false;
    }
    return true;
}

long long myquery(long long n, long long k)
{
    long long ans = 0;
    k--;
    if(n<62 && k>=(1LL<<n)) return -1LL;
    for(int pcnt=0; ;++pcnt)
    {
        if(nCkLTEQx(n, pcnt, k))
        {
            k -= nCk(n, pcnt);
        }
        else
        {
            //ans is in this pcnt
            long long phi = n;
            for(int i=pcnt-1; i>=0; --i)
            {
                long long lo = i; //LT
                long long hi = phi; // GTEQ
                while(lo+1!=hi)
                {
                    long long mi = (lo+hi)/2;
                    if(nCkLTEQ(mi, i, k)) lo = mi;
                    else hi = mi;
                }
                ans += pow(2, phi);
                phi = hi;
            }
        }
    }
    return ans;
}


