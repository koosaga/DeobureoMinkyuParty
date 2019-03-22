#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<int, int>;

int n, a[MAXN];;
vector<int> p;

int interval(int s, int e){
	return *max_element(a + s, a + e + 1) - *min_element(a + s, a + e + 1) == e - s;
}

int main(){
	while(~scanf("%d",&n)){
		for(int i=1; i<=n; i++) scanf("%d",&a[i]);
		p.resize(4);
		for(auto &i : p) scanf("%d",&i);
		auto canon = [&](vector<int> v){
			vector<int> nxt = v;
			sort(v.begin(), v.end());
			for(auto &i : nxt){
				i = lower_bound(v.begin(), v.end(), i) - v.begin() + 1;
			}
			return nxt;
		};
		lint ret = 0;
		for(int i=1; i<n; i++){
			for(int j=i+1; j<n; j++){
				for(int k=j+1; k<n; k++){
					// [1, i] [i+1, j] [j+1, k] [k+1, n]
					if(interval(1, i) && interval(i+1, j) && interval(j+1, k) && interval(k+1, n)){
						vector<int> x = {a[1], a[i+1], a[j+1], a[k+1]};
						x = canon(x);
						if(p == x) ret++;
					}
				}
			}
		}
		printf("%lld\n", ret % mod);
		fflush(stdout);
	}
}
