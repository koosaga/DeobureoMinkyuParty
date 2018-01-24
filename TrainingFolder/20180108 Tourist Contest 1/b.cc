#include<bits/stdc++.h>
using namespace std;
#define prev fuck
#define next fuckyou
char s[202020];
int next[202020];
int prev[202020];
int N;
int main()
{
    freopen("bad.in", "r", stdin);
    freopen("bad.out", "w", stdout);
    int ans = 0;
    scanf("%s", s);
    N = strlen(s);
    for(int i=0; i<N; ++i)
        if(s[i] == '1') ans += 4;
    if(ans==0)
    {
        puts("0");
        return 0;
    }
    int np = N;
    for(int i=N-1; i>=0; --i)
    {
        if(s[i] == '1')
        {
            next[i] = np;
            np = i;
        }
    }
    int pp = -1;
    for(int i=0; i<N; ++i)
    {
        if(s[i] == '1')
        {
            prev[i] = pp;
            pp = i;
        }
    }
    int minv = 7*(N-np);
    for(int i=0; i<N; ++i)
    {
        int l = 0;
        if(s[i] == '1')
        {
            if(next[i] == N)
                l = 7*i;
            else
                l = 14*i + 7*(N-next[i]);

            if(prev[i] == -1)
                l = min(l, 7 * (N-i));
            else
                l = min(l, 14 * (N-i)+ 7 * prev[i]);
            minv = min(minv, l);
        }
    }    
    printf("%d\n", ans+minv);
    return 0;
}   






