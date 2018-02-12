#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int MAXM = 5005;
typedef pair<int, int> pi;

int n, m;
char str[MAXN][MAXM];

int cnt[MAXN][MAXM];
int sum[MAXN][MAXM];
int LL[MAXN][MAXM];
int RR[MAXN][MAXM];

vector<pi> lp[MAXN];
vector<int> dp[MAXN];

int getsum(int x, int s, int e){
	if(e - s + 1 <= 0) return 0;
	return sum[x][e] - sum[x][s-1];
}

int getcnt(int x, int s, int e){
	if(e - s + 1 <= 0) return 0;
	return cnt[x][e] - cnt[x][s-1];
}

int getLeftmost(int x, int s, int e){
	assert(e - s + 1 >= 0);
	if(RR[x][s] > e) return 0;
	return str[x][RR[x][s]] - '0';
}

int getRightmost(int x, int s, int e){
	assert(e - s + 1 >= 0);
	if(LL[x][e] < s) return 0;
	return str[x][LL[x][e]] - '0';
}

bool insec(pi a, pi b){
	return max(a.first, b.first) <= min(a.second, b.second);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		char buf[MAXM] = "";
		scanf("%s",str[i] + 1);
		scanf("%s",buf);
		vector<int> tmp;
		for(int j=0; buf[j]; j++){
			if(buf[j] == '|') tmp.push_back(j + 1);
		}
		for(int j=0; j<tmp.size(); j++){
			for(int k=j; k<tmp.size(); k++){
				lp[i].push_back(pi(tmp[j], tmp[k]));
			}
		}
	}
	fill(str[n] + 1, str[n] + m + 1, '-');
	for(int i=0; i<=n; i++){
		for(int j=1; j<=m; j++){
			cnt[i][j] = cnt[i][j-1] + (isdigit(str[i][j]) != 0);
			sum[i][j] = sum[i][j-1] + (isdigit(str[i][j])?(str[i][j] - '0') : 0);
		}
		for(int j=1; j<=m+1; j++){
			if(isdigit(str[i][j])) LL[i][j] = j;
			else LL[i][j] = LL[i][j-1];
		}
		RR[i][m+1] = m+1;
		for(int j=m; j>=0; j--){
			if(isdigit(str[i][j])) RR[i][j] = j;
			else RR[i][j] = RR[i][j+1];
		}
		dp[i].resize(lp[i].size());
		if(i) fill(dp[i].begin(), dp[i].end(), -1e9);
	}
	for(int i=0; i<n-1; i++){
		for(int j=0; j<dp[i].size(); j++){
			for(int k=0; k<dp[i+1].size(); k++){
				pi li = pi(lp[i][j].first, lp[i+1][k].first);
				pi ri = pi(lp[i][j].second, lp[i+1][k].second);
				if(li.first > li.second) swap(li.first, li.second);
				if(ri.first > ri.second) swap(ri.first, ri.second);
				if(insec(li, ri)){
					int sx = max(li.first, ri.first);
					int ex = min(li.second, ri.second);
					if(getcnt(i+1, sx, ex)) continue;
					int cur = dp[i][j]
							+ getsum(i + 1, min(li.first, ri.first) + 1, max(li.second, ri.second) - 1)
							+ getRightmost(i + 1, 1, min(li.first, ri.first)) + 
							+ getLeftmost(i + 1, max(li.second, ri.second), m);	
					dp[i+1][k] = max(dp[i+1][k], cur);
				}
				else{
					if(li > ri) swap(li, ri);
					int cur = dp[i][j];
					if(li.first == li.second){
						if(isdigit(str[i + 1][li.first]) == 0){
							cur += getRightmost(i + 1, 1, li.first);
						}
					}
					else{
						cur += getsum(i + 1, li.first + 1, li.second - 1);
						cur += getRightmost(i + 1, 1, li.first);
					}
					if(ri.first == ri.second){	
						if(isdigit(str[i + 1][ri.second]) == 0){
							cur += getLeftmost(i + 1, ri.second, m);
						}
					}
					else{	
						cur += getsum(i + 1, ri.first + 1, ri.second - 1);
						cur += getLeftmost(i + 1, ri.second, m);
					}
					int kk = getcnt(i + 1, li.second, ri.first);
					if(kk == 1){
						cur += getsum(i + 1, li.second, ri.first);
					}
					else if(kk > 1){
						cur += getRightmost(i + 1, li.second, ri.first);
						cur += getLeftmost(i + 1, li.second, ri.first);
					}
					dp[i+1][k] = max(dp[i+1][k], cur);
				}
			}
		}
	}
	int ans = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<dp[i].size(); j++){
		//	printf("%d %d %d %d\n", i + 1, lp[i][j].first, lp[i][j].second, dp[i][j]);
			ans = max(ans, dp[i][j] + getsum(i + 1, lp[i][j].first, lp[i][j].second)
			+ (isdigit(str[i+1][lp[i][j].second]) == 0 ? getLeftmost(i + 1, lp[i][j].second + 1, m) : 0)
			+ (isdigit(str[i+1][lp[i][j].first]) == 0 ? getRightmost(i + 1, 1, lp[i][j].first - 1) : 0));
		}
	}
	cout << ans << endl;
}
