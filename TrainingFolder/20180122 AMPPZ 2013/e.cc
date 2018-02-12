#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, k, i;
    scanf("%d%d", &n, &k);
    
    if(k > n/2)
    {
        printf("NIE");
        return 0;
    }
    
    if(n % 2 == 1)
    {
        printf("%d ", n/2 + 1);
        for(i=1;i<=n/2;i++)
            printf("%d %d ", i, i + n/2 + 1);
    }
    else
    {
        for(i=1;i<=n/2;i++)
            printf("%d %d ", n/2 + i, i);
    }
    return 0;
}
