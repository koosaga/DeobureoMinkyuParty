#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
int n, m, t[MAXN], cnt[MAXN];

int main(){
	cin >> n >> m;
	for(int i=0; i<m; i++) cin >> t[i];
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			int v;
			cin >> v;
			if(t[j] == v) cnt[i]++;
		}
	}
	cout << max_element(cnt, cnt + n) - cnt + 1 << endl;
}
