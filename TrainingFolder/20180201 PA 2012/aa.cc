#include<bits/stdc++.h>
using namespace std;

char x[1000010];
char y[1000010];

struct str
{
    int off;
    int pos;
    bool operator <(const str &a) const
    {
        return off != a.off ? off < a.off : pos < a.pos;
    }
};

int main()
{
    int n, i;
    scanf("%d%s%s", &n, x, y);
    
    vector<int> px, py;
    for(i=0;i<n;i++)
        if(x[i] == 'b')
            px.push_back(i);
    for(i=0;i<n;i++)
        if(y[i] == 'b')
            py.push_back(i);
    
    if(px == py){
        puts("TAK");
        return 0;
    }
    if(px.size() != py.size() || px.size() <= 1 || px.size() >= n-1)
    {
        printf("NIE\n");
        return 0;
    }
    
    multiset<str> s;
    long long sum = 0;
    for(i=0;i<px.size();i++)
    {
        int off = py[i] - px[i];
        int pos = px[i];
        sum += off;
        
        if(off)
            s.insert({off, pos});
        //printf("insert %d %d\n", off, pos);
    }
    
    if(sum != 0)
    {
        printf("NIE\n");
        return 0;
    }
    
    printf("TAK\n");
    if(n > 4000)
        return 0;
    
    vector<pair<int, int>> res;
    while(!s.empty())
    {
        assert(s.size() > 1);
        
        auto it = s.begin();
        auto it2 = s.end();
        it2--;
        
        str p = *it;
        str q = *it2;
        
        s.erase(it);
        s.erase(it2);
        
        res.push_back({p.pos - 1, q.pos});
        assert(res.size() <= 1000000);
        
        p.off++;
        p.pos--;
        
        q.off--;
        q.pos++;
        
        if(p.off)
            s.insert(p);
        
        if(q.off)
            s.insert(q);
    }
    
    assert(res.size() >= 1);
    
    printf("%d\n", res.size());
    for(auto p : res)
        printf("%d %d\n", p.first + 1, p.second + 1);    
    return 0;
}
