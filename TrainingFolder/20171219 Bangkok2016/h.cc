#include<bits/stdc++.h>
using namespace std;

int ene[8];
int poi[8];
int mem[256][82][100];

void upd(int &x, int v)
{
    x = max(x, v);
}

void process()
{
    int r, e, m, n, i, j, k, l;
    scanf("%d%d%d", &e, &m, &n);
    for(i=0;i<n;i++)
        scanf("%d", &ene[i]);
    for(i=0;i<n;i++)
        scanf("%d", &poi[i]);
    
    memset(mem, 0, sizeof mem);
    
    mem[0][0][0] = 100;
    
    r = 0;
    for(i=0;i<(1<<n);i++)
    {
        for(j=0;j<=81;j++)
        {
            for(k=0;k<100;k++)
            {
                if(mem[i][j][k])
                    r = max(r, j);
                
                if(mem[i][j][k] <= e)
                    continue;
                
                upd(mem[i][j+1][max(k-m, 0)], mem[i][j][k] - e);
                for(l=0;l<n;l++)
                {
                    if(i & (1<<l))
                        continue;
                    if(max(k-m, 0) + poi[l] >= 100)
                        continue;
                    upd(mem[i | (1<<l)][j+1][max(k-m, 0) + poi[l]], min(mem[i][j][k] - e + ene[l], 100));
                }
            }
        }
    }
    
    printf("%d\n", r);
}

int main()
{
    int t, i;
    scanf("%d", &t);
    for(i=1;i<=t;i++)
        process();
    return 0;
}
