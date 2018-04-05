#include <bits/stdc++.h>
using namespace std;

bool chk[100010];
int a[100010];
int b[100010];
int s = 0;

int main()
{
    int n, m, i;
    scanf("%d%d", &n, &m);
    for(i=0;i<m;i++)
        scanf("%d", &a[i]);
    
    for(i=0;i<m;i++)
        chk[a[i]] = 1;
    
    for(i=1;i<=n;i++)
        if(!chk[i])
            b[s++] = i;
    
    int p, q;
    p = q = 0;
    while(p < m || q < s)
    {
        if(q == s || p != m && a[p] < b[q])
        {
            printf("%d\n", a[p]);
            p++;
        }
        else
        {
            printf("%d\n", b[q]);
            q++;
        }
    }
    
    return 0;
}
