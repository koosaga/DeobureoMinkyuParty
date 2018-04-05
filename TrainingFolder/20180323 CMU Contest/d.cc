#include<bits/stdc++.h>
using namespace std;
int N;
char a[101010];
char b[101010];
char t[101010];
int tp = 0;
int s;
int main()
{
    scanf("%s", a);
    N = strlen(a);
    for(int i=0; i<N; ++i)
    {
        b[tp++] = a[i];
        
        if(tp >= 2 && b[tp - 1] == b[tp - 2])
        {
            tp -= 2;
            
        b[tp] = 0;
        //printf("%d %s\n", i, b);
            continue;
        }
        
        int s = 0;
        while(tp >= 5)
        {
            if(b[tp - 1] == b[tp - 3] && b[tp - 3] == b[tp - 5] && b[tp - 2] == b[tp - 4])
            {
                //printf("tp %d\n", tp);
                t[s++] = b[tp - 2];
                t[s++] = b[tp - 3];
                b[tp - 5] = b[tp - 4];
                tp -= 4;
            }
            else
                break;
        }
        
        for(int j=s-1; j>=0; j--)
            b[tp++] = t[j];
        b[tp] = 0;
        //printf("%d %s\n", i, b);
        /*
        queue<int> Q;
        for(int i=max(tp-20, 0); i<tp; ++i)
            Q.push(i);
        while(!Q.empty())
        {
            int j = Q.front(); Q.pop();
            if(j+1 < tp && b[j] == b[j+1])
            {
                for(int k=j+2; j<tp; ++j)
                        b[k-2] = b[k];
                b[tp-2] = 0;
                b[tp-1] = 0;
                tp -= 2;
                for(int k=max(j-20, 0); k<=min(j+20, tp-1); ++k) Q.push(k);
            }
            else if(j+4 < tp && b[j]==b[j+2] && b[j+2] == b[j+4] && b[j+1] == b[j+3])
            {
                char A = b[j]; char B = b[j+1];
                b[j] = B; b[j+1] = A; b[j+2] = B;
                for(int k=j+5; j<tp; ++j)
                    b[k-2] = b[k];
                b[tp-2] = 0;
                b[tp-1] = 0;
                tp -= 2;
                for(int k=max(j-20, 0); k<=min(j+20, tp-1); ++k) Q.push(k);
            }
        }
        */
    }
    if(tp==0) puts("closed");
    else puts("open");
    return 0;
}
