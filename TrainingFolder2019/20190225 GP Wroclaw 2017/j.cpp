#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
const int MAXT = 530000;
const int MAXM = 1000005;
using lint = long long;
using pi = pair<lint, int>;

struct frac{
	lint x, y;
	frac mul(int _x){
		frac ret = {x * _x, y};
		return ret;
	}
};

bool cmp(frac a, frac b){
	return (__int128)a.x * b.y < (__int128)a.y * b.x;
}

struct elem{
	int x;
	frac y;
}a[MAXN];

int n;

int ccw(elem a, elem b){
	return cmp(a.y.mul(b.x), b.y.mul(a.x));
}

void solve(){
	scanf("%d",&n);
	vector<int> v;
	vector<int> w;
	for(int i=0; i<n; i++){
		int p, q, b;
		scanf("%d %d %d",&p,&q,&b);
		a[i] = {b, (frac){p - q, q}};
		if(p <= q && b <= 0){
			v.push_back(i);
		}
		else{
			w.push_back(i);
		}
	}
	sort(w.begin(), w.end(), [&](const int &p, const int &q){
		int mode1 = a[p].x < 0;
		int mode2 = a[q].x < 0;
		if(mode1 != mode2) return mode1 < mode2;
		return ccw(a[p], a[q]) > 0;
	});
	for(auto &i : v) printf("%d ", i + 1);
	for(auto &i : w) printf("%d ", i + 1);
	puts("");
}

int main(){
	int tc; scanf("%d",&tc);
	while(tc--) solve();
}
