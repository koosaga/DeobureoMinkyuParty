#include <bits/stdc++.h>
using namespace std;

int arr[100010];
long long sum[100010];
int place[101010][50];
static char buf[1<<19];
static int idx = 0;
static int bytes = 0;
static inline int _read()
{
    if(!bytes || idx == bytes)
    {
        bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
        idx = 0;
    }
    return buf[idx++];
}
static inline int _readInt()
{
    int x = 0, s = 1;
    int c = _read();
    while(c<=32) c= _read();
    while(c>32) x = 10*x+(c-'0'), c = _read();
    return x;
}
inline void addsum(long long& res, long long mult, long long i, long long from, long long to)
{
    res += mult*((to-from)*i+to*(to-1)/2 - from*(from-1)/2 );
}
void solve()
{
    int n, i, j;
    n = _readInt();
    //assert(1==scanf("%d", &n));
    for(i=1;i<=n;i++)
        arr[i] = _readInt();
        //assert(1==scanf("%d", &arr[i]));
    
    for(i=1;i<=n;i++)
        sum[i] = sum[i-1] + arr[i];
    
    long long res = 0;
    for(j=0; j<=40; j++)
    {
        if(sum[n] < (1LL << j))
            break;
        int p = 0;
        for(int i=1; i<=n; ++i)
        {
            while(p<=n && (sum[p]-sum[i-1] < (1LL<<j)) ) ++p;
            place[i][j] = p;
        }
    }
    int herej= j;
    for(int i=1; i<=n; ++i)
    {
        place[i][herej] = n+1;
        for(int j=0; j<herej; ++j)
        {
            if(j==0) addsum(res, j+1, i, i, place[i][j+1]);
            else addsum(res, j+1, i, place[i][j], place[i][j+1]);
        }
    }
    printf("%lld\n", res);
}

int main()
{
    int t, i;
    t = _readInt();
    //assert(1==scanf("%d", &t));
    for(i=0;i<t;i++)
        solve();
    return 0;
}
