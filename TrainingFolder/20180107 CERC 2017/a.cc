#include<bits/stdc++.h>
using namespace std;

char arr[100][20];

int main()
{
    int m, n, l, r, x1, x2, i, j, k;
    scanf("%d%d", &m, &n);
    for(i=0;i<m+3;i++)
        scanf("%s", arr[i]);
    
    l = r = 0;
    for(i=0;i<m+3;i++)
    {
        for(j=0;j<11;j++)
        {
            if(arr[i][j] == '-')
            {
                if(j <= 4)
                    l++;
                else if(j >= 6)
                    r++;
            }
        }
    }
    
    for(i=0;i<n;i++)
    {
        int x, xn;
        
        x = 0;
        xn = 0;
        for(j=0;j<m+3;j++)
        {
            int t = 0;
            for(k=0;k<11;k++)
                if(arr[j][k] == '-')
                    t++;
            
            if(j == 1)
            {
                if(t)
                {
                    x = j;
                    xn = t + 100;
                }
            }
            else if(j == m/2+2)
            {
                if(t && t + 100 > xn)
                {
                    x = j;
                    xn = t + 100;
                }
            }
            else if(t >= xn)
            {
                if(t > xn || min({abs(j - 0), abs(j - (m/2+1)), abs(j - (m+2))}) < min({abs(x - 0), abs(x - (m/2+1)), abs(x - (m+2))}))
                {
                    x = j;
                    xn = t;
                }
            }
        }
        
        int g = 0;        
        
        if(arr[x][4] == '-' || arr[x][6] == '-')
        {
            if(arr[x][4] == '-' && arr[x][6] == '-')
            {
                if(l >= r)
                    g = 4;
                else
                    g = 6;
            }
            else if(arr[x][4] == '-')
                g = 4;
            else
                g = 6;
        }
        else if(arr[x][2] == '-' || arr[x][8] == '-')
        {
            if(arr[x][2] == '-' && arr[x][8] == '-')
            {
                if(l >= r)
                    g = 2;
                else
                    g = 8;
            }
            else if(arr[x][2] == '-')
                g = 2;
            else
                g = 8;
        }
        else if(arr[x][0] == '-' || arr[x][10] == '-')
        {
            if(arr[x][0] == '-' && arr[x][10] == '-')
            {
                if(l >= r)
                    g = 0;
                else
                    g = 10;
            }
            else if(arr[x][0] == '-')
                g = 0;
            else
                g = 10;
        }
        else if(arr[x][5] == '-')
        {
            g = 5;
        }
        else if(arr[x][1] == '-' || arr[x][9] == '-')
        {
            if(arr[x][1] == '-' && arr[x][9] == '-')
            {
                if(l >= r)
                    g = 1;
                else
                    g = 9;
            }
            else if(arr[x][1] == '-')
                g = 1;
            else
                g = 9;
        }
        
        if(g <= 4)
            l--;
        else if(g >= 6)
            r--;
        
        arr[x][g] = 'a' + i;
    }
    
    for(i=0;i<m+3;i++)
        printf("%s\n", arr[i]);
    
    return 0;
}




