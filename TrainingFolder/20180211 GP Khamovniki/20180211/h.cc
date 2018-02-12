#include <bits/stdc++.h>
using namespace std;

int arr[300010];

vector<int> v;
int k, n;

void print()
{
    if(v.size() + k == n)
    {
        for(int &a : v)
            printf("%d ", a);
        for(int i = 0; i<k; i++)
            printf("%d ", arr[i]);
        printf("\n");
        exit(0);
    }
}

void push(int x)
{
    v.push_back(x);
    print();
}

int main()
{
    int m, i, j;
    scanf("%d%d%d", &k, &n, &m);
    for(i=0;i<k;i++)
        scanf("%d", &arr[i]);
    
    if(n < k)
    {
        printf("-1\n");
        return 0;
    }
    
    int t = 1;
    for(i=0;i<k;i++)
    {
        if(arr[i] == -1)
            arr[i] = t;
        else
        {
            if(arr[i] < t)
            {
                printf("-1\n");
                return 0;
            }
            t = arr[i];
        }
    }
    
    print();
    
    int a, b;
    a = arr[0];
    b = arr[k - 1];
    
    for(i=m; i>=b+1; i--)
        for(j=0;j<k;j++)
            push(i);
    
    int sum = k;
    int p = k-1;
    
    for(i=b; i>=a; i--)
    {
        while(p >= 0 && arr[p] >= i)
        {
            sum--;
            p--;
        }
        for(j=0;j<sum;j++)
            push(i);
    }
    
    printf("-1\n");
    return 0;
}

