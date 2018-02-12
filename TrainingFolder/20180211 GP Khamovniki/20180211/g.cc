#include<bits/stdc++.h>
using namespace std;
int x[101010];
int y[101010];
int N;

using frac = pair<long long, long long>;
frac norm(frac a)
{
    if(a.first == 0) return frac(0ll, 1ll);
    
    bool v = (a.first < 0)^(a.second < 0);
    long long g = __gcd(abs(a.first), abs(a.second));
    return make_pair((v?1:-1)*abs(a.first)/g, abs(a.second)/g);
}

frac add(frac a, frac b)
{
    a = norm(a); b = norm(b);
    return norm(make_pair(a.first*b.second+b.first*a.second, b.second*a.second));
}
frac mul(frac a, frac b)
{
    a = norm(a); b = norm(b);
    return norm(make_pair(a.first*b.first, a.second*b.second));
}
frac inv(frac a)
{
    int x, y; tie(x, y) = a;
    return norm(make_pair(y, x));
}
void print(frac x)
{
return;
    cout << x.first << "/" << x.second<< " ";
}
vector<frac> slope;

int main()
{
    scanf("%d", &N);
    for(int i=0; i<=N; ++i)
        scanf("%d%d", x+i, y+i);
    slope.resize(N);
    for(int i=0; i<N; ++i)
        slope[i] = norm(make_pair(y[i]-y[i+1], x[i]-x[i+1]));

    if(add(slope[0], slope[N-1]).first != 0)
    {
        puts("No");
        return 0;
    }
    
    frac totalslope = frac(0ll, 0ll);
    
    vector<pair<int, frac> > func;
    while(slope.size() > 1)
    {
        frac sM = slope[slope.size()-1]; slope.pop_back();
        frac sN = slope[slope.size()-1]; 
        sM.first = -sM.first;
        
        frac sX = mul(add(sN, sM), frac(-1ll, 2ll));
        
        func.emplace_back(x[slope.size()], sX);
        sX.first = -sX.first;
        
        
        //print(sM); print(sN);
        //cout << x[slope.size()] << " "; print(sX); cout << endl;
        //print(totalslope);
        //cout << endl;
    }
    //Verify is 0
    frac ans = make_pair(0ll, 0ll);
    for(auto d: func)
    {
        frac f = d.second;
        f.first *= abs(d.first-x[0]);
        ans = add(ans, f);
    }
    if(ans.first == y[0] && ans.second == 1)
        puts("Yes");
    else
        puts("No");
    return 0;
}














