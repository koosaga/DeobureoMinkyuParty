#include<bits/stdc++.h>
using namespace std;
int main()
{
    int N, K;
    scanf("%d%d", &N, &K);
    vector<int> a;
    for(int i=0; i<N; ++i)
    {
        int t;
        scanf("%d", &t);
        a.push_back(t);
    }
    sort(a.begin(), a.end());
    int sum = 0;
    for(int i=0; i<K; ++i) sum += a[i];
    printf("%d\n", sum);
    return 0;
}
