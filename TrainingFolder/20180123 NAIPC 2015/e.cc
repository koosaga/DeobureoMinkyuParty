#include<bits/stdc++.h>
using namespace std;
const int MAXN = 32768;
const int MAXK = 1e6+10;
int minprime[MAXK+1];
int N, K;
int A[MAXN];

bool can(int v)
{
    int partition = 1;
    int gcd = A[0];
    for(int i=1; i<N; ++i)
    {
        gcd = __gcd(gcd, A[i]);
        if(minprime[gcd] < v)
        {
            partition++;
            gcd = A[i];
        }
    }
    return partition <= K;
}
int main()
{
    for(int i=2; i<MAXK; ++i)
    {
        if(minprime[i] != 0)
            continue;
        for(int j=i; j<MAXK; j += i)
            minprime[j] = i;
    }
    scanf("%d%d", &N, &K);
    for(int i=0; i<N; ++i)
        scanf("%d", A+i);
    int lo = 0; //can 
    int hi = *min_element(A, A+N)+1; //can't
    while(lo+1 != hi)
    {
        int mi = (lo+hi)/2;
        if(can(mi)) lo = mi;
        else hi = mi;
    }
    printf("%d\n", lo);
    return 0;
}
