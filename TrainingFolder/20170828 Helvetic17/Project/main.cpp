#include <cstdio>
#include <cmath>

using namespace std;

int a[25099];

void process()
{
    int n, t, i;
    double mean, sv, x;
    n=250;
    for(i=0;i<n;i++)
        scanf("%d", &a[i]);

    t=0;
    for(i=0;i<n;i++)
        t+=a[i];
    mean = 1.0*t/n;

    sv = 0;
    for(i=0;i<n;i++)
        sv+=(mean - a[i])*(mean - a[i]);
    sv /= n;
    sv = sqrt(sv);

    x = (mean + (mean*mean/6))/2;
    //printf("%lf %lf %lf\n", mean, sv, x);
    /*if(sv < 0.25*mean)
        printf("poisson\n");
    else
        printf("uniform\n");*/
    printf("%d\n", (int)mean);
}
//1 9 180 147 53 84 80 180 85 8 16
int main()
{
    //freopen("in", "r", stdin);
    int t, i;
    scanf("%d", &t);
    for(i=0;i<t;i++)
        process();
    return 0;
}
