#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;

int n, a[MAXN];
int dp[MAXN];
vector<int> pos[MAXN];
set<int> s[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
		if(i && a[i-1] == a[i]){
			i--;
			n--;
		}
	}
	vector<int> v;
	for(int i=0; i<n; i++){
		v.push_back(a[i]);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for(int i=0; i<n; i++){
		a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
		pos[a[i]].push_back(i);
		s[a[i]].insert(i);
	}
	int ff = v.size();
	for(int i=ff-1; i>=0; i--){
		if(pos[i+1].empty()) continue;
		for(auto &j : pos[i]){
			if(pos[i+1].size() >= 2 && s[i+1].find(j+1) != s[i+1].end() && s[i+2].find(j+2) != s[i+2].end()){
				for(int k=0; k<pos[i+1].size() && k<3; k++){
					if(j != pos[i+1][k] - 1) dp[j] = max(dp[j], dp[pos[i+1][k]] + 1);
				}
				dp[j] = max(dp[j], dp[j+2] + 1);
			}
			else{
				if(s[i+1].find(j+1) != s[i+1].end()){
					dp[j] = max(dp[j], dp[pos[i+1][0]] + 1);
				}
				else dp[j] = max(dp[j], dp[pos[i+1][0]]);
			}
		}
		sort(pos[i].begin(), pos[i].end(), [&](const int &a, const int &b){
			return dp[a] > dp[b];
		});
	}
	cout << n - 1 - *max_element(dp, dp + MAXN) << endl;
}
