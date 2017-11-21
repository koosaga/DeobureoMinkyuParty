#include<bits/stdc++.h>

using namespace std;

long long pro(long long x, long long y, long long q)
{
	if(y == 0)
		return 1;
	if(y % 2)
		return (__int128)x * pro(x, y-1, q) % q;
	long long t = pro(x, y/2, q);
	return (__int128)t * t % q;
}

long long wei[70];
pair<long long, long long> rel[70];

int main()
{
    int n, i;
    long long q, r, c, k, cc;
    while(1)
    {
        scanf("%d%lld%lld", &n, &q, &r);
        if(!n && !q && !r)
        	return 0;
        
        for(i=0;i<n;i++)
        	scanf("%lld", &wei[i]);
        scanf("%lld", &c);
        
        for(i=0;i<n;i++)
        	rel[i] = {(__int128)pro(r, q-2, q) * wei[i] % q, wei[i]};
        
        k = (__int128)pro(r, q-2, q) * c % q;
        
        sort(rel, rel + n);
        
        cc = 0;
		vector<long long> res;
        for(i=n-1;i>=0;i--)
        {
        	if(cc + rel[i].first <= k)
        	{
        		cc += rel[i].first;
        		res.push_back(rel[i].second);
        	}
		}
		sort(res.begin(), res.end());
        if(1)//cc == k)
        {
        	for(auto t : res)
        		printf("%lld ", t);
        	printf("\n");
        }
        else
        	printf("NIE\n");
    }
    return 0;
}


