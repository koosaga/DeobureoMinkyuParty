#include<bits/stdc++.h>
using namespace std;
bool isPrime(long long x)
{
    for(long long i=2; i*i<=x; ++i)
    if(x%i==0) return false;
    return true;
}
int main()
{
    for(long long i=1e13;;++i)
    {
        if(isPrime(i))
        {
            printf("%lld\n", i);
            return 0;
        }
    }
}
