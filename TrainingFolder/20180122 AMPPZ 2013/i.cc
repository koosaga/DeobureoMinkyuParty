#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;

int n, k, a[MAXN], nxt[MAXN];
int dp[MAXN], fu[MAXN], trk[MAXN];
vector<int> v[MAXN];

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	reverse(a+1, a+n+1);
	for(int i=1; i<=n; i++){
		v[a[i]].push_back(i);
	}
	for(int i=1; i<=n; i++){
		dp[i] = dp[i-1];
		trk[i] = trk[i-1];
		auto l = upper_bound(v[a[i]].begin(), v[a[i]].end(), i);
		if(l >= v[a[i]].begin() + k){
			l -= k;
			nxt[i] = *l;
			if(dp[i] < dp[nxt[i] - 1] + 1){
				dp[i] = dp[nxt[i] - 1] + 1;
				trk[i] = nxt[i];
				fu[i] = 1;
			}
			else if(dp[i] == dp[nxt[i] - 1] + 1 && a[trk[i]] > a[nxt[i]]){
			    trk[i] = nxt[i];
				fu[i] = 1;
			}
			else if(dp[i] == dp[nxt[i] - 1] + 1 && a[trk[i]] == a[nxt[i]] &&trk[i] < nxt[i]){
				trk[i] = nxt[i];
				fu[i] = 1;
			}
		}
	}
	cout << dp[n] * k << endl;
	vector<int> v;
	for(int j=n; j>0; ){
		if(!fu[j]){
			j--;
		}
		else{
			for(int kk=0; kk<k; kk++)v.push_back(a[j]);
			j = nxt[j] - 1;
		}
	}
	for(auto &i : v) printf("%d ", i);
}
