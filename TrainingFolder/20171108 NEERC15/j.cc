#include<bits/stdc++.h>
using namespace std;

int N;
char a[1010];
char b[1010];
mt19937 gen;
bool getAns(bool y = true)
{
    if(y) printf("%s\n", a);
    else printf("%s\n", b);
    fflush(stdout);
    int x; 
    scanf("%d", &x);
    if(x==N)
        exit(0);
    
    return x == N/2;
}

void phase1()
{
    for(int x=0; x<498; ++x)
    {
        for(int i=0; i<N; ++i)
            a[i] = '0'+(gen()&1);
        if(getAns()) return;
    }
    while(true);
}
void phase2()
{
    b[0] = a[0];
    for(int i=1; i<N; ++i)
    {
        a[0] ^= 1; a[i] ^= 1;
        if(getAns()) b[i] = a[i];
        else b[i] = a[i] ^ 1;
        a[0] ^= 1; a[i] ^= 1;
    }
    getAns(false);
    for(int i=0; i<N; ++i) b[i] ^= 1;
    getAns(false);
    while(true);
}
void solve()
{
    phase1();
    phase2();
}

int main()
{
    gen.seed(0x94949);
    scanf("%d", &N);
    a[N] = 0;
    b[N] = 0;
    solve();
}
