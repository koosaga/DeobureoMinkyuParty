#include <bits/stdc++.h>
using namespace std;

int arr[250];
int N = 250;
void tmain()
{
    double m = 0;
    for(int i=0; i<N; ++i)
    {
        scanf("%d", arr+i);
        m += arr[i];
    }
    m /= N;
    double dev = 0;
    for(int i=0; i<N; ++i)
    {
        dev += arr[i]*arr[i];
    }
    dev /= N;
    dev = sqrt(dev);
    if(dev>35)
    {
        puts("uniform");
        return;
    }
    //uniform
    double P = sqrt(dev*dev*3+0.25)-0.5;
    int minv = *min_element(arr, arr+N);
    int maxv = *max_element(arr, arr+N);
    if(P<10.0 && minv+maxv!=0)
    {
        puts("poisson");
        return;
    }
    
    if(0.9*P >maxv || maxv < 1.1*P)
    {
        puts("poisson");
        return;
    }
    //Poisson
    P = dev*dev;
    int cnt = 0;
    for(int i=0; i<N; ++i)
    {
        if(-dev <= arr[i] && arr[i] <= dev) ++cnt;
    }
    if(cnt<0.5*N) puts("uniform");
    else puts("poisson");
    
    
}
int main()
{
    int T;
    scanf("%d", &T);
    while(T--) tmain();
}
