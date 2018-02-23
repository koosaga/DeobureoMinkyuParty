#include<bits/stdc++.h>
using namespace std;




using real_t =  __float128;

real_t mypow(real_t x, long N)
{
    if(N==0) return 1;
    real_t res = mypow(x, N/2);
    if(N%2==1) return res*res*x;
    return res*res;
}
real_t solve(vector<long> E)
{
    long N = E.size();
    if(N==1) return E[0];
    vector<real_t> p;
    for(long i=0; i<N; ++i)
        p.push_back(pow(E[i], -1.0L/(N-1)));
    real_t sum = 0;
    for(long i=0; i<N; ++i)
        sum += p[i];
    sum /= (N-1);
    for(long i=0; i<N; ++i)
        p[i] /= sum;
    real_t ans = 0, ans2=0, ans3 = 0;
    for(long i=0; i<N; ++i)
    {
        ans += E[i] * mypow(p[i], N);
        ans2 += E[i];
    }
    return (ans2-ans) / N;
}
int main()
{
    long N;
    cin >> N;
    vector<long> A(N);
    for(long& x: A) cin >> x;
    printf("%.16Lf\n", (long double)solve(A) - 5e-8);
}
