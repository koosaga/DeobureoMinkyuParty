#include<bits/stdc++.h>
using namespace std;

long long arr[10];

int m4[10] = {6, 5, 5, 5, 4};
int m5[10][10] = {
{10, 9, 9, 9, 8, 8},
{8, 8, 8, 8, 8},
{7, 7, 7, 7},
{7, 7, 7},
{7, 6},
{6}
};

int main()
{
    int n, a, b, i;
    long long s;
    scanf("%d", &n);
    
    a = b = s = 0;
    for(i=0;i<n;i++)
    {
        scanf("%lld", &arr[i]);
        if(arr[i] == 2)
            a++;
        else if(arr[i] == 3)
            b++;
        s += arr[i];
    }
    
    if(n == 2)
        s -= 1;
    else if(n == 3)
        s -= 3;
    else if(n == 4)
        s -= m4[a];
    else if(n == 5)
        s -= m5[a][b];
    
    printf("%lld", s);
    return 0;
}
