#include<bits/stdc++.h>
int N;
char arr[202020];
int main()
{
    scanf("%d", &N);
    scanf("%s" , arr);
    for(int i=0; i<N; ++i)
        arr[i] -= '0';
    int a = 0;
    for(int i=0; i<N; ++i)
    {
        printf("%d", arr[i]);
        if(i!=N-1) printf("+");
    }
        
}
