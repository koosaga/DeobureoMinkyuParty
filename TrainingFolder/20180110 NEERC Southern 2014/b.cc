#include<bits/stdc++.h>
using namespace std;

int arr[1010];
vector<int> lis[1010];
vector<pair<int, int>> sor;
int res[1010];

int main()
{
    int k, n, i, j;
    scanf("%d%d", &k, &n);
    for(i=0;i<k;i++)
        scanf("%d", &arr[i]);
    
    for(i=0;i<k;i++)
        if(arr[i] == -1)
            arr[i] = 1;
    
    for(i=0;i<k;i++)
    {
        if(lis[arr[i]].empty())
            sor.push_back({0, arr[i]});
        lis[arr[i]].push_back(i);
    }
    
    for(auto &p : sor)
        p.first = lis[p.second].size();
    
    sort(sor.begin(), sor.end());
    
    while(!sor.empty())
    {
        int x = sor.front().second;
        int xn = sor.front().first;
        
        if(xn < k/n)
        {
            int y = sor.back().second;
            
            for(i=0;i<xn;i++)
            {
                res[lis[x].back()] = y;
                lis[x].pop_back();
            }
            
            for(i=0;i<k/n-xn;i++)
            {
                res[lis[y].back()] = x;
                lis[y].pop_back();
            }
        }
        else
        {
            for(i=0;i<k/n;i++)
            {
                res[lis[x].back()] = x;
                lis[x].pop_back();
            }
        }
        
        sor.clear();
        for(i=0;i<=n;i++)
            if(!lis[i].empty())
                sor.push_back({lis[i].size(), i});
        
        sort(sor.begin(), sor.end());
    }
    
    printf("Yes\n");
    for(i=0;i<k;i++)
        printf("%d %d\n", arr[i], res[i]);
    return 0;
}
