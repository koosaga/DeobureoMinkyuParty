#include<bits/stdc++.h>
using namespace std;
const int MAXN = 101010;
long long solve(vector<pair<int, int> > from, vector<int> to, vector<int>& res)
{
    assert(from.size() == to.size());
    long long ans = 0;
    for(int i=0; i<from.size(); ++i)
        ans += abs(from[i].first - to[i]);
    int tp1 = 0, tp2 = 0;
    priority_queue<int, vector<int>, greater<int> > Q1; //from
    priority_queue<int, vector<int>, greater<int> > Q2;
    while(tp1 < from.size() || tp2 < to.size())
    {
        if(tp1!=from.size() && (
            tp2 == to.size() ||
            from[tp1].first < to[tp2] ||
            from[tp1].first == to[tp2] && Q1.size() > Q2.size()
            ) )
        {
            if(Q1.size() > Q2.size())
            {
                while(!Q2.empty())
                {
                    res[Q2.top()] = Q1.top();
                    Q1.pop(); Q2.pop();
                }
            }
            Q1.push(from[tp1++].second);
        }
        else
        {
            if(Q2.size() > Q1.size())
            {
                while(!Q1.empty())
                {
                    res[Q2.top()] = Q1.top();
                    Q1.pop(); Q2.pop();
                }
            }
            Q2.push(to[tp2++]);
        }
        if(Q1.size() == Q2.size())
            while(!Q1.empty())
            {
                res[Q2.top()] = Q1.top();
                Q1.pop(); Q2.pop();
            }
        //printf("(%d, %d) => (%d, %d)\n", tp1, tp2, (int)Q1.size(), (int)Q2.size());
    }
    //printf("%d %d\n", (int)from.size(), (int)to.size());
    assert(tp1 == from.size() && tp2==to.size());
    assert(Q1.empty() && Q2.empty());
    return ans;
}
vector<int> solve(vector<int> arr)
{
    int N = arr.size();
    vector<int> bktk(N);
    for(int i=0; i<N; ++i) bktk[i] = i;
    vector<int> ans;
    int cost = 9999999;
    do
    {
        bool flag = true;
        for(int i=0; i<N-1; ++i)
            if(arr[bktk[i]]%2==arr[bktk[i+1]]%2)
            {
                flag = false; break;
            }
        if(!flag) continue;
        int fuck = 0;
        for(int i=0; i<N; ++i)
            fuck += abs(bktk[i]-i);
        vector<int> p(N);
        for(int i=0; i<N; ++i) p[i] = arr[bktk[i]];
        if(fuck<cost || fuck==cost && ans > p)
        {
            cost = fuck;
            ans = p;
        }
    }while(next_permutation(bktk.begin(), bktk.end()));
    return ans;
}
vector<int> rsolve(vector<int> arr)
{
    int N = arr.size();
    int even = 0, quirk = 0;
    for(int i=0; i<N; ++i)
        if(arr[i]%2==0) ++even;
        else ++quirk;
    vector<pair<int, int> > evenvector;
    vector<pair<int, int> > oddvector;
    vector<int> evendest;
    vector<int> odddest;
    for(int i=0; i<N; ++i)
    {
        if(arr[i]%2==0)
            evenvector.emplace_back(i, arr[i]);
        else
            oddvector.emplace_back(i, arr[i]);
        if(i%2==0)
            evendest.push_back(i);
        else
            odddest.push_back(i);
    }
    long long maxv = 1e18;
    vector<int> ans;
    for(int i=0; i<2; ++i)
    {
        if(evenvector.size() == evendest.size())
        {   
            vector<int> p(N);
            long long t1 = solve(evenvector, evendest, p);
            long long t2 = solve(oddvector, odddest, p);
            if(maxv > t1+t2 || maxv==t1+t2 && ans > p)
            {
                maxv = t1+t2;
                ans = p;
            }
        }
        swap(evendest, odddest);
    }
    return ans;
}
int main()
{
    while(true)
    {
        vector<int> arr(rand()%2+7);
        for(int i=0; i<arr.size(); ++i)
            arr[i] = i;        
        random_shuffle(arr.begin(), arr.end());
        
        for(auto x: arr) printf("%d ", x);
        puts("");
        
        auto res = solve(arr);
        auto ans = rsolve(arr);
        for(auto x: res) printf("%d ", x);
        puts("");
        for(auto x: ans) printf("%d ", x);
        puts("");
        assert(ans == res);
    }
}












