#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
using lint = long long;
using pi = pair<int, int>;

int n, a[MAXN];
char str[MAXN];
int chk[MAXN];

void solve(){
	memset(chk, 0, sizeof(chk));
	scanf("%d %s",&n,str);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	int h = 0;
	lint ret = 0;
	for(int i=0; i<n; i++){
		if(str[i] == '('){
			h++;
		}
		else{
			pq.emplace(a[i], i);
			h--;
			if(h < 0){
				auto x = pq.top();
				pq.pop();
				chk[x.second] = 1;
				ret += x.first;
				h++;
			}
		}
	}
	while(!pq.empty()) pq.pop();
	h = 0;
	for(int i=n-1; i>=0; i--){
		if(chk[i]) continue;
		if(str[i] == ')'){
			h++;
		}
		else{
			pq.emplace(a[i], i);
			h--;
			if(h < 0){
				auto x = pq.top();
				pq.pop();
				chk[x.second] = 1;
				ret += x.first;
				h++;
			}
		}
	}
	cout << ret << endl;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--) solve();
}
