#include <bits/stdc++.h>
using namespace std;

int arr[10010];

int main()
{
    int n, i;
    scanf("%d", &n);
    
    if(n == 2 || n % 2 == 1)
    {
        printf("NIE");
        return 0;
    }
    
    int s = 0;
    for(i=0;i<n/2-2;i++)
    {
        s += i%2 + 1;
        arr[i] = i%2 + 1;
    }
    arr[n/2-2] = n - s;
    
    for(i=0;i<=n/2-2;i++)
        printf("%d %d\n%d %d\n", i, arr[i], i+1, arr[i]);
    printf("%d %d\n%d %d\n", n/2-2+1, 0, 0, 0);
    return 0;
}
