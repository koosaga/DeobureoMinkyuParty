#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 10000005;
const int mod = 1e9 + 7;

char str[MAXN];

int prv[MAXN];
bool vis[MAXN];
lint dx[MAXN];

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%s", str+1);
		int n = strlen(str+1);
		stack<int> stk;
		for(int i=1; i<=n; i++){
			prv[i] = i;
			if(str[i] == '('){
				stk.push(i);
				continue;
			}
			if(!stk.empty()){
				prv[i] = stk.top() - 1;
				stk.pop();
			}
		}
		for(int i=n; i; i--){
			if(vis[i]) continue;
			vector<int> pth;
			for(int j=i; !vis[j]; j=prv[j]){
				vis[j] = 1;
				pth.push_back(j);
			}
			if(pth.size() == 1) continue;
			reverse(pth.begin(), pth.end());
			for(int i=0; i+1<pth.size(); i++){
				int l = pth[i]+1;
				int r = pth[i+1];
				dx[l] += 1ll * (i + 1) * (pth.size() - i - 1);
				dx[r+1] -= 1ll * (i + 1) * (pth.size() - i - 1);
			}
		}
		lint ans = 0;
		for(int i=1; i<=n; i++){
			dx[i] += dx[i-1];
			ans += 1ll * i * dx[i] % mod;

		}
		printf("%lld\n", ans);
		for(int i=0; i<n+2; i++) dx[i] = vis[i] = 0;
	}
}

