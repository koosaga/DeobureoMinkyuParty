#include<bits/stdc++.h>
using namespace std;
int N;
int gph[1010];
bool vis[1010];
int calc()
{
    for(int i=0; i<N; ++i) vis[i] = false;
    int cnt= 0 ;
    for(int i=0; i<N; ++i)
    {
        if(vis[i]) continue;
        int j = i;
        while(!vis[j])
        {
            vis[j] = true;
            j = gph[j];
        }
        ++cnt;
    }
    //printf("%d\n", cnt);
    return cnt;
}
int main()
{
    scanf("%d", &N);
    for(int i=0; i<N/2; ++i)
    {
        gph[i] = 2*i+1;
        gph[i+N/2] = 2*i;
        if((gph[i] == i) || (gph[i+N/2] == 2*i))
            swap(gph[i], gph[i+N/2]);
    }
    
    //swap
    int now = calc();
    int i = 0;
    while(now != 1)
    {
        for(;;i = (i+1)%(N/2))
        {
            if((gph[i+N/2] == i) || (gph[i] == i+N/2))
                continue;
            
            swap(gph[i], gph[i+N/2]);
            int future = calc();
            if(now <= future)
                swap(gph[i], gph[i+N/2]);
            else
            {
                now = future;
                break;
            }
        }
    }
    /*
    for(int i=0; i<N; ++i)
        printf("%d ", i);
    puts("");
    for(int i=0; i<N; ++i)
        printf("%d ", gph[i]);
    puts("");
    */
    int x = 0;
    for(int i=0; i<N; ++i)
    {
        if(gph[x]%2) printf("1");
        else printf("0");
        x = gph[x];
    }
    puts("");
    return 0;
}
