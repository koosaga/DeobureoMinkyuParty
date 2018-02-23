#include<bits/stdc++.h>
using namespace std;
double D[50][50];
const double p = 2./6;
int main()
{
    D[0][0] = 1;
    for(int i=1; i<=10; ++i)
        for(int j=0; j<=i; ++j)
        {
            if(i&&j)
            {
                double x = D[i-1][j-1];
                for(int k=0; k<i-j; ++k) x *= p;
                D[i][j] += x;
            }
            if(i)
            {
                double x = D[i-1][j];
                for(int k=0; k<j; ++k) x *= 1-p;
                D[i][j] += x;
            }
        }
    printf("%f \n", D[2][1]);
    printf("%f %f\n", D[3][1], D[3][2]);
    printf("%f %f %f\n", D[4][1], D[4][2], D[4][3]);
    printf("%f %f %f %f\n", D[5][1], D[5][2], D[5][3], D[5][4]);
}
