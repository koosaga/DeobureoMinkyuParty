#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const char dir[] = "ENWS";
bool chk[51][51][4];

int mem[2][51][51][4];
int las[51][51][4];
int bac[51][51];

int main()
{
    int n, x0, y0, t, i, j, k;
    scanf("%d%d%d%d", &n, &x0, &y0, &t);
    for(i=0;i<n;i++)
    {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        
        if(y1 == y2)
        {
            if(x1 > x2)
                swap(x1, x2);
            
            for(j=x1+1; j<=x2-1; j++)
                chk[j][y1][0] = chk[j][y1][2] = 1;
            
            chk[x1][y1][0] = 1;
            chk[x2][y1][2] = 1;
        }
        else
        {
            if(y1 > y2)
                swap(y1, y2);
            
            for(j=y1+1; j<=y2-1; j++)
                chk[x1][j][1] = chk[x1][j][3] = 1;
            
            chk[x1][y1][1] = 1;
            chk[x1][y2][3] = 1;
        }
    }
    
    int tim = 1;
    for(int d=0; d<4; d++)
        if(chk[x0][y0][d])
            mem[tim&1][x0][y0][d] = tim;
    tim++;
    
    for(i=1;i<=t;i++)
    {
        int l;
        char c;
        scanf("%d %c", &l, &c);
        
        for(int b=0;b<l;b++)
        {
            int idx = tim&1;
            memset(bac, -1, sizeof bac);
            for(j=0;j<=50;j++)
            {
                for(k=0;k<=50;k++)
                {
                    int xx = -1;
                    for(int d=0;d<4;d++)
                    {
                        if(mem[!idx][j][k][d] != tim-1)
                            continue;
                            
                        int nx = j + dx[d];
                        int ny = k + dy[d];
                        if(!(0 <= nx && nx <= 50 && 0 <= ny && ny <= 50))
                        	continue;
                       	
                       	las[nx][ny][d] = tim;
                        
                        if(bac[nx][ny] == -1)
                        {
                            int d3 = (d <= 1) ? d + 2 : d - 2;
                            bac[nx][ny] = d3;
                            for(int d2=0;d2<4;d2++)
                                if(d2 != d3 && chk[nx][ny][d2])
                                    mem[idx][nx][ny][d2] = tim;
                        }
                        else
                        {
                        	if(chk[nx][ny][bac[nx][ny]])
                            	mem[idx][nx][ny][bac[nx][ny]] = tim;
                        }
                    }
                }
            }
            tim++;
        }
        
        int xx;
        for(int d=0; d<4; d++)
        {
            if(dir[d] == c)
            {
                xx = d;
                break;
            }
        }
        
        int x2 = (xx <= 1) ? xx + 2 : xx - 2;
        int idx = tim&1;
        for(j=0;j<=50;j++)
        {
            for(k=0;k<=50;k++)
            {
            	if(las[j][k][xx] != tim-1)
                {
                    for(int d=0;d<4;d++)
                        if(d != xx)
                        	mem[!idx][j][k][d] = 0;
                }
                else
                {
                	mem[!idx][j][k][x2] = 0;
                }
            }
        }
    }
    
    int idx = tim&1;
    for(j=0;j<=50;j++)
    {
        for(k=0;k<=50;k++)
        {
            for(int d=0;d<4;d++)
            {
                if(mem[!idx][j][k][d] == tim-1)
                {
                    printf("%d %d\n", j, k);
                    break;
                }
            }
        }
    }
    
    return 0;
}










