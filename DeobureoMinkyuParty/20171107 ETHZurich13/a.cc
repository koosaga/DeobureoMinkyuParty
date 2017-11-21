#include<bits/stdc++.h>
using namespace std;
int64_t a,b,p,k;
int main()
{
    cin >> a >> b >> p >> k;
    int64_t ai = a, bi = b;
    ai%=p; bi%=p;
    for(int64_t i=1; i<=p; ++i)
    {
        if((ai+bi)%p==0)
        {
            for(int j=0; j<k-1; ++j)
                i *= p;
            cout << i << endl;
            return 0;
        }
        ai *= a;
        bi *= b;
        ai %= p;
        bi %= p;
    }
    cout << -1 << endl;
    return 0;
}
