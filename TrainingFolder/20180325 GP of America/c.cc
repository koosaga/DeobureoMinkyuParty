#include <bits/stdc++.h>
using namespace std;

char tmp[20];
bool chk[(1<<16) + 10];
bool nxt[(1<<16) + 10];

int main()
{
    int n, i, j, k, l;
    scanf("%s", tmp);
    n = strlen(tmp);
    
    int s = 0;
    for(i=n-1;i>=0;i--)
        if(tmp[n - i - 1] == '1')
            s += 1 << i;
    
    chk[s] = 1;
    for(i=0;;i++)
    {
        if(chk[(1<<n) - 1])
        {
            printf("%d", i);
            return 0;
        }
        
        memset(nxt, 0, sizeof nxt);
        for(j=0;j<(1<<n);j++)
        {
            if(!chk[j])
                continue;
            
            nxt[j] = 1;
            for(k=0;k<n;k++)
            {
                int x = j;
                for(l=k;l>=max(k-i, 0);l--)
                    x ^= 1 << l;
                
                nxt[x] = 1;
            }
        }
        memcpy(chk, nxt, sizeof chk);
    }
    
    return 0;
}
