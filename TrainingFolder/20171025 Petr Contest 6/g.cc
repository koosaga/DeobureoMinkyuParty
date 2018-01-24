#include<bits/stdc++.h>
using namespace std;
inline long long area4S2(int a, int b, int c)
{
    int s = a+b+c;
    return 1LL*s*(s-2*a)*(s-2*b)*(s-2*c);
}
int N;
int arr[10];
int N6(int N)
{
    int a=1;
    for(int i=0;i<N;++i)
        a *= 6;
    return a;
}
int main()
{
    freopen("polygon.in", "r", stdin);
    freopen("polygon.out", "w", stdout);
    scanf("%d", &N);
    for(int i=0; i<N; ++i) scanf("%d", arr+i);
    long long marea = 0x3f3f3f3f3f3f3f3fll;
    int v = N6(N-1);
    for(int i=0; i<v; ++i)
    {
        int a[3] = {0, 0, 0};
        int icopy = i;
        for(int j=0; j<N; ++j)
        {
            int v = icopy%6;
            a[v/2] += ((v%2)?1:-1)* arr[j];
            icopy /= 6;
        }
        if(a[0]<0) a[0] = -a[0];
        if(a[1]<0 || a[2]<0) continue;
        if(a[0]>a[2]+a[1] || a[1]>a[2]+a[0] || a[2]>a[0]+a[1]) continue;
        marea = min(marea, area4S2(a[0], a[1], a[2]));
    }
    printf("%.12f\n", sqrt(marea)/4);
    return 0;
}
