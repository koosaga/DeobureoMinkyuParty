#include<bits/stdc++.h>

using namespace std;
using point = complex<double>;

const int MAXN = 1010;
point p[MAXN];
int N; 

const double PI = 3.141592653589793238;


double calc(point P, int gon)
{
    if(abs(P)<1e-9) return 0;
    double ang = arg(P);
    if(ang < 0) ang += 2*PI;
    for(int i=0; i<gon; ++i)
    {
        if(i == gon-1 || ang < 2*PI*(i+1)/gon)
        {
            ang -= 2*PI*i/gon;
            break;
        }
    }
    //deal with ang
    if(ang < 1e-9 || ang > 2*PI/gon - (1e-9) )
        return abs(P);
    double phi = PI/2 - PI/gon;
    double theta = PI - phi - ang;
    double x = sin(phi)/sin(theta);
    return abs(P)/x;
}

double solve(int gon)
{
    double minval = 1e18;
    double maxval = 0;
    for(int i=0; i<N; ++i)
    {
        double val = calc(p[i], gon);
        minval = min(minval, val);
        maxval = max(maxval, val);
    }
    if(abs(minval-maxval)<1e-9) return 1.0;
    return minval/maxval;
}

int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i)
    {
        double a, b;
        scanf("%lf%lf", &a, &b);
        p[i] = point(a, b);
    }
    double maxs = -1;
    int maxi = -1;
    for(int i=3; i<=8; ++i)
    {
        double score = solve(i);
        if(maxs<score)
        {
            maxs = score;
            maxi = i;
        }
    }
    printf("%d %.12f\n", maxi, maxs*maxs);
    return 0;
}
