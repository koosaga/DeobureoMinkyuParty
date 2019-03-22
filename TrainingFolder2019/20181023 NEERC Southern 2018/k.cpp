#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n, k, a[MAXN];

int main(){
	cin >> n >> k;
	for(int i=0; i<n; i++) cin >> a[i];
	int sum = accumulate(a, a + n, 0);
	if(sum % k){
		puts("No");
		return 0;
	}
	sum /= k;
	vector<int> ans;
	for(int i=0; i<n; ){
		int e = i;
		int cur = 0;
		while(e < n && cur < sum){
			cur += a[e++];
		}
		if(cur != sum){
			puts("No");
			return 0;
		}
		ans.push_back(e - i);
		i = e;
	}
	puts("Yes");
	for(auto &i : ans) printf("%d ", i);
}

