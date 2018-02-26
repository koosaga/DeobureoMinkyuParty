#include<bits/stdc++.h>
using namespace std;

pair<int, int> mem[1000010];
vector<int> chi[1000010];
int cnt = 1;

pair<int, int> INF = {0, 1000000010};

void input(int x)
{
    int c;
    scanf("%d", &c);
    
    if(c == 0)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        mem[x] = {a, b};
    }
    else
    {
        for(int i=0;i<c;i++)
        {
            cnt++;
            chi[x].push_back(cnt);
            input(cnt);
        }
    }
}

int f(int x)
{
    if(chi[x].size() == 0)
        return 0;
    
    int r = 0;
    
    mem[x] = INF;
    for(int &y : chi[x])
    {
        r += f(y);
        mem[x].first = max(mem[x].first, mem[y].first);
    }
    
    for(int &y : chi[x])
    {
        if(mem[y].second < mem[x].first)
            r++;
        else
            mem[x].second = min(mem[x].second, mem[y].second);
    }
    
    return r;
}

int main()
{
    input(1);
    printf("%d", f(1) + 1);
    
    return 0;
}

