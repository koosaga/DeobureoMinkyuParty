#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2020;
double eps = 1e-9;
double INF = 1e18;
int N, M;
int o[MAXN], a[MAXN], b[MAXN], d[MAXN];
double mindist[MAXN];

int S[2*MAXN];
int E[2*MAXN];
double W[2*MAXN];
int tp = 0;
bool debug;
void clear(){tp=0;if(debug)puts("");}
void add_edge(int s, int e, double x)
{
    if(debug)printf("%3d %3d %f\n", s, e, x);
    S[tp] = s; E[tp] = e; W[tp] = x;
    ++tp; return;
}
bool BM()
{
    mindist[0] = 0;
    for(int i=1; i<=N; ++i) mindist[i] = INF;
    for(int i=0; i<=N; ++i)
    {
        for(int j=0; j<tp; ++j)
            mindist[E[j]] = min(mindist[E[j]],
                mindist[S[j]]+W[j]);
    }
    if(debug)
    for(int i=0; i<=N; ++i)
        printf("%f\n", mindist[i]);
    for(int j=0; j<tp; ++j)
        if(mindist[E[j]] > mindist[S[j]]+W[j]+ eps)
            return true;
    return false;
}
bool negcyc(double x)
{
    clear();
    //0 -> x
    int tp = 0;
    for(int i=1; i<=N; ++i)
    {
        if(o[i] != int(-1e9))
        {
            add_edge(0, i, o[i]);
            add_edge(i, 0, -o[i] + eps);
        }
        else
        {
            add_edge(i, 0, 5e6); 
            add_edge(0, i, 5e6);
        }
    }
    for(int i=0; i<M; ++i)
        add_edge(b[i], a[i], x-d[i]);
    return BM();
}
int main()
{
    while(2 == scanf("%d%d", &N, &M))
    {
        for(int i=1; i<=N; ++i)
        {
            char buf[10];
            scanf("%s", buf);
            if(*buf == '?')
                o[i] = int(-1e9);
            else
                sscanf(buf, "%d", o+i);
        }
        for(int i=0; i<M; ++i)
            scanf("%d%d%d", a+i, b+i, d+i);
        double lo = 0;
        double hi = 2e7;
        for(int iter=0; iter<100; ++iter)
        {
            double mi = (lo+hi)/2;
            if(!negcyc(mi))
                hi = mi;
            else
                lo = mi;
        }
        //debug = true;
        negcyc(lo);
        debug = false;
        printf("%.12f\n", lo);
        for(int i=1; i<=N; ++i)
        {
            if(o[i] != int(-1e9))
                printf("%d ", o[i]);
            else
                printf("%.12f ", mindist[i]);
        }
        puts("");
    }
    return 0;
}
