#include<bits/stdc++.h>
using namespace std;
int q;
int n, m, a, b;
int mm[1010][1010];
int seal[1010][1010];
bool valid(int a, int b)
{
    return 0<=a && a<n && 0<=b && b<m;
}
bool tmain()
{
    scanf("%d%d%d%d", &n, &m, &a, &b);
    for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j)
        {
            char c; scanf(" %c", &c);
            if(c=='x') mm[i][j] = 1;
            else mm[i][j] = 0;
        }
    vector<pair<int, int> > V;
    int mini = a;
    int minj = b;
    for(int i=0; i<a; ++i)
        for(int j=0; j<b; ++j)
        {
            char c; scanf(" %c", &c);
            if(c=='x') seal[i][j] = 1;
            else seal[i][j] = 0;
            if(seal[i][j])
            {
                V.emplace_back(i, j);
                mini = min(mini, i);
                minj = min(minj, j);
            }
        }
    for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j)
        {
            int x = i + V[0].first - mini;
            int y = j + V[0].second - minj;
            if(valid(x, y) && mm[x][y])
            {
                for(pair<int, int> t: V)
                {
                    int xx = i + t.first - mini;
                    int yy = j + t.second - minj;
                    //printf("%d %d\n", xx, yy);
                    if(valid(xx, yy))
                    {
                        if(mm[xx][yy]==0) return false;
                        mm[xx][yy] = 0;
                    }
                    else return false;
                }
            }
        }
    for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j)
            if(mm[i][j] != 0) return false;
    return true;
}
int main()
{
    scanf("%d", &q);
    while(q--)
        puts(tmain()?"TAK":"NIE");
}
