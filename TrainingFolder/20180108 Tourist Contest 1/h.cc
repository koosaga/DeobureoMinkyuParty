#include <bits/stdc++.h>
using namespace std;

int on[100010];
int off[100010];
vector<int> sor;

int main()
{
    freopen("hop.in", "r", stdin);
    freopen("hop.out", "w", stdout);
    int n, x, s, g, m, i;
    scanf("%d%d", &n, &x);
    for(i=0;i<n;i++)
        scanf("%d", &on[i]);
    for(i=0;i<n;i++)
        scanf("%d", &off[i]);
    
    if(x == n)
    {
        printf("%d", n);
        return 0;
    }
    
    for(i=1;i<n;i++)
        sor.push_back(on[i]);
    
    sort(sor.rbegin(), sor.rend());
    
    m = 0;
    int mine = on[0] + off[m];
    bool ok = 0;
    for(i=0;i<x;i++)
    {
        if(i < m)
        {
            if(sor[x-i-1] + off[i] <= mine)
            {
                ok = 1;
                break;
            }
        }
        else
        {
            if(sor[x-i-1] + off[i+1] <= mine)
            {
                ok = 1;
                break;
            }
        }
    }
    
    if(!ok)
    {
        printf("-1");
        return 0;
    }
    
    s = 0;
    g = n - 1;
    while(s < g)
    {
        m = (s+g+1) / 2;
        int mine = on[0] + off[m];
        //printf("m = %d, mine = %d\n", m, mine);
        bool ok = 0;
        for(i=0;i<x;i++)
        {
            if(i < m)
            {
            //printf("%d %d\n", sor[x-i-1], off[i]);
                if(sor[x-i-1] + off[i] <= mine)
                {
                    ok = 1;
                    break;
                }
            }
            else
            {
            //printf("> %d %d\n", sor[x-i-1], off[i+1]);
                if(sor[x-i-1] + off[i+1] <= mine)
                {
                    ok = 1;
                    break;
                }
            }
        }
        if(ok)
            s = m;
        else
            g = m - 1;
    }
    printf("%d", s + 1);
    return 0;
}
