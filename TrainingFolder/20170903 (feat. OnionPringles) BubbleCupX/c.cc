#include<bits/stdc++.h>
using namespace std;
int N;
vector<pair<int, int> > V;
int arr[101010];
int pri[101010];
int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i)
        scanf("%d", arr+i);
    for(int i=0; i<N; ++i)
        V.emplace_back(arr[i]+arr[(i+1)%N]-N, i);
    sort(V.begin(), V.end());
    for(int i=0; i<N; ++i)
        pri[V[i].second] = i;
    for(int i=0; i<N; ++i)
        printf("%d ", pri[i]);
    puts("");
    
    return 0;
}
