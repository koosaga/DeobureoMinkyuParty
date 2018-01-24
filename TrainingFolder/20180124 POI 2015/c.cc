#include<bits/stdc++.h>
using namespace std;
int n, a, b, p, m;
int w[1010101];
int diff[1010101];
map<int, int> ms;

int fail[1000005];

int Occurence(vector<int> A, vector<int> B)
{
	int p = 0;
	for(int i=1; i<B.size(); i++){
		while(p && B[p] != B[i]) p = fail[p];
		if(B[p] == B[i]) p++;
		fail[i + 1] = p;
	}
	p = 0;
	int ans = 0;
	for(int i=0; i<A.size(); i++){
		while(p && B[p] != A[i]) p = fail[p];
		if(B[p] == A[i]) p++;
		if(p == B.size()){
			ans++;
			p = fail[p];
		}
	}
	return ans;
}

int myset(int a, int b)
{
    ms[a] = ms[a] + 1;
    ms[b+1] = ms[b+1] -1;
}
int solve()
{
    ms[0] = 0; ms[n] = 0;
    for(int i=0; i<m; ++i)
    {
        long long srange, erange;
        if(w[i])
            srange = p, erange = n-1;
        else
            srange = 0, erange = p-1;
        srange -= 1LL*a*i;
        erange -= 1LL*a*i;
        srange = (srange%n+n)%n;
        erange = (erange%n+n)%n;
        if(srange<=erange)
            myset(srange, erange);
        else
        {
            myset(srange, n-1);
            myset(0, erange);
        }
    }
    int pxf = 0;
    int pxs = 0;
    vector<pair<int, int> > V;
    int ans = 0;
    for(auto x: ms)
    {
        if(pxs == m)
            ans += x.first-pxf;
        pxf = x.first;
        pxs += x.second;
    }
    vector<int> VA;
    vector<int> VB;
    for(int i=n-(m-1); i<n; ++i)
    {
        if((1LL*i*a+b)%n<p) VA.push_back(0);
        else VA.push_back(1);
    }
    for(int i=0; i<m-1; ++i)
    {
        if((1LL*i*a+b)%n<p) VA.push_back(0);
        else VA.push_back(1);
    }
    for(int i=0; i<m; ++i)
        VB.push_back(w[i]);
    return ans - Occurence(VA, VB);
}
int main()
{
    scanf("%d%d%d%d%d", &n, &a, &b, &p, &m);
    for(int i=0; i<m; ++i)
        scanf("%1d", w+i);
    printf("%d\n", solve());   
}
