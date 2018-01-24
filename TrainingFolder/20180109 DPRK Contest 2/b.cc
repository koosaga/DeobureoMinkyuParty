#include<bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
// if i>=5:
//        assert a[i] == 3*a[i-1]+24*a[i-2] - 16*a[i-3]

struct mat
{
    long long a[3][3];
}X;
mat mul(mat A, mat B)
{
    mat C;
    for(int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
        {
            C.a[i][j] = 0;
            for(int k=0; k<3; ++k)        
                C.a[i][j] += A.a[i][k]*B.a[k][j] % MOD;
            C.a[i][j] %= MOD;
        }
    return C;
}

mat ipow(mat A, long long int b)
{
    if(b==1) return A;
    mat res = ipow(A, b/2);
    res = mul(res, res);
    if(b&1) res = mul(res, A);
    return res;
}

int ans[] = {0, 0, 31, 197, 1255, 7997};
int main()
{
    X.a[0][0] = 3;
    X.a[0][1] = 24;
    X.a[0][2] = MOD-16;
    X.a[1][0] = 1;
    X.a[1][1] = 0;
    X.a[1][2] = 0;
    X.a[2][0] = 0;
    X.a[2][1] = 1;
    X.a[2][2] = 0;
    int T; cin >> T;
    while(T--)
    {
        long long int x; cin >> x;
        if(x<=5) cout << ans[x] << endl;
        else
        {
            mat Y = ipow(X, x-5);
            cout << (Y.a[0][0] * ans[5] + Y.a[0][1]*ans[4] + Y.a[0][2]*ans[3])%MOD << endl;
        }
    }         
}






/*
2 31
3 197
4 1255
5 7997
6 50959
7 324725
8 2069239
9 13185773
10 84023455
11 535421093
12 3411853831
13 21741292445
14 138541631791
15 882826252757
16 5625617242135
17 35848015683917
18 228433640818879
19 1455643422996485
20 9275769397699879
21 59107812091913213
22 376651607052592975
23 2400130001000497973
24 15294303578793113911
25 97459605047549805485
26 621040021017676182751
27 3957441726933534057317
28 25217932004464033670215
29 160695757123514099462237

*/
