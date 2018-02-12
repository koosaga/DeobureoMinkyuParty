#include<bits/stdc++.h>
using namespace std;
char str[1010101];
int N;
int cnt[26];
int nonzero = 0;
void update(char x, int a)
{
    if(x == '*') return;
    if(cnt[x-'A'] != 0) nonzero--;
    cnt[x-'A'] += a;
    if(cnt[x-'A'] != 0) nonzero++;
}
bool can(int x) // propagate +-x;
{
    memset(cnt, 0, sizeof(cnt));
    nonzero = 0;
    for(int i=0; i<x; ++i)
        update(str[i], 1);
    if(nonzero > 1) return false;
    for(int i=x; i<N; ++i)
    {
        update(str[i-x], -1);
        update(str[i], 1);
        if(nonzero > 1) return false;
    }
    return true;
    
}
int main()
{
    scanf("%s", str);
    N = strlen(str);
    int lo = 0; //cant
    int hi = N; //can
    while(lo+1!=hi)
    {
        int mi = (lo+hi)/2;
        if(can(N+1-mi)) hi = mi;
        else lo = mi;
    }
    printf("%d\n", hi);
}
