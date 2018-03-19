#include<bits/stdc++.h>

using namespace std;

int arr[5000];
int n;

vector<pair<int, double>> mem[5000];

void f(int s, int g)
{
    if(s == g)
        return;
        
    int m = (s+g)/2+1;
    
    f(s, m-1);
    f(m, g);
    //printf("c %d %d %d\n", s, g, m);
    vector<pair<int, double>> t;
    
    for(auto &x : mem[s])
    {
        double r = 0.0;
        int my = arr[x.first];
        for(auto &y : mem[m])
            r += y.second * my / (my + arr[y.first]);
        //printf("x %d : %lf\n", x.first, r);
        r *= x.second;
        //printf("x %d : %lf\n", x.first, r);
        
        t.push_back({x.first, r});
    }
    
    for(auto &x : mem[m])
    {
        double r = 0.0;
        int my = arr[x.first];
        for(auto &y : mem[s])
        {
            //printf("yy %lf %d %d\n", y.second, my, arr[y.first]);
            r += y.second * my / (my + arr[y.first]);
        }
        //printf("y %d : %lf\n", x.first, r);
        r *= x.second;
        //printf("y %d : %lf\n", x.first, r);
        
        t.push_back({x.first, r});
    }
    
    mem[s] = t;
}

int main()
{
    int i;
    scanf("%d", &n);
    scanf("%d", &arr[n-1]);
    
    for(i=0;i<n-1;i++)
        scanf("%d", &arr[i]);
    
    sort(arr, arr+n-1);
    reverse(arr, arr+n-1);
    
    for(i=1;i<n;i*=2);
    int s = i;
    if(s > n)
        s /= 2;
        
    int t = n-s;
    
    for(i=0;i<t;i++)
    {
        mem[i].push_back({2*i, 1.0 * arr[2*i] / (arr[2*i] + arr[2*i+1])});
        mem[i].push_back({2*i+1, 1.0 * arr[2*i+1] / (arr[2*i] + arr[2*i+1])});
    }
    
    for(i=t;i<s;i++)
    {
        mem[i].push_back({t+i, 1.0});
    }
    /*
    for(i=0;i<s;i++)
    {
        printf("i = %d\n", i);
        for(auto &x : mem[i])
            printf("%d %lf\n", x.first, x.second);
    }
    printf("\n\n");
    printf("%d %d\n", t, s);*/
    f(0, s-1);
    
    for(auto &x : mem[0])
    {
        if(x.first == n-1)
        {
            printf("%.10lf\n", x.second);
            return 0;
        }
    }
    return 0;
}





