#include <bits/stdc++.h>
using namespace std;

int arr[1000010];

int main()
{
    int n, k, i, j;
    scanf("%d%d", &n, &k);
    for(i=1;i<=n;i++)
        scanf("%d", &arr[i]);
    
    priority_queue<int> pq;
    
    for(i=1;i<=k;i++)
        pq.push(-arr[i]);
    
    for(i=1;i<=n;i++)
    {
        if(-pq.top() == arr[i])
        {
            pq.pop();
            if(i+k <= n)
                pq.push(-arr[i+k]);
            continue;
        }
        
        sort(arr + i, arr + min(n + 1, i + k));
        break;
    }
    
    for(i=1;i<=n;i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
