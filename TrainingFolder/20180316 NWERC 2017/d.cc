#include <bits/stdc++.h>

using namespace std;

char buf[100];
string arr[30];

multimap<string, pair<string, bool>> mp;

int main()
{
    int n, m, i;
    scanf("%d", &n);
    for(i=0;i<n;i++)
    {
        scanf("%s", buf);
        arr[i] = buf;
    }
    scanf("%d", &m);
    for(i=0;i<m;i++)
    {
        scanf("%s", buf);
        string s = buf;
        scanf("%s", buf);
        string t = buf;
        scanf("%s", buf);
        bool b;
        if(strcmp(buf, "correct") == 0)
            b=1;
        else
            b=0;
            
        mp.insert(make_pair(s, make_pair(t, b)));
    }
    
    bool single = 1;
    long long r = 1;
    for(i=0;i<n;i++)
    {
        int c = mp.count(arr[i]);
        if(c != 1)
            single = 0;
        r *= c;
    }
    
    if(single)
    {
        bool cor = 1;
        for(i=0;i<n;i++)
        {
            auto it = mp.find(arr[i]);
            if(!it->second.second)
                cor = 0;
            
            printf("%s ", it->second.first.c_str());
        }
        
        if(cor)
            printf("\ncorrect\n");
        else
            printf("\nincorrect\n");
        return 0;
    }
    
    long long cc = 1;
    for(i=0;i<n;i++)
    {
        auto p = mp.equal_range(arr[i]);
        int t = 0;
        for(auto it = p.first; it != p.second; it++)
        {
            if(it->second.second)
                t++;
        }
        
        cc *= t;
    }
    
    printf("%lld correct\n%lld incorrect\n", cc, r-cc);
    return 0;
}

