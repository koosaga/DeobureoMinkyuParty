#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int mod = 1e9 + 7;
const int MAXN = 4005;
typedef pair<int, int> pi;

int n, p[MAXN], d[MAXN], sl[MAXN];
vector<int> one_list;
lint cost[MAXN][MAXN]; // 128MB
int nxtl[MAXN][MAXN];
int nxtr[MAXN][MAXN];
lint ps[MAXN];

lint pivot_left(int s, int e){
	lint ans = ps[e] - ps[s-1];
	ans -= 1ll * p[s] * (sl[e] - sl[s-1]);
	return ans;
}

lint pivot_right(int s, int e){
	lint ans = ps[s-1] - ps[e];
	ans += 1ll * p[e] * (sl[e] - sl[s-1]);
	return ans;
}

void get_table(){
	memset(cost, 0x3f, sizeof(cost));
	for(int i=1; i<=n; i++){
		if(d[i] == 1) one_list.push_back(i);
		sl[i] = sl[i-1] + (d[i] == 1);
		ps[i] = ps[i-1] + (d[i] == 1 ? p[i] : 0);
		if(d[i] >= (i > 1) + (i < n)){
			cost[i][i] = 0;
			if(i == 1 && i < n) cost[i][i] += -p[i];
			if(i > 1 && i == n) cost[i][i] += p[i];
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			nxtl[i][j] = nxtl[i][j-1];
			if(d[j] >= i) nxtl[i][j] = j;
		}
		nxtr[i][n+1] = n+1;
		for(int j=n; j; j--){
			nxtr[i][j] = nxtr[i][j+1];
			if(d[j] >= i) nxtr[i][j] = j;
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=i+1; j<=n; j++){
			int dneed = sl[j-1] - sl[i] + 1 + (i > 1) + (j < n);
			if(d[i] >= dneed){
				lint tmp = p[j] - p[i] + pivot_left(i, j-1);
				if(i == 1 && j < n) tmp += -p[i];
				if(i > 1 && j == n) tmp += p[i];
				cost[i][j] = min(cost[i][j], tmp);
			}
			if(d[j] >= dneed){
				lint tmp = p[j] - p[i] + pivot_right(i+1, j);
				if(i == 1 && j < n) tmp += -p[j];
				if(i > 1 && j == n) tmp += p[j];
				cost[i][j] = min(cost[i][j], tmp);
			}
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=i+2; j<=n; j++){
			int dneed = sl[j-1] - sl[i] + 2 + (i > 1) + (j < n);
			if(dneed > n) continue;
			if(i == 1 && j < n){
				for(int k=i+1; k<j; k++){
					if(d[k] >= dneed){
						cost[i][j] = min(cost[i][j], p[j] - p[i] - p[k] + 
								pivot_left(k, j-1) + pivot_right(i+1, k));
					}
				}
				continue;
			}
			if(i > 1 && j == n){
				for(int k=i+1; k<j; k++){
					if(d[k] >= dneed){
						cost[i][j] = min(cost[i][j], p[j] - p[i] + p[k] + 
								pivot_left(k, j-1) + pivot_right(i+1, k));
					}
				}
				continue;
			}
			if(sl[j-1] == sl[i]){
				if(nxtr[dneed][i+1] < j) cost[i][j] = p[j] - p[i];
				continue;
			}
			int kth = (sl[i] + sl[j-1] + 1) / 2;
			int pos = one_list[kth - 1];
			int rig = nxtr[dneed][pos], lef = nxtl[dneed][pos];
			if(lef > i){
				cost[i][j] = min(cost[i][j], 
				p[j] - p[i] + pivot_left(lef, j-1) + pivot_right(i+1, lef));
			}
			if(rig < j){
				cost[i][j] = min(cost[i][j], 
				p[j] - p[i] + pivot_left(rig, j-1) + pivot_right(i+1, rig));
			}
		}
	}
}

lint dp[MAXN];

int main(){
	pi a[MAXN];
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d %d",&a[i].first,&a[i].second);
	sort(a+1, a+n+1);
	for(int i=1; i<=n; i++) p[i] = a[i].first, d[i] = a[i].second;
	get_table();
	for(int i=1; i<=n; i++){
		dp[i] = 1e18;
		for(int j=0; j<i; j++) dp[i] = min(dp[i], dp[j] + cost[j+1][i]);
	}
	if(dp[n] > 1e16) dp[n] = -1;
	cout << dp[n] << endl;
}
