#include<bits/stdc++.h>
using namespace std;
using Point = complex<long long>;


long long ccw(Point a, Point b, Point c)
{
    return imag(conj((b-a))*(c-a));
}

//a sil-su ssugo shipda
bool solve(vector<pair<Point, Point> > segs, pair<Point, Point> init)
{
    for(pair<Point, Point>& x: segs)
        if(ccw(Point(0, 0), x.first, x.second)<0)
            swap(x.first, x.second);
    if(ccw(Point(0 ,0), init.first, init.second)<0)
        swap(init.first, init.second);
    int nn = segs.size();
    for(int i=0; i<nn; ++i)
    {
        Point x, y; tie(x, y) = segs[i];
        segs.emplace_back(-x, -y);
    }
    vector<pair<Point, int> > upper;
    vector<pair<Point, int> > lower;
    int cnt = 0;
    for(pair<Point, Point>& x: segs)
    {
        //cout << real(x.first) << " " << imag(x.first) << endl;
        //cout << real(x.second) << " " << imag(x.second) << endl;
        bool uc = true;
        if(imag(x.first)>0 || (imag(x.first)==0 && real(x.first)>0))
            upper.emplace_back(x.first, 1), uc = false;
        else
            lower.emplace_back(x.first, 1);
        if(imag(x.second)>0 || (imag(x.second)==0 && real(x.second)>0))
            upper.emplace_back(x.second, -1);
        else
            lower.emplace_back(x.second, -1), uc = false;
        if(uc) ++cnt;
    }
    if(init.first != Point(0, 0))
    {
        bool uc = true;
        if(imag(init.first)>0 || (imag(init.first)==0 && real(init.first)>0))
            upper.emplace_back(init.first, -10000), uc = false;
        else
            lower.emplace_back(init.first, -10000);
        if(imag(init.second)>0 || (imag(init.second)==0 && real(init.second)>0))
            upper.emplace_back(init.second, 10000);
        else
            lower.emplace_back(init.second, 10000), uc = false;
        if(uc) cnt += 10000;
    }
    
    auto cmp = [&](pair<Point, int> a, pair<Point, int> b)
    {
        long long val = ccw(Point(0, 0), a.first, b.first);
        if(val>0) return true;
        if(val<0) return false;
        return a.second > b.second;
    };
    sort(upper.begin(), upper.end(), cmp);
    sort(lower.begin(), lower.end(), cmp);
    //printf("%d\n",cnt);
    if(cnt==0) return true;
    for(auto x: upper)
    {
        //cout << "UPPER " << cnt << " " ;
        //cout << real(x.first) << " " << imag(x.first) << " " << x.second << endl;
        cnt += x.second;
        if(cnt==0) return true; 
    }
    for(auto x: lower)
    {
        //cout << "LOWER " << cnt << " ";
        //cout << real(x.first) << " " << imag(x.first) << " " << x.second << endl;
        cnt += x.second;
        if(cnt==0) return true;
    }
    return false;
}

int N;
Point p[2020];
int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i)
    {
        long long x, y; scanf("%lld%lld", &x, &y);
        p[i] = Point(x, y);
    }
    for(int i=0; i<N; ++i)
    {
        vector<pair<Point, Point> > segs;
        for(int j=0; j<i-1; ++j)
            segs.emplace_back(p[j]-p[i], p[j+1]-p[i]);
        for(int j=i+2; j<N; ++j)
            segs.emplace_back(p[j-1]-p[i], p[j]-p[i]);
        pair<Point, Point> init = make_pair(Point(0,0), Point(0,0));
        if(i!=0 && i!=N-1) init = make_pair(p[i-1], p[i+1]);
        if(!solve(segs, init))
        {
            puts("Impossible");
            return 0;
        }
    }
    puts("Possible");
    return 0;
}
