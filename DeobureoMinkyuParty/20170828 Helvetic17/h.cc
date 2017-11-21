#include<bits/stdc++.h>
using namespace std;
int N = 4;
char a[6010101];
int K;
//int dp[201][5];
int solve(char *ptr)
{
    int a,b,c,d,e;
    a=1;b=c=d=e=0;
    for(int i=1;i<=N;++i)
    {
        if(ptr[i-1]=='a') b+=a,d+=c;
        else c+=b,e+=d;
    }
    return e;
}
int solve2(char *ptr)
{
    int a,b,c,d,e;
    a=1;b=c=d=e=0;
    for(int i=1;i<=N;++i)
    {
        if(ptr[i-1]=='b') b+=a,d+=c;
        else c+=b,e+=d;
    }
    return e;
}
inline int ab(int x)
{
    return x < 0 ? -x : x;
}
int main()
{
    srand(9801);
    scanf("%d", &K);
    {
        char *ptr = a + 3000000;
        ptr[0] = 'a';
        ptr[1] = 'b';
        ptr[2] = 'a';
        ptr[3] = 'b';
        
        int iter=0;
        while(true)
        {
            int v = solve(ptr);
            int v2 = solve2(ptr);
            
            if(ab(v-K) > ab(v2-K))
            {
                if(v2==K)
                {
                    reverse(
                    printf("%s abab\n", ptr);
                    break;
                }
                if(v<K)
                {
                    while(rand()%2)
                        ptr[N++] = 'a';
                    ptr[N++] = 'b';
                }
                else
                {
                    while(*ptr == 'b') ++ptr, --N;
                    ++ptr;
                    --N;
                }
                if(N>200)
                {
                    ptr = a;
                    N = 4;
                }
            }
            
            if(v==K)
            {
                printf("%s abab\n", ptr);
                break;
            }
            if(v<K)
            {
                while(rand()%2)
                    ptr[N++] = 'a';
                ptr[N++] = 'b';
            }
            else
            {
                while(*ptr == 'b') ++ptr, --N;
                ++ptr;
                --N;
            }
            if(N>200)
            {
                ptr = a;
                N = 4;
            }
            ++iter;
        }
        
    }
}

