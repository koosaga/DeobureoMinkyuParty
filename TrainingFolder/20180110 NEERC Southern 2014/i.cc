#include<bits/stdc++.h>
using namespace std;
int arr[2002];
int N;
int knap[101010];
int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i) scanf("%d", arr+i);
    sort(arr, arr+N);
    int W = arr[N-1];
    N--;
    for(int i=0; i<N; ++i)
    {
        int t = arr[i];
        for(int j=W-t; j>=0; --j)
            knap[j+t] = max(knap[j+t], knap[j]+1);
    }
    printf("%d\n", knap[W]+1);
}
