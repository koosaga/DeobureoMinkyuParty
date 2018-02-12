#include<bits/stdc++.h>
using namespace std;

map<int, bool> proxy;

int cnt = 0;

bool query(int x, int y)
{
    if(proxy.find(x*20000 + y) == proxy.end())
    {
        if(cnt == 300000)
        {
            assert(false);
        }
        cnt++;
        printf("? %d %d\n", x, y);
        fflush(stdout);
        
        char c;
        scanf(" %c", &c);
        
        proxy[x*20000 + y] = (c != '<');
        return c != '<';
    }
    return proxy[x*20000 + y];
}

int res[10010];
int res2[10010];

int main()
{
    srand(9801);
    
    vector<vector<int>> arr;
    int n, i, j;
    scanf("%d", &n);
    
    arr.resize(1);
    for(i=1;i<=(n+1)/2;i++)
        arr[0].push_back(i);
    
    for(i=1;i<=n/2;i++)
    {
        // e[i]
        
        int s, g, x;
        s = 0;
        g = arr.size() - 1;
        while(g-s+1 >= 3)
        {
            x = (s+g)/2;
            if(query(i, arr[x][0]))
                s = x;
            else
                g = x;
        }
        
        int q, q2 = -1;
        
        if(s == g)
            q = s;
        else
        {
            if(query(i, arr[g][0]))
                q = g;
            else if(arr[g].size() < arr[s].size())
            {
                q2 = s;
                q = g;
            }
            else
            {
                q2 = g;
                q = s;
            }
        }
        
        vector<int> v1, v2;
        
        for(int &t: arr[q])
        {
            if(query(i, t))
                v1.push_back(t);
            else
                v2.push_back(t);
        }
        
        int r = 0;
        if(q2 == -1 || !v1.empty() && !v2.empty())
        {
            arr.erase(arr.begin() + q);
            if(v1.empty())
                arr.insert(arr.begin() + q, v2);
            else
            {
                arr.insert(arr.begin() + q, v1);
                if(!v2.empty())
                    arr.insert(arr.begin() + q + 1, v2);
            }
            for(j=0;j<q;j++)
                r += arr[j].size();
            r += v1.size();
        }
        else
        {
            q = q2;
            v1.clear();
            v2.clear();
            for(int &t: arr[q2])
            {
                if(query(i, t))
                    v1.push_back(t);
                else
                    v2.push_back(t);
            }
            arr.erase(arr.begin() + q);
            if(v1.empty())
                arr.insert(arr.begin() + q, v2);
            else
            {
                arr.insert(arr.begin() + q, v1);
                if(!v2.empty())
                    arr.insert(arr.begin() + q + 1, v2);
            }
            for(j=0;j<q;j++)
                r += arr[j].size();
            r += v1.size();
        }
        
        res[i] = 2*r;
    }
    
    int rr = 1;
    for(auto &v : arr)
    {
        for(int &t : v)
        {
            res2[t] = rr;
            rr += 2;
        }
    }
    
    printf("! ");
    for(i=1;i<=n/2;i++)
        printf("%d ", res[i]);
    for(i=1;i<=(n+1)/2;i++)
        printf("%d ", res2[i]);
    printf("\n");
    fflush(stdout);
    return 0;
}
















