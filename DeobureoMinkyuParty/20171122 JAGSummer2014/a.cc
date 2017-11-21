#include<bits/stdc++.h>
using namespace std;
double dist;
int main()
{
    double ans = 0;
    scanf("%lf", &dist);
    ans = dist*sqrt(2);
    for(int i=0; i<=dist; ++i)
    {
        double remdist = sqrt(dist*dist-i*i);
        if(remdist<1) remdist = 1;
        ans = max(ans, i+remdist);
    }
    printf("%.12f\n", ans);
}
