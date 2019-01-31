#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
using pi = pair<int, int>;

int n;
int a[MAXN], b[MAXN];
vector<int> reduce(int x){
	vector<pi> bv;
	for(int j=0; j<n; j++) bv.emplace_back(-b[j], j);
	sort(bv.begin(), bv.end());
	vector<int> v;
	for(int i=0; i<bv.size() && i < x; i++){
		if(b[bv[i].second]) b[bv[i].second]--;
		v.push_back(bv[i].second);
	}
	return v;
}

int ans;
vector<vector<int>> ansfrm;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	ans = -1;
	{
		memcpy(b, a, sizeof(b));
		vector<vector<int>> v;
		while(count(b, b + n, b[0]) != n){
			v.push_back(reduce(2));
		}
		if(ans < b[0]){
			ans = b[0];
			ansfrm = v;
		}
	}
	if(n >= 3){
		memcpy(b, a, sizeof(b));
		vector<vector<int>> v;
		v.push_back(reduce(3));
		while(count(b, b + n, b[0]) != n){
			v.push_back(reduce(2));
		}
		if(ans < b[0]){
			ans = b[0];
			ansfrm = v;
		}
	}
	cout << ans << endl;
	cout << ansfrm.size() << endl;
	for(auto &j : ansfrm){
		int chk[105] = {};
		for(auto &k : j) chk[k] = 1;
		for(int j=0; j<n; j++) printf("%d", chk[j]);
		puts("");
	}
}
