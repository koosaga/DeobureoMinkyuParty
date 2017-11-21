#include<bits/stdc++.h>
using namespace std;
int N, M, A, Q;
int paq;

int phi(int A, int Q)
{
    int aa = 1;
    for(int i=1; ; ++i)
    {
        aa = 1LL*aa*A%Q;
        if(aa==1) return i;
    }
}

int pow(int a, int b, int m)
{
    if(b==0) return 1;
    int ans = pow(a, b/2, m);
    ans = (1LL*ans*ans)%m;
    if(b%2==1) ans = (1LL*ans*a)%m;
    return ans;
}


int main()
{
    scanf("%d%d%d%d", &N, &M, &A, &Q);
    paq = phi(A, Q);
    vector<int> fuck;
    long long int comb = 1;
    int a = 0;
    for(int i=0; i<N; ++i)
    {
        a += comb;
        a %= paq;
        fuck.push_back(a);
        comb *= (1LL*(M-i)*pow(i+1, paq-2, paq))%paq;
        comb %= paq;
    }
    for(int i=N-1; i>=0; --i)
    {
        printf("%d ", pow(A, fuck[i], Q));
    }    
    puts("");
    return 0;
}
