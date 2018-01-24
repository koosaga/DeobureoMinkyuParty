#include <bits/stdc++.h>
using namespace std;

int arr[2010][2010];
bool chk[2010];

void process()
{
    int n, i, j;
    scanf("%d", &n);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            scanf("%d", &arr[i][j]);
    
    memset(chk, 0, sizeof chk);
    
    chk[1] = 1;
    int p = 2;
    for(i=0;i<n-1;i++)
    {
        while(chk[arr[1][p]])
            p++;
        
        int x = arr[1][p];
        
        for(j=2;j<=n;j++)
        {
            if(chk[arr[x][j]])
            {
                printf("%d %d\n", arr[x][j], x);
                break;
            }
        }
        chk[x] = 1;
    }
    printf("\n");
}

int main()
{
    int t, i;
    scanf("%d", &t);
    for(i=0;i<t;i++)
        process();
    return 0;
}
