#include<bits/stdc++.h>
using namespace std;
int N;
int sx, sy;
int x[9], y[9];
complex<double> pt[8];

complex<double> reflect(complex<double> p1, complex<double> p2, complex<double> p)
{
    double theta = arg(p2-p1);
    
    p -= p1;
    p *= exp(complex<double>(0, -theta));
    p = complex<double>(p.real(), -p.imag());
    p *= exp(complex<double>(0, theta));
    p += p1;
    
    return p;
}

void reflect(complex<double> x, complex<double> y)
{
    for(int i=0; i<N; ++i)
    
        pt[i] = reflect(x, y, pt[i]);
}
const double PI = 3.141592653589793238;
bool solve(int vertexorder[])
{
    double a1[8];
    double a2[8];
    double maxv = -9999;
    double minv = 9999;
    for(int i=0; i<N; ++i)
    {
        pt[i] = complex<double>(x[i] - sx, y[i]- sy);
    }
    for(int i=0; i<N; ++i)
    {
        complex<double> l1 = pt[vertexorder[i]];
        complex<double> l2 = pt[(vertexorder[i]+1)%N];
        reflect(l1, l2);
        if(i%2==1)
            swap(l1, l2);
        if(abs(l1) < 5e-7) return false;
        if(abs(l2) < 5e-7) return false;
        a1[i] = arg(l1);
        a2[i] = arg(l2);
        if(a2[i] < a1[i]) a2[i] += 2*PI;
        if(a2[i] - a1[i] > PI) return false;
    }
    for(int i=0; i<N; ++i)
    {
        if(a1[i]-a1[0] > PI)
        {
            a1[i] -= 2*PI;
            a2[i] -= 2*PI;
        }
        if(a1[i]-a1[0] < -PI)
        {
            a1[i] += 2*PI;
            a2[i] += 2*PI;
        }
        //printf("%.12f %.12f\n", a1[i], a2[i]);
        
        maxv = max(maxv, a1[i]);
        minv = min(minv, a2[i]);
    }
    if(minv-maxv > 5e-7)
    {
        //printf("O%d %d %d %d\n", vertexorder[0], vertexorder[1], vertexorder[2], vertexorder[3]);
        //printf("%.12f %.12f %.12f\n", minv, maxv, minv-maxv);
        return true;
    }
    
    //printf("X%d %d %d %d\n", vertexorder[0], vertexorder[1], vertexorder[2], vertexorder[3]);
    //printf("%.12f %.12f %.12f\n", minv, maxv, minv-maxv);
    return false;
}
int main()
{
    //auto _x = reflect({0, 0}, {2, 1}, {0, 1});
    //cout << _x.real() << _x.imag();
    scanf("%d", &N);
    scanf("%d%d", &sx, &sy);
    for(int i=0; i<N; ++i) scanf("%d%d", x+i, y+i);
    x[N] = x[0]; y[N] = y[0];
    int a[8];
    int f = 0;
    for(int i=0; i<N; ++i) a[i] = i;
    do
    {
        f += solve(a);
    }while(next_permutation(a, a+N));
    printf("%d\n", f);
}





