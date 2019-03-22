#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;

int n, cnt[MAXN];
int have_besu[MAXN];
int ret[MAXN];

int main(){
	freopen("equal.in", "r", stdin);
	freopen("equal.out", "w", stdout);
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x; scanf("%d",&x);
		cnt[x]++;
	}
	vector<int> v, w;
	int distinct = 0;
	for(int i=1; i<MAXN; i++){
		if(!cnt[i]) continue;
		distinct++;
		v.push_back(cnt[i]);
		for(int j=2*i; j<MAXN; j+=i){
			if(cnt[j]){
				have_besu[i] = 1;
				break;
			}
		}
		if(have_besu[i]) w.push_back(cnt[i]);
	}
	sort(v.begin(), v.end());
	sort(w.begin(), w.end());
	int cursum = 0;
	memset(ret, 0x3f, sizeof(ret));
	for(int i=0; i<v.size(); i++){
		for(int j=cursum; j<cursum + v[i]; j++){
			ret[j] = min(ret[j], distinct + 1 - i);
		}
		cursum += v[i];
	}
	ret[n] = min(ret[n], 1);
	cursum = 0;
	for(int i=0; i<w.size(); i++){
		for(int j=cursum; j<cursum + w[i]; j++){
			ret[j] = min(ret[j], distinct - i);
		}
		cursum += w[i];
	}
	for(int j=cursum; j<=n; j++) ret[j] = min(ret[j], distinct - (int)w.size());
	for(int j=0; j<=n; j++) printf("%d ", ret[j]);
}

