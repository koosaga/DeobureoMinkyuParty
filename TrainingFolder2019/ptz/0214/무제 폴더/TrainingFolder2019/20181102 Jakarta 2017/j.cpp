#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;

int n, k, t, a[MAXN];

int main(){
	cin >> n >> k >> t;
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	sort(a, a + n);
	if(k == n){
		puts("0");
		return 0;
	}
	if(t == 0){
		puts("-1");
		return 0;
	}
	if(a[k-1] != a[k]){
		puts("0");
		return 0;
	}
	int l = count(a, a + k, a[k-1]);
	int r = count(a + k, a + n, a[k]);
	if(a[k] == 0) cout << r << endl;
	else if(a[k] == t) cout << l << endl;
	else cout << min(l, r) << endl;
}
