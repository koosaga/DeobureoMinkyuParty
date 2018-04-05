#include<bits/stdc++.h>
using namespace std;
char A[22], B[22];
int N, M;
pair<pair<int, int>, pair<int, int> > dp[22][22];

int s(char *a, int x, char c)
{
    string s;
    for(int i=1; i<=x; ++i)
        s += a[i];
    s += c;
    for(int L=x+1; L>=0; --L)
    {
        bool flag = true;
        for(int j=1; j<=L; ++j)
        {
            if(a[j] != s[x-L+j])
                flag = false;
        }
        if(flag) return L;
    }
}

int Do2(int x, char c)
{
    return s(B, x, c);
}
int Do1(int x, char c)
{
    return s(A, x, c);
}
double M1[444][444], M2[444][444], M3[444][444];
int SZ ;
double solve(double arr[444][444])
{
    /*
    for(int i=0; i<SZ; ++i, puts(""))
        for(int j=0; j<SZ; ++j)
            printf("%f ", arr[i][j]);
    */
    int r = 0;
    for(int i=0; i<SZ; ++i)
    {
        int maxi = r;
        double maxv = abs(arr[r][i]);
        for(int j=r+1; j<SZ; ++j)
            if(maxv<arr[j][i])
            {
                maxv = abs(arr[j][i]);
                maxi = j;
            }
        if(maxv <1e-8) continue;
        if(maxi != r)
            for(int i=0; i<SZ; ++i)
                swap(arr[maxi][i], arr[r][i]);
        for(int j=i+1; j<SZ; ++j)
            arr[r][j] /= arr[r][i];
        arr[r][i] = 1;
        for(int j=0; j<SZ; ++j)
        {
            if(j == r) continue;
            for(int k=0; k<SZ; ++k)
            {
                if(i==k) continue;
                arr[j][k] -= arr[j][i] * arr[r][k];
            }
            arr[j][i] = 0;
        }
        ++r;
    }
    /*
    puts("");
    for(int i=0; i<SZ; ++i, puts(""))
        for(int j=0; j<SZ; ++j)
            printf("%f ", arr[i][j]);
    puts("");
    */
    return -arr[0][SZ-1];
}
int main()
{
    scanf("%s%s", A+1, B+1);
    N = strlen(A+1);
    M = strlen(B+1);
    SZ = (N+1)*(M+1)+1;
    for(int i=0; i<=N; ++i)
        for(int j=0; j<=M; ++j)
        {
            int mystate = i*(M+1)+j;
            M1[mystate][mystate] -= 1.0;
            M2[mystate][mystate] -= 1.0;
            M3[mystate][mystate] -= 1.0;
            if(i==N || j==M)
            {
                if(i==N && j==M)
                    M3[mystate][(N+1)*(M+1)] = 1.0;
                else if(i==N)
                    M1[mystate][(N+1)*(M+1)] = 1.0;
                else
                    M2[mystate][(N+1)*(M+1)] = 1.0;
            }
            else
            {
                int trans1 = Do1(i, 'H')*(M+1)+Do2(j, 'H');
                int trans2 = Do1(i, 'T')*(M+1)+Do2(j, 'T');
                M1[mystate][trans1] += 0.5;
                M1[mystate][trans2] += 0.5;
                M2[mystate][trans1] += 0.5;
                M2[mystate][trans2] += 0.5;
                M3[mystate][trans1] += 0.5;
                M3[mystate][trans2] += 0.5;
            }
        } 
    printf("%.12f\n%.12f\n%.12f\n", solve(M1), solve(M2), solve(M3));
}
