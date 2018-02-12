#include<bits/stdc++.h>
using namespace std;
const int SZ = 61;
vector<int> serialize(long long  x)
{
    vector<int> res;
    for(int i=0; i<SZ; ++i)
        res.push_back(!!(x&(1ll<<i)));
    return res;
}
int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int N;
        scanf("%d", &N);
        vector<int> V(SZ);
        vector<long long> ans;
        for(int i=0; i<N; ++i)
        {
            long long t; scanf("%lld", &t);
            vector<int> S = serialize(t);
            for(int j=0; j<SZ; ++j)
                V[j] = (V[j] + S[j]) % 3;
            ans.push_back(t);
        }
        //printf("%d %d %d\n", V[2], V[1], V[0]);
        long long zerotoone = 0;
        long long onetozero = 0;
        for(int i=0; i<SZ; ++i)
        {
            if(V[i] == 1) onetozero |= (1ll<<i);
            if(V[i] == 2) zerotoone |= (1ll<<i);
        }
        if(onetozero == 0 && zerotoone == 0)
        {
            puts("C");
            continue;
        }
        bool flag = false;
        //printf("%lld %lld\n", onetozero, zerotoone);
        for(auto x: ans)
        {
            if((x&onetozero) != onetozero) continue;
            if((x&zerotoone) != 0) continue;
            long long targ = x - onetozero + zerotoone;
            if(targ < x)
            {
                puts("A");
                flag = true;
                break;
            }
        }
        if(!flag) puts("B");
    }
}















