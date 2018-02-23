#include<bits/stdc++.h>
using namespace std;
string targ;
int main()
{
    freopen("fraud.in", "r", stdin);
    freopen("fraud.out", "w", stdout);
    vector<string> V;
    cin >> targ;
    int N; cin >> N;
    for(int i=0; i<N; ++i)
    {
        string t;
        cin >> t;
        bool flag = true;
        for(int j=0; j<9; ++j)
        {
            if(targ[j] != '*' && targ[j] != t[j])
                flag = false;
        }
        if(flag) V.push_back(t);
    }
    cout << V.size() << endl;
    for(auto x: V)
        cout << x << endl;
}
