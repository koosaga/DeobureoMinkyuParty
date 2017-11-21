#include <bits/stdc++.h>

using namespace std;

char arr[1000010];
int mem[1000010][26];
int pos[26];

int main()
{
    int n, x, r, p, c, t, o, i, j;
    scanf("%s", arr);
    n = strlen(arr);
    
    memset(mem, -1, sizeof mem);
    
    for(i=0;i<n;i++)
    {
        x = arr[i] - 'a';
        for(j=pos[x];j<=i;j++)
            mem[j][x] = i;
        pos[x] = i + 1;
    }
    
    r = 0;
    c = 0;
    while(c < n)
    {
        p = 0;
        o = c;
        while(c < n)
        {
            t = mem[p][arr[c] - 'a'];
            if(t == -1 || t >= o)
                break;
            p = t + 1;
            c++;
        }
        if(c == o)
            c++;
        r++;
    }
    printf("%d", r);
    return 0;
}



