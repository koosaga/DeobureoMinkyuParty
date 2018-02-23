#include<bits/stdc++.h>
using namespace std;


const int MAXW = 10010;
const int BIAS = 8e8;
int wei[110];
bool mem[110][MAXW+4];
// (weight, value) -> possible

void request(int a, int x, vector<bool>& q)
{
    assert(mem[a][x]);
    for(int i=1; i<=a; ++i)
    {
        assert(x>=wei[i]);
        if(mem[a-i][x-wei[i]])
        {
            for(int j=0; j<i-1; ++j)
                q.push_back(false);
            q.push_back(true);
            request(a-i, x-wei[i], q);
            return;
        }
    }
}

void Find(int a, int b, int x, int y)
{
    vector<bool> upper, lower;
    upper.push_back(true); lower.push_back(true);
    request(a-1, x, upper);
    request(b-1, y, lower);
    puts("Yes");
    for(int i=0; i<a; ++i)
    {
        int xcoord = i;
        int ycoord = BIAS;
        if(upper[i]) ycoord -= (a-1-i)*i;
        else ycoord += (a-1-i)*i;
        printf("%d %d\n", xcoord, ycoord);
    }
    for(int i=b-1; i>=0; --i)
    {
        int xcoord = i;
        int ycoord = -BIAS;
        if(lower[i]) ycoord += (b-1-i)*i;
        else ycoord -= (b-1-i)*i;
        printf("%d %d\n", xcoord, ycoord);
    }
    exit(0);
}
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    
    if(k < n - 3)
    {
        printf("No\n");
        return 0;
    }
    
    for(int i=1;i<=n;i++)
        wei[i] = i*(i-1)/2;
        
    mem[0][0] = 1;
    for(int i=1; i<=n; ++i)
        for(int j=1; j<=i; ++j)
            for(int k=wei[j]; k<=MAXW; ++k)
                mem[i][k] |= mem[i-j][k-wei[j]];
    
    for(int a=1; a<n; ++a)
    {
        int b = n-a;
        
        int internal = a * b - 2;
        if(internal > k) continue;
        
        for(int i=0; i<=k-internal; ++i)
            if(mem[a-1][i] && mem[b-1][k-internal-i])
                Find(a, b, i, k-internal-i);
    }
    assert(false);    
    return 0;
}




