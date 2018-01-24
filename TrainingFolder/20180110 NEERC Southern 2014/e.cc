#include<bits/stdc++.h>
using namespace std;
int arr[252525];
int N;
int main()
{
    scanf("%d", &N);
    int ans = 0;
    for(int i=0; i<N; ++i)
    {
        int s, t; scanf("%d%d", &s, &t); arr[i] = s-t;
        if(arr[i]>0) ++ans;
        else --ans;
    }
    vector<pair<int, int> > res;
    for(int i=0; i<N-1 && ans<=0; ++i)
    {
        if(arr[i]<=0 && arr[i+1]<=0)
        {
            res.emplace_back(i, i+1);
            ++i; ++ans; 
        }
        else if(((arr[i]<=0)&&(arr[i+1]>0)) ||
                ((arr[i]>0)&&(arr[i+1]<=0)))
        {
            if(arr[i]+arr[i+1]>0)
            {
                res.emplace_back(i, i+1);
                ++i; ++ans;
            }
        }
    }
    if(ans<=0)
    {
        puts("-1");
        return 0;
    }
    printf("%d\n", (int)res.size());
    for(pair<int, int> x: res)
        printf("%d %d\n", x.first+1, 1+x.second);
    return 0;
}
