#include<bits/stdc++.h>
using namespace std;
int s1[256];
int main()
{
    int cnt = 0;
    int N;
    scanf("%d", &N);
    for(int i=0; i<N; ++i)
        for(int j=0; j<i; ++j)
            for(int k=0; k<j; ++k)
                for(int s=0; s<k; ++s)
            for(int t=0; t<s; ++t)
                for(int r=0; r<t; ++r)
                    s1[i^j^k^s^t^r]++;
    for(int i=0; i<N; ++i)
        printf("%d\n", s1[i]);
    printf("%d\n", s1[1]-s1[0]);
    return 0;
}   
