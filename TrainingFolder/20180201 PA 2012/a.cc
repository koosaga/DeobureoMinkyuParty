#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000000;
int N;
char a[MAXN+1];
char b[MAXN+1];
long long sa(char* x)
{
    long long ans = 0;
    for(int i=0; i<N; ++i)
    {
        if(x[i] == 'a')
            ans += i;
    }
    return ans;
}
set<int> abpos;
set<int> bapos;
set<int> as;
set<int> bs;
int update(int x)
{
    as.erase(x); bs.erase(x);
    as.erase(x+1); bs.erase(x+1);
    if(x) abpos.erase(x-1), bapos.erase(x-1);
    abpos.erase(x), bapos.erase(x);
    abpos.erase(x+1), bapos.erase(x+1);
    if(a[x]=='a') as.insert(x);
    else bs.insert(x);
    if(a[x+1]=='a') as.insert(x+1);
    else bs.insert(x+1);
    if(x && a[x-1] == 'a' && a[x] == 'b') abpos.insert(x-1);
    if(x && a[x-1] == 'b' && a[x] == 'a') bapos.insert(x-1);
    if(a[x] == 'a' && a[x+1] == 'b') abpos.insert(x);
    if(a[x] == 'b' && a[x+1] == 'a') bapos.insert(x);
    if(a[x+1] == 'a' && a[x+2] == 'b') abpos.insert(x+1);
    if(a[x+1] == 'b' && a[x+2] == 'a') bapos.insert(x+1);
    return 0;
}
int main()
{
    scanf("%d", &N);
    scanf("%s%s", a, b);

    int acnt1=0, acnt2=0, bcnt1=0, bcnt2=0;
    for(int i=0; i<N; ++i)
    {
        if(a[i] == 'a') acnt1++;
        else acnt2++;
        if(b[i] == 'a') bcnt1++;
        else bcnt2++;
    }
    if(acnt1<2 || bcnt1<2 || acnt2<2 || bcnt2<2)
    {
        puts("NIE");
        return 0;
    }
    if(acnt1!= bcnt1 || acnt2 != bcnt2)
    {
        puts("NIE");
        return 0;
    }
    if(sa(a)!=sa(b))
    {
        puts("NIE");
        return 0;
    }
    puts("TAK");
    if(N>4000)
        return 0;

    for(int i=0; i<N; ++i)
    {
        if(a[i] == 'a') as.insert(i);
        else bs.insert(i);
    }
    
    for(int i=0; i<N-1; ++i)
    {
        if(a[i] == 'a' && a[i+1] == 'b') abpos.insert(i);
        if(a[i] == 'b' && a[i+1] == 'a') bapos.insert(i);
    }
    vector<pair<int, int> > res;
    for(int i=0; i<N; ++i)
    {
        /*
        for(auto x: as)
            assert(a[x] == 'a');
        for(auto x: bs)
            assert(a[x] == 'b');
        for(auto x: abpos)
            assert(a[x] == 'a' && a[x+1] == 'b');
        for(auto x: bapos)
            assert(a[x] == 'b' && a[x+1] == 'a');
        for(int i=0; i<N; ++i)
        {
            if(a[i] == 'a') assert(as.find(i) != as.end());
            if(a[i] == 'b') assert(bs.find(i) != bs.end());
            if(a[i] == 'a' && a[i+1] == 'b')
                assert(abpos.find(i) != abpos.end());
            if(a[i] == 'b' && a[i+1] == 'a')
                assert(bapos.find(i) != bapos.end());
        }
        */
        while(a[i] != b[i])
        {
            if(b[i] == 'a')
            {
                //pull first ba, last ab
                int firstba = *bapos.lower_bound(i);
                int lastab = *abpos.rbegin();
                a[firstba] = 'a'; 
                a[firstba+1] = 'b';
                a[lastab] = 'b';
                a[lastab+1] = 'a';
                update(firstba);
                update(lastab);
                res.emplace_back(lastab, firstba);
            }
            else
            {
                //pull first ab, last ba
                int firstab = *abpos.lower_bound(i);
                int lastba = *bapos.rbegin();
                
                a[firstab] = 'b'; 
                a[firstab+1] = 'a';
                a[lastba] = 'a';
                a[lastba+1] = 'b';
                update(firstab);
                update(lastba);
                res.emplace_back(firstab, lastba);
            }
            
        }
        
    }
    assert(res.size() <= 1000000);
    printf("%d\n", (int)res.size());
    for(auto x: res)
        printf("%d %d\n", x.first+1, x.second+1);
    
    
}




















