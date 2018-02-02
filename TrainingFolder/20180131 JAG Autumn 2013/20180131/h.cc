#include<bits/stdc++.h>
using namespace std;

const double PI = 3.14159265358979;

double sq(double x)
{
    return x*x;
}

double ab(double x)
{
    return x < 0 ? -x : x;
}

double theta(double r1, double r2, double d)
{
    return acos((sq(r1)+sq(d)-sq(r2))/(2*r1*d));
}

double aaa(double r1, double r2, double d)
{
    return 0.5 * sq(r1) * sin(2*theta(r1, r2, d));
}

double sss(double r1, double r2, double d)
{
    return 0.5 * sq(r1) * 2 * theta(r1, r2, d);
}

double area(double r1, double r2, double d)
{
    if(d < ab(r1 - r2))
        return PI * sq(min(r1, r2));
    if(d > r1 + r2)
        return 0;
    return sss(r1, r2, d) - aaa(r1, r2, d) + sss(r2, r1, d) - aaa(r2, r1, d);
}

int main()
{
    int w, h, a, b, cen;
    scanf("%d%d%d%d%d", &w, &h, &a, &b, &cen);
    
    double r1, r2;
    
    r1 = sqrt(a/PI);
    r2 = sqrt(b/PI);
    
    if(max(2*r1, 2*r2) > min(w, h))
    {
        printf("impossible\n");
        return 0;
    }
    
    double maxd = sqrt(sq(w-r2-r1) + sq(h-r2-r1));
    double s, g, m;
    
    s = 0;
    g = maxd;
    for(int b=0; b<50; b++)
    {
        m = (s + g)/2;
        
        double res = area(r1, r2, m);
        
        if(res < cen)
            g = m;
        else
            s = m;
    }
    
    if(ab(area(r1, r2, s) - cen) > 0.0001)
    {
        printf("impossible\n");
        return 0;
    }
    
    bool sw = 0;
    if(r2 > r1)
    {
        sw = 1;
        swap(r1, r2);
    }
    
    double x1, y1, x2, y2;
    
    x1 = y1 = r1;
    x2 = x1 + (w-r1-r2) * s / maxd;
    y2 = y1 + (h-r1-r2) * s / maxd;
    
    if(sw)
    {
        swap(r1, r2);
        swap(x1, x2);
        swap(y1, y2);
    }
    
    printf("%.10lf %.10lf %.10lf %.10lf %.10lf %.10lf\n", x1, y1, r1, x2, y2, r2);
    return 0;
}





