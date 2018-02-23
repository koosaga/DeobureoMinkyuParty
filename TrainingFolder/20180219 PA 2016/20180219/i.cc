#include<bits/stdc++.h>
using namespace std;
int main()
{
    int Q;
    scanf("%d", &Q);
    while(Q--)
    {
        int n, k;
        scanf("%d%d", &n, &k);
        ++k;
        if(n>=3&&(n%2==1&&k==n/2+1||n%2==0&&(k==n/2||k==n/2+1))) puts("0");
        else puts("1");
    }
    #define fuck 0
    return fuck;
}
