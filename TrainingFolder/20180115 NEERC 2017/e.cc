#include <bits/stdc++.h>

using namespace std;

int cnt[1010];

int main()
{
    int n, a, u, i;
    scanf("%d", &n);
    
    u = 0;
    vector<int> uni;
    for(i=0;i<n;i++)
    {
        scanf("%d", &a);
        if(a > 0)
            cnt[a]++;
        else if(a == 0)
            u++;
        else
        {
            if(cnt[-a] > 0)
                cnt[-a]--;
            else if(u > 0)
            {
                uni.push_back(-a);
                u--;
            }
            else
            {
                printf("No");
                return 0;
            }
        }
    }
    
    while(u)
    {
        uni.push_back(1);
        u--;
    }
    
    printf("Yes\n");
    for(int &c : uni)
        printf("%d ", c);
    return 0;
}
