#include<bits/stdc++.h>
using namespace std;
int N;
int arr[10101];
char buf[252];
const int BROKEN = 0x3f3f3f3f;
int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i)
    {
        scanf("%s", buf);
        if(buf[0] == 'x') arr[i] = BROKEN;
        else arr[i] = atoi(buf);
    }
    int maxv = 0x3f3f3f3f;
    int minv = -0x3f3f3f3f;
    for(int i=0; i<N-1; ++i)
    {
        if(arr[i] == arr[i+1] && arr[i] == BROKEN)
        {
            puts("none");
            return 0;
        }
        if(arr[i] != BROKEN)
        {
            if(i%2==0)
            {
                if(arr[i+1] != BROKEN && arr[i] >= arr[i+1])
                {
                    puts("none");
                    return 0;
                }
            }
            else
            {
                if(arr[i+1] != BROKEN && arr[i] <= arr[i+1])
                {
                    puts("none");
                    return 0;
                }
            
            }
        }
    }
    for(int i=0; i<N; ++i)
    {
        if(arr[i] != BROKEN) continue;
        if(i%2==0)
        {
            if(i) maxv = min(maxv, arr[i-1]);
            if(i!=N-1) maxv = min(maxv, arr[i+1]);
        }
        else
        {
            if(i) minv = max(minv, arr[i-1]);
            if(i!=N-1) minv = max(minv, arr[i+1]);
        
        }
    }
    maxv--; minv++;
    if(maxv == minv)
    {
        printf("%d\n", maxv);
    }
    else if(maxv > minv)
    {
        puts("ambiguous");
    }
    else
    {
        puts("none");
    }
    return 0;
}
