#include<bits/stdc++.h>
using namespace std;
bool mysolve(vector<int> V, vector<pair<int, int>>&ans)
{
    int N = V.size();
    for(int i=0; i<N-1; ++i)
    {
        if(V[i] == 1)
        {
            ans.emplace_back(i, i+1);
            V[i]--; V[i+1]++;
        }
        else if(V[i] == -1)
        {
            ans.emplace_back(i+1, i);
            V[i]++; V[i+1]--;
        }
        else if(V[i] == 0)
        {
            //do nothing
        }
        else return false;
            
    }
    return V[N-1] == 0; //true
}
void print(vector<pair<int, int> >& ans)
{
    puts("YES");
    printf("%d\n",(int)ans.size());
    for(auto x: ans)
        printf("%d %d\n", x.first+1, x.second+1);
    return;
}
void solve(vector<int> V)
{
    int N = V.size();
    if(N==2)
    {
        if(V[0]-V[1] == 2)
        {
            puts("YES");
            puts("1");
            puts("1 2");
        }
        else if(V[1] - V[0] == 2)
        {
            puts("YES");
            puts("1");
            puts("2 1");
        }
        else if(V[1] == V[0])
        {
            puts("YES");
            puts("0");
        }
        else puts("NO");
        return;
    }
    vector<pair<int, int> > ans;
    if(mysolve(V, ans) )
    {
        print(ans);
        return;
    }
    V[0]--;
    V[N-1]++;
    ans.clear();
    ans.emplace_back(0, N-1);
    if(mysolve(V, ans) )
    {
        print(ans);
        return;
    }
    V[0]+=2;
    V[N-1]-=2;
    ans.clear();
    ans.emplace_back(N-1, 0);
    if(mysolve(V, ans))
    {
        print(ans);
        return;
    }
    puts("NO");
    return;
}
int main()
{
    int T; scanf("%d", &T);
    while(T--)
    {
        int N; scanf("%d", &N);
        vector<int> V;
        long long ans = 0;
        for(int i=0; i<N; ++i)
        {
            int t; scanf("%d", &t);
            V.push_back(t);
            ans += t;
        }
        if(ans%N!=0)
            puts("NO");
        else
        {
            int denom = ans/N;
            for(int i=0; i<V.size(); ++i)
                V[i] -= denom;
            solve(V);
        }
    }
}
