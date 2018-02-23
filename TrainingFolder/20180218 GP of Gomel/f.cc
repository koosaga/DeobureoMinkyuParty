#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<pair<int, int>> res;
    
    res.push_back({1, -1});
    res.push_back({1, -1});
    
    for(int i=2;i<=100;i++)
    {
        res.push_back({i, 1});
        for(int j=0;j<i-2;j++)
            res.push_back({i, -1});
    }
    
    printf("%d %d\n", res.size(), 100);
    for(auto &p : res)
    {
        if(p.second == -1)
            printf("1 %d\n", p.first);
        else
            printf("2 %d %d\n", p.first, p.second);
    }
    
    return 0;
}
