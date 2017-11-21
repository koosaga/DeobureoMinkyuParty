#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+11;
int N;
int a[MAXN];
int solve(int x, int y)
{
    if(ans[x]>=y) return 1;
    return 0;
}
int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i) scanf("%d", a+i);
    for(int i=0; i<n; i++){
		int e = i;
		while(e+1 < n && a[e] <= a[e+1]) e++;
		int f = i;
		while(f+1 < n && a[f] >= a[f+1]) f++;
		ans[i] = max(e, f);
		printf("%d ", ans[i]);
	}
	for(int i=1; i<n; i++){
		for(int j=0; j+i<n; j++){
			if(ans[j] >= j+i) dp[j][j+i] = 1;
			else dp[j][j+i] = (!dp[j][j+i-1] || !dp[j+1][j+i]);
		}
	}
}
