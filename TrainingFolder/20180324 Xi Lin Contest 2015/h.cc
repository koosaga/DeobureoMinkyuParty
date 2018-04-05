#include <bits/stdc++.h>
using namespace std;

struct str
{
    int l, r, i;
    bool operator <(const str &s) const
    {
        return l < s.l;
    }
};

str arr[100010];
bool chk[100010];

void solve()
{
    int n, i;
    scanf("%d", &n);
    for(i=0;i<n;i++)
        scanf("%d", &arr[i].l);
    for(i=0;i<n;i++)
        scanf("%d", &arr[i].r);
    
    for(i=0;i<n;i++)
        arr[i].i = i+1;
        
    sort(arr, arr+n);
    priority_queue<pair<int, int>> pq;
    vector<int> res;
    int p = 0;
    int s = 0;
    memset(chk, 0, sizeof chk);
    while(1)
    {
        bool ok = 0;
        while(p < n && arr[p].l <= s)
        {
            ok = 1;
            pq.push({-arr[p].r, arr[p].i});
            p++;
        }
        
        while(!pq.empty() && s > -pq.top().first)
            pq.pop();
        
        if(!pq.empty() && s <= -pq.top().first)
        {
            ok = 1;
            res.push_back(pq.top().second);
            chk[pq.top().second] = 1;
            pq.pop();
            s++;
        }
        
        if(!ok)
            break;
    }
    
    printf("%d\n", s);
    for(int t : res)
        printf("%d ", t);
    for(i=1;i<=n;i++)
        if(!chk[i])
            printf("%d ", i);
    printf("\n");
}

int main()
{
    int t, i;
    scanf("%d", &t);
    for(i=0;i<t;i++)
        solve();
    return 0;
}
