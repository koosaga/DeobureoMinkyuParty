#include<bits/stdc++.h>

using namespace std;

struct str
{
    long long a;
    int i;
    bool operator <(const str &s) const
    {
        return s.a < a;
    }
};

vector<str> lv, hv;

int main()
{
    int n, l, i;
    long long a, m;
    scanf("%d%lld", &n, &m);
    for(i=1;i<=n;i++)
    {
        scanf("%lld%d", &a, &l);
        if(l == 1)
            lv.push_back({a, i});
        else
            hv.push_back({a, i});
    }
    
    sort(lv.begin(), lv.end());
    sort(hv.begin(), hv.end());
    
    long long sum = 0;
    for(i=0;i<lv.size();i++)
        sum += lv[i].a;
    
    int mn = n + 1, lmn, lp, li;
    
    int p = 0;
    for(i=0;i<lv.size() + 1;i++)
    {
        while(p < hv.size() && sum < m)
        {
            sum += hv[p].a;
            p++;
        }
        
        if(sum >= m)
        {
            int t = lv.size() - i + p;
            if(t < mn || t == mn && lv.size() - i > lmn)
            {
                mn = t;
                lmn = lv.size() - i;
                lp = p;
                li = lv.size() - i;
            }
        }
        
        if(i != lv.size())
            sum -= lv[lv.size() - 1 - i].a;
    }
    
    printf("%d %d\n", mn, lmn);
    for(i=0;i<li;i++)
        printf("%d ", lv[i].i);
    for(i=0;i<lp;i++)
        printf("%d ", hv[i].i);
    
    return 0;
}


