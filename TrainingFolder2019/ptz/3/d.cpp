#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;

int n, l[MAXN], r[MAXN];
int pmax[MAXN], smax[MAXN], dp1[MAXN], dp2[MAXN];

bool mustdecent(){
	for(int i=1; i<=n; i++) pmax[i] = max(r[i], pmax[i-1]);
	for(int i=n; i; i--) smax[i] = max(r[i], smax[i+1]);
	for(int i=2; i<n; i++){
		if(pmax[i-1] > l[i] && smax[i+1] > l[i]) return 0;
	}
	return 1;
}

bool candecent(){
	for(int i=1; i<=n; i++){
		if(dp1[i-1] > r[i]){
			fill(dp1 + i, dp1 + n + 1, -1);
			break;
		}
		dp1[i] = max(dp1[i-1], l[i]);
	}
	for(int i=n; i; i--){
		if(dp2[i+1] > r[i]){
			fill(dp2 + 1, dp2 + i + 1, -1);
			break;
		}
		dp2[i] = max(dp2[i+1], l[i]);
	}
	for(int i=1; i<=n; i++){
		if(~dp1[i-1] && ~dp2[i+1] && dp1[i-1] <= r[i] && r[i] >= dp2[i+1]) return 1;
	}
	return 0;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&l[i],&r[i]);
	}
	if(mustdecent()) puts("TAK");
	else if(!candecent()) puts("NEIN");
	else puts("AgiSeokhwanDurududuru");
}
