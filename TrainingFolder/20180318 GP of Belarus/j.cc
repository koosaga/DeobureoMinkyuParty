#include<bits/stdc++.h>
using namespace std;
bool can(int x, int y, int N)
{
    while(x < N || y < N)
    {
        if(x == N || y == N) return true;
        int ny = x + y;
        x = y;
        y = ny;
    }
    return false;
}
int main()
{
    int N; scanf("%d", &N);
    for(int xpy = 1;;++xpy)
        for(int x=0; x<=xpy; ++x)
        {
            int y = xpy - x;
            if(x == N || y == N || can(x, y, N))
            {
                printf("%d %d\n", x, y);
                return 0;
            }
        }
}
