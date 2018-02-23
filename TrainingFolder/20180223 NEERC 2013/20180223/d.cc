#include<bits/stdc++.h>
using namespace std;
int N;
string s[50];
int main()
{
    freopen("dictionary.in", "r", stdin);
    freopen("dictionary.out", "w", stdout);
    cin >> N;
    for(int i=0; i<N; ++i) cin>>s[i];
    int sum = 0;
    for(int i=0; i<N; ++i) sum += s[i].size();
    printf("%d\n", sum+1);
    puts("0");
    int tp = 1;
    for(int i=0; i<N; ++i)
    {
        int ptp = 1;
        for(int j=0; j<s[i].size(); ++j)
        {
            printf("%d %c\n", ptp, s[i][j]);
            ptp = ++tp;
        }
    }
}
