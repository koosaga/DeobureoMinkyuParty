#include <bits/stdc++.h>
using namespace std;

char arr[2010][2010];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int main()
{
    int r, c, x, y, d, i, j;
    long long n;
    scanf("%d%d%d%d%lld", &r, &c, &x, &y, &n);
    
    d = n % 4;
    
    x--;
    y--;
    
    x = (x + (n/4) * 2) % r;
    y = (y - (n/4) * 2) % c;
    
    if(d == 1)
    {
        x = (x - n) % r;
    }
    else if(d == 2)
    {
        x = (x - (n-1)) % r;
        y = (y + n) % c;
    }
    else if(d == 3)
    {
        x += 2;
        y = (y + (n-1)) % c;
    }
    
    x = (x%r + r) % r;
    y = (y%c + c) % c;
    
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            arr[i][j] = '.';
    
    arr[x][y] = '@';
    
    int rc = max(r, c);
    int colnum = (n + 25) % 26;
    const int ___c = CLOCKS_PER_SEC * 0.98;
    while(clock() < ___c)
    {
        int cx, cy;
        cx = x;
        cy = y;
        //printf("xy %d %d\n", x, y);
        int t = min((long long)rc, n);
        char col = 'A' + colnum;
        for(i=0;i<t;i++)
        {
            x = (x + dx[d] + r) % r;
            y = (y + dy[d] + c) % c;
            //printf("color %d %d %c\n", x, y, col);
            if(arr[x][y] == '.')
                arr[x][y] = col;
        }
        
        x = (cx + dx[d] * n) % r;
        y = (cy + dy[d] * n) % c;
        
        d = (d + 3) % 4;
        colnum = (colnum + 25) % 26;
        n--;
        
        if(n == 0)
            break;
    }
    
    for(i=0;i<r;i++)
        printf("%s\n", arr[i]);
    
    return 0;
}
/*
.EG..
CE@BB
CEGA.
CEG..
FFGFF
*/


