#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using pi = pair<int, int>;
using lint = long long;

int n;
char str[MAXN];

int main(){
	int tc;
	scanf("%d",&tc);
	for(int i=1; i<=tc; i++){
		scanf("%s", str + 1);
		n = strlen(str + 1);
		vector<pi> v;
		for(int j=1; j<=n; ){
			int e = j;
			while(e <= n && str[j] == str[e]) e++;
			v.emplace_back(j, e - 1);
			j = e;
		}
		vector<lint> ps(v.size());
		for(int i=0; i<v.size(); i++){
			int l = v[i].second - v[i].first + 1;
			ps[i] = 1ll * l * l;
			if(i > 0) ps[i] += ps[i-1];
		}
		lint ret = ps.back();
		auto getsum = [&](int s, int e){
			if(s > e) return 0ll;
			lint ret = 0;
			if(e >= 0) ret += ps[e];
			if(s > 0) ret -= ps[s-1];
			return ret;
		};
		for(int j=0; j<v.size(); j++){
			if(v[j].first == v[j].second){
				lint dap = getsum(0, j - 2) + getsum(j + 2, v.size() - 1);
				int st = (j > 0 ? v[j-1].first : v[j].first);
				int ed = (j + 1 < v.size() ? v[j+1].second : v[j].second);
				dap += 1ll * (ed - st + 1) * (ed - st + 1);
				ret = max(ret, dap);
			}
			else{
				{
					int li = 1;
					int ri = v[j].second - v[j].first;
					if(j > 0) li += v[j-1].second - v[j-1].first + 1;
					ret = max(ret, getsum(0, j - 2) + 1ll * li * li + 1ll * ri * ri + getsum(j + 1, v.size() - 1));
				}
				{
					int li = v[j].second - v[j].first;
					int ri = 1;
					if(j + 1 < v.size()) ri += v[j+1].second - v[j+1].first + 1;
					ret = max(ret, getsum(0, j - 1) + 1ll * li * li + 1ll * ri * ri + getsum(j + 2, v.size() - 1));
				}
			}
		}
		printf("Case #%d: %lld\n", i, ret);
	}
}
