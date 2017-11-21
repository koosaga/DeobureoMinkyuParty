//UNSOLVED
#include<bits/stdc++.h>

using namespace std;

double arr[20];
bool edg[20][20];
double mem[1 << 20][20];

int main()
{
    int n, m, t, x, y, b, h, i;
    scanf("%d%d%d", &n, &m, &t);
    for(i=0;i<n;i++)
        scanf("%lf", &arr[i]);
    for(i=0;i<m;i++)
    {
        scanf("%d%d", &x, &y);
        x--;
        y--;
        edg[x][y] = edg[y][x] = 1;
    }
    
    for(i=0;i<n;i++)
        mem[(1<<n)-1][i] = 1.0;
    
    for(b=(1<<n)-2;b>=1;b--)
    {
        for(h=0;h<n;h++)
        {
            if(!(b&(1<<h)))
                continue;
            for(x=0;x<n;x++)
            {
                
            }
        }
    }
    
    
    return 0;
}
