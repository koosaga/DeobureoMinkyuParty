#include<bits/stdc++.h>
using namespace std;

long long g(vector<pair<int, int>> &v1, vector<int> &v2)
{
    long long d = 0;
    for(int i=0;i<v1.size();i++)
        d += abs(v1[i].first - v2[i]);
    return d;
}

// v1 : loc, num
long long f(vector<pair<int, int>> &v1, vector<int> &v2, vector<int> &res)
{
    assert(v1.size() == v2.size());
    assert(res.empty());
    
    /*
    printf("FFF\n");
    for(auto p : v1)
        printf("v1 %d %d\n", p.first, p.second);
    for(auto p : v2)
        printf("v2 %d\n", p);
    */
    
    long long d = 0;
    int p1, p2;
    p1 = p2 = 0;
    
    priority_queue<pair<int, int>> pq1;
    priority_queue<int> pq2;
    
    while(p1 < v1.size() || p2 < v2.size())
    {
        if(p2 == v2.size() ||
           p1 < v1.size() && (v1[p1].first < v2[p2] ||
                              v1[p1].first == v2[p2] && pq1.size() >= pq2.size()))
        {
            while(!pq2.empty() && pq1.size() >= pq2.size())
            {
                auto t1 = pq1.top();
                int t2 = pq2.top();
                pq1.pop();
                pq2.pop();
                
                d += abs(t1.second - t2);
                res.push_back(-t1.first);
            }
            
            pq1.push({-v1[p1].second, v1[p1].first});
            p1++;
            
            while(!pq1.empty() && pq1.size() == pq2.size())
            {
                auto t1 = pq1.top();
                int t2 = pq2.top();
                pq1.pop();
                pq2.pop();
                
                d += abs(t1.second - t2);
                res.push_back(-t1.first);
            }
        }
        else
        {
            while(!pq1.empty() && pq2.size() >= pq1.size())
            {
                auto t1 = pq1.top();
                int t2 = pq2.top();
                pq1.pop();
                pq2.pop();
                
                d += abs(t1.second - t2);
                res.push_back(-t1.first);
            }
            
            pq2.push(v2[p2]);
            p2++;
            
            while(!pq1.empty() && pq1.size() == pq2.size())
            {
                auto t1 = pq1.top();
                int t2 = pq2.top();
                pq1.pop();
                pq2.pop();
                
                d += abs(t1.second - t2);
                res.push_back(-t1.first);
            }
        }
    }
    
    while(!pq1.empty() && pq1.size() == pq2.size())
    {
        auto t1 = pq1.top();
        int t2 = pq2.top();
        pq1.pop();
        pq2.pop();
        
        d += abs(t1.second - t2);
        res.push_back(-t1.first);
    }
    
    assert(pq1.empty() && pq2.empty());
    
    assert(g(v1, v2) == d);
    
    return d;
}

int arr[100010];
int p[100010];

int main()
{
    int n, i;
    scanf("%d", &n);
    for(i=0;i<n;i++)
        scanf("%d", &arr[i]);
    /*
    n = 100000;
    for(i=0;i<n;i++)
        arr[i] = i+1;
    
    srand(time(NULL));
    */
    //for(i=0;i<10000;i++)
    //   swap(arr[rand()%n], arr[rand()%n]);
    //random_shuffle(arr, arr+n);
    
    int c[2];
    c[0] = c[1] = 0;
    for(i=0;i<n;i++)
        c[arr[i]%2]++;
        
    if(n % 2 == 1)
    {
        vector<pair<int, int>> v1;
        vector<int> v2;
        vector<int> res;
        
        for(i=0;i<n;i++)
        {
            int t = arr[i] % 2;
            if(c[t] > c[1-t])
                v1.push_back({i, arr[i]});
            if(i%2 == 0)
                v2.push_back(i);
        }
        f(v1, v2, res);
        for(i=0;i<v2.size();i++)
            p[v2[i]] = res[i];
        
        int sz = v2.size();
        
        v1.clear();
        v2.clear();
        res.clear();
        for(i=0;i<n;i++)
        {
            int t = arr[i] % 2;
            if(c[t] < c[1-t])
                v1.push_back({i, arr[i]});
            if(i%2 == 1)
                v2.push_back(i);
        }
        f(v1, v2, res);
        for(i=0;i<v2.size();i++)
            p[v2[i]] = res[i];
        
        sz += v2.size();
        
        assert(sz == n);
    }
    else
    {
        long long t1 = 0;
        long long t2 = 0;
        vector<int> pri1;
        vector<int> pri2;
        
        {
            vector<pair<int, int>> v1;
            vector<int> v2;
            vector<int> res;
            
            for(i=0;i<n;i++)
            {
                if(arr[i]%2 == 0)
                    v1.push_back({i, arr[i]});
                if(i%2 == 0)
                    v2.push_back(i);
            }
            t1 += f(v1, v2, res);
            for(i=0;i<v2.size();i++)
                p[v2[i]] = res[i];
            
            int sz = v2.size();
            
            v1.clear();
            v2.clear();
            res.clear();
            for(i=0;i<n;i++)
            {
                if(arr[i]%2 == 1)
                    v1.push_back({i, arr[i]});
                if(i%2 == 1)
                    v2.push_back(i);
            }
            t1 += f(v1, v2, res);
            for(i=0;i<v2.size();i++)
                p[v2[i]] = res[i];
            
            sz += v2.size();
            
            assert(sz == n);
            
            for(i=0;i<n;i++)
                pri1.push_back(p[i]);
        }
        {
            vector<pair<int, int>> v1;
            vector<int> v2;
            vector<int> res;
            
            int t1 = 0;
            for(i=0;i<n;i++)
            {
                if(arr[i]%2 == 1)
                    v1.push_back({i, arr[i]});
                if(i%2 == 0)
                    v2.push_back(i);
            }
            t2 += f(v1, v2, res);
            for(i=0;i<v2.size();i++)
                p[v2[i]] = res[i];
            
            int sz = v2.size();
            
            v1.clear();
            v2.clear();
            res.clear();
            for(i=0;i<n;i++)
            {
                if(arr[i]%2 == 0)
                    v1.push_back({i, arr[i]});
                if(i%2 == 1)
                    v2.push_back(i);
            }
            t2 += f(v1, v2, res);
            for(i=0;i<v2.size();i++)
                p[v2[i]] = res[i];
            
            sz += v2.size();
            
            assert(sz == n);
            
            for(i=0;i<n;i++)
                pri2.push_back(p[i]);
        }
        
        if(t1 < t2 || t1 == t2 && pri1 <= pri2)
        {
            for(i=0;i<n;i++)
                p[i] = pri1[i];
        }
        else
        {
            for(i=0;i<n;i++)
                p[i] = pri2[i];
        }
    }
    
    for(i=0;i<n;i++)
        printf("%d ", p[i]);
    return 0;
}
