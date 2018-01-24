#include<bits/stdc++.h>
using namespace std;

void special(int N)
{
    if(N==3)
    {
        puts("1");
        puts("0 0");
        puts("0 1");
        puts("1 0");
    }
    if(N==4)
    {
        puts("4");
        puts("0 0");
        puts("0 1");
        puts("1 1");
        puts("1 0");
    }
    if(N==5)
    {
        puts("3");
        puts("0 0");
        puts("0 2");
        puts("1 2");
        puts("2 1");
        puts("2 0");
    }
    if(N==6)
    {
        puts("5");
        puts("0 0");
        puts("0 2");
        puts("1 2");
        puts("1 1");
        puts("2 1");
        puts("2 0");
    }
    if(N==7)
    {
        puts("5");
        puts("0 0");
        puts("0 4");
        puts("2 4");
        puts("2 3");
        puts("3 2");
        puts("4 2");
        puts("4 0");
    }
    if(N==8)
    {
        puts("6");
        puts("0 0");
        puts("0 4");
        puts("2 4");
        puts("2 3");
        puts("3 3");
        puts("3 2");
        puts("4 2");
        puts("4 0");
    }
    if(N==9)
    {
        puts("7");
        puts("0 6");
        puts("2 6");
        puts("2 4");
        puts("4 6");
        puts("6 4");
        puts("4 2");
        puts("6 2");
        puts("6 0");
        puts("0 0");
    }
    if(N==10)
    {
        puts("7");
        puts("0 6");
        puts("2 6");
        puts("2 5");
        puts("3 5");
        puts("4 6");
        puts("6 4");
        puts("4 2");
        puts("6 2");
        puts("6 0");
        puts("0 0");
    }
    if(N==11)
    {
        puts("8");
        puts("0 12");
        puts("4 12");
        puts("4 10");
        puts("5 11");
        puts("6 10");
        puts("8 12");
        puts("12 8");
        puts("8 4");
        puts("12 4");
        puts("12 0");
        puts("0 0");
    }
}
void tmain()
{
    vector<pair<int, int> > V;
    int N; scanf("%d", &N);
    int w = 0;
    if(N<12)
    {
        special(N);
        return;
    }
    for(int i=1; i<=100; ++i)
    {
        for(int j=0; j<=i; ++j)
        {
            if(i==2 && j==1) continue;
            if(i==1 || __gcd(j, i-j) == 1)
                V.emplace_back(j, i-j);
            if(V.size() == N/3-2) break;
        }    
    }
    const int MAXV = 100;
    V.emplace_back(2*MAXV, 2*MAXV+2);
    V.emplace_back(2*MAXV+2, 2*MAXV);
    sort(V.begin(), V.end(), [](
        pair<int, int> a, pair<int, int> b)
        {
            return a.first*b.second < b.first * a.second;
        });
    int xx = 0, yy = 0;
    for(int i=0; i<V.size(); ++i)
        xx += V[i].first;
    vector<pair<int, int> > P;
    for(int i=0; i<N/3; ++i)
    {
        xx += V[i].second; yy += V[i].first; P.emplace_back(xx, yy); 
        xx -= V[i].first; yy += V[i].second; P.emplace_back(xx, yy); 
        if(i==N/3-1)
            P.emplace_back(0, 0);
        else if(V[i] == make_pair(2*MAXV, 2*MAXV+2) && N%3 != 0)
        {
            if(N%3 == 1)
            {
                xx -= MAXV+1; yy -= MAXV; P.emplace_back(xx, yy);
                xx -= 1; yy += 1; P.emplace_back(xx, yy);
                xx -= V[i+1].second/2; yy -= V[i+1].first/2;
            }
            else
            {
                xx -= MAXV+1; yy -= MAXV; P.emplace_back(xx, yy);
                yy += 1; P.emplace_back(xx, yy);
                xx -= 1; P.emplace_back(xx, yy);
                xx -= V[i+1].second/2; yy -= V[i+1].first/2;
            }
        }
        else
        {
            xx -= V[i].second; yy -= V[i].first; P.emplace_back(xx, yy); 
        }
    }
    printf("%d\n", N- (N-1)/3);
    for(auto x: P)
        printf("%d %d\n", x.first, x.second);
    
}
int main()
{
    freopen("foss.in" ,"r",stdin);
    freopen("foss.out" ,"w",stdout);
    int X; scanf("%d", &X);
    while(X--)
        tmain();
}
