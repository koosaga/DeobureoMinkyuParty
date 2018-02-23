#include <bits/stdc++.h>

using namespace std;

int arr[(1 << 20) + 10];

void shu(int x, int n)
{
    if(n == 2)
        swap(arr[x], arr[x+1]);
    else
    {
        shu(x, n/2);
        shu(x+n/2, n/2);
        for(int i=x;i<x+n/2;i++)
            swap(arr[i], arr[i+n/2]);
    }
}

int main()
{
    int n, t, i;
    scanf("%d%d", &n, &t);
    for(i=0;i<(1<<n);i++)
        scanf("%d", &arr[i]);
    
    if(t % 2 == 1)
        shu(0, 1<<n);
     
    for(i=0;i<(1<<n);i++)
        printf("%d ", arr[i]);
        
    return 0;
}
