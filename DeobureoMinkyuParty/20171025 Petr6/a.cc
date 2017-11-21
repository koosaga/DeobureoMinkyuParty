#include<bits/stdc++.h>
using namespace std;
int n, l1, l2, p;
double arr[51];
double P(int n, int r)
{
    if(r>n) return 0;
    double ans = 1;
    for(int i=0; i<r; ++i)
        ans *= n-i;
    return ans;
}
double C(int n, int r)
{
    if(n==0 && r == 0) return 1.0;
    return P(n, r) / P(r, r);
}
int main()
{
    freopen("black-white-balls.in", "r", stdin);
    freopen("black-white-balls.out", "w", stdout);
    scanf("%d%d%d%d",&n,&l1,&l2,&p);
    double ppp = 0;
    if(p==0)
    {
        puts("0 0");
        return 0;
    }
    if(p==100)
    {
        printf("%d %d\n", l1, n-l2);
        return 0;
    }
    for(int i=l1; i<=n-l2; ++i)
    {
        double targ = P(i, l1) * P(n-i, l2) * C(l1+l2, l1);
        double tot = P(n, l1+l2);
        arr[i] = targ/tot;
        //printf("%d %f\n", i, arr[i]);
        ppp += arr[i];
    }
    double pp = (double)p/100;
    int s = l1, e = n-l2;
    int intv = n+2;
    int i1, i2;
    
    for(int i=s; i<=e; ++i)
    {
        for(int j=i; j<=e; ++j)
        {
            double x = 0;
            for(int k=i; k<=j; ++k)
            {
                x += arr[k];
            }
            //printf("%d %d %f\n",i,j,x);
            if(x>ppp*(pp-(1e-9)))
            {
                if(intv > j-i)
                {
                    intv = j -i;
                    i1= i, i2 = j;
                }
            }
        }
    }
    printf("%d %d\n", i1, i2);
}
