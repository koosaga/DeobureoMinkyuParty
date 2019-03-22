#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int MAXW = 100000005;

struct frog{
	int l, w, h;
	bool operator<(const frog &f)const{
		return w > f.w;
	}
}a[MAXN];
;
int n, d;
int dp[MAXW];

int main(){
	scanf("%d %d",&n,&d);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].l,&a[i].w,&a[i].h);
	}
	sort(a, a + n);
	int cnt = 0;
	for(int i=0; i<n; i++){
		if(dp[a[i].w] + a[i].l > d) cnt++;
		for(int j=a[i].w-1; j>=0; j--){
			if(j + a[i].w < MAXW) dp[j] = max(dp[j], dp[j + a[i].w] + a[i].h);
			else dp[j] = max(dp[j], a[i].h);
			dp[j] = min(dp[j], 1 << 27);
		}
	}
	cout << cnt << endl;
}
