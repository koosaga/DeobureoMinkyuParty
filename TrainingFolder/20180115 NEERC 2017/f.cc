#include<bits/stdc++.h>
using namespace std;

struct str
{
    int x1, y1, x2, y2;
};

void process()
{
    int a, b, r, i;
    scanf("%d%d%d", &a, &b, &r);
    
    int d;
    int x, y;
    x = y = 0;
    d = 1;
    
    vector<str> res;
    
    while(1)
    {
        if(abs(a-x) < r && abs(b-y) < r)
        {
            int cx, cy;
            if(!(d % 2))
            {
                cx = a;
                cy = y;
            }
            else
            {
                cx = x;
                cy = b;
            }
            
            if(cy != y || cx != a)
            {
                swap(a, x);
                swap(b, y);
            }
            
            int p;
            if(x <= cx)
                p = cx - r + 1;
            else
                p = cx + r - 1;
            
            if(x == cx)
            {
                if(d == 2 || d == 3 || d == 4 || d == 5)
                    p = cx - r + 1;
                else
                    p = cx + r - 1;
            }
            
            int q;
            if(y <= cy)
                q = cy - r + 1;
            else
                q = cy + r - 1;
            
            if(y == cy)
            {
                if(d == 4 || d== 5 || d == 6 || d == 7)
                    q = cy - r + 1;
                else
                    q = cy + r - 1;
            }
            
            res.push_back({cx, q, p, cy });
            
            break;
        }
        
        int dx, dy;
        dx = abs(a - x);
        dy = abs(b - y);
        
        if(a>=x && b>=y)
        {
            res.push_back({x, y, x + r - 1, y + r - 1});
            if(dx >= dy)
            {
                d = 0;
                x = x+r;
                y = y+r-1;
            }
            else
            {
                d = 1;
                x = x+r-1;
                y = y+r;
            }
        }
        else if(a<=x && b>=y)
        {
            res.push_back({x, y, x - r + 1, y + r - 1});
            if(dx >= dy)
            {
                d = 2;
                x = x-r;
                y = y+r-1;
            }
            else
            {
                d = 3;
                x = x-r+1;
                y = y+r;
            }
        }
        else if(a<=x && b<=y)
        {
            res.push_back({x, y, x - r + 1, y - r + 1});
            if(dx >= dy)
            {
                d = 4;
                x = x-r;
                y = y-r+1;
            }
            else
            {
                d = 5;
                x = x-r+1;
                y = y-r;
            }
        }
        else if(a>=x && b<=y)
        {
            res.push_back({x, y, x + r - 1, y - r + 1});
            if(dx >= dy)
            {
                d = 6;
                x = x+r;
                y = y-r+1;
            }
            else
            {
                d = 7;
                x = x+r-1;
                y = y-r;
            }
        }
    }
    
    printf("%d\n", res.size());
    for(auto &a : res)
        printf("%d %d %d %d\n", a.x1, a.y1, a.x2, a.y2);
}

int main()
{
    int t, i;
    scanf("%d", &t);
    for(i=0;i<t;i++)
        process();
    return 0;
}
