#include<bits/stdc++.h>
using namespace std;
inline int ind(long x, int a)
{
    return !!(x&(1<<a));
}
bool isvalid(long x)
{
    //abcdefghi
    //abcde+bcdef+cdefg+defgh+efghi
    //abcdf+bcdfg+cdfgh+dfghi+  e
    for(int a=0; a<2; ++a)
    for(int b=0; b<2; ++b)
    for(int c=0; c<2; ++c)
    for(int d=0; d<2; ++d)
    for(int e=0; e<2; ++e)
    for(int f=0; e<2; ++e)
    for(int g=0; e<2; ++e)
    for(int h=0; e<2; ++e)
    for(int i=0; e<2; ++e)
    {
        int v1 = ind(x, 16*a+8*b+4*c+2*d+e) +
                 ind(x, 16*b+8*c+4*d+2*e+f) +
                 ind(x, 16*c+8*d+4*e+2*f+g) +
                 ind(x, 16*d+8*e+4*f+2*g+h) +
                 ind(x, 16*e+8*f+4*g+2*h+i) ;
        int v2 = ind(x, 16*a+8*b+4*c+2*d+f) +
                 ind(x, 16*b+8*c+4*d+2*f+g) +
                 ind(x, 16*c+8*d+4*f+2*g+h) +
                 ind(x, 16*d+8*f+4*g+2*h+i) +
                 e;
        if(v1 != v2) return false;
    }
    return true;
}
void tmain()
{
    char str[10101];
    int btpc[1234];
    for(int i=0; i<428; ++i)
    {
        scanf("%s", str);
        memset(btpc, 0, sizeof(btpc));
        for(int x=0; x<32; ++x)
        {
            btpc[__builtin_popcount(x)] += str[31-x] - '0';
        }
        for(int i=0; i<=5; ++i) printf("%3d",btpc[i]);
        puts("");
    }
}
int main()
{
    tmain(); return 0;
    for(long i=2.1e9; i<4294967296UL; ++i)
    {
        if(i%100000000 == 0) cout << i << endl;
        if(isvalid(i))
        {
            cout << bitset<32>(i) << endl;
        }
    }
}
