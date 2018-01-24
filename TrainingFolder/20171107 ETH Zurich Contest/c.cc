#include<bits/stdc++.h>
using namespace std;
int N; double R;
int main()
{
    cin >> N >> R;
    double sum=0;
    double ssum=0;
    for(int i=0; i<N; ++i)
    {
        double x; cin >> x;
        sum += x;
        ssum += x*x;
    }
    printf("%.12f\n", (sum*sum-ssum)/(R*R));
}
