#include <bits/stdc++.h>
using namespace std;

bool chk[1010];

int main()
{
    int n, m, i, j;
    scanf("%d%d", &n, &m);
    for(i=0;i<m;i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        for(j=x;j<y;j++)
            chk[j] = 1;
    }
    
    int r = n + 1;
    for(i=1;i<n;i++)
        if(chk[i])
            r += 2;
    printf("%d\n", r);
    return 0;
}
