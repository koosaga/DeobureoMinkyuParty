#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<int, int>;

mt19937 rng(0x14004);
int randint(int lb, int ub){
	return uniform_int_distribution<int>(lb, ub)(rng);
}

pi find_random_vector(){
	double rnd = randint(0, 3141592 * 2);
	rnd /= 1e6;
	int x = round(sin(rnd) * 1e8);
	int y = round(cos(rnd) * 1e8);
	return pi(x, y);
}

struct pnt{
	int first, second, sex, idx;
	bool operator<(const pnt &p)const{
		return pi(first, second) < pi(p.first, p.second);
	}
}a[MAXN];
int n;

lint dot(pnt x, pi y){ return 1ll * x.first * x.second + 1ll * y.first * y.second; }

lint ccw(pnt x, pnt y, pnt z){
	int dx1 = y.first - x.first;
	int dy1 = y.second - x.second;
	int dx2 = z.first - x.first;
	int dy2 = z.second - x.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

int chk[MAXN];

bool collinear(){
	pnt p1, p2;
	int cnt = 0;
	for(int i=0; i<n; i++){
		if(!chk[a[i].idx]){
			if(cnt == 0) p1 = a[i];
			else if(cnt == 1) p2 = a[i];
			else if(ccw(p1, p2, a[i]) != 0) return 0;
			cnt++;
		}
	}
	return 1;
}

bool unimodal(){
	int cnt0 = 0, cnt1 = 0;
	for(int i=0; i<n; i++){
		if(!chk[a[i].idx]){
			if(a[i].sex == 0) cnt0++;
			if(a[i].sex == 1) cnt1++;
			if(cnt0 && cnt1) return 0;
		}
	}
	return 1;
}

void havesex(int x){
	string retst = "Draw";
	for(int i=0; i<n; i++){
		if(!chk[a[i].idx]){
			if(a[i].sex == 0) retst = "White";
			else retst = "Black";
		}
	}
	cout << retst << " " << x << endl;
	exit(0);
}

void pass(int x){
	if(unimodal()) havesex(x);
	sort(a, a + n);
	set<pi> s;
	for(int i=0; i<n; i++){
		if(!chk[a[i].idx]) s.emplace(i, a[i].sex);
	}
	vector<pi> erm;
	for(auto it = s.begin(); it != s.end(); it++){
		auto nxt = next(it);
		if(nxt != s.end() && nxt->second != it->second){
			erm.push_back(*it);
			erm.push_back(*nxt);
		}
	}
	while(!erm.empty()){
		x++;
		vector<pi> nerm;
		for(auto &i : erm) s.erase(i);
		for(auto &i : erm){
			auto l = s.lower_bound(i);
			if(l != s.end() && l != s.begin() && prev(l)->second != l->second){
				nerm.push_back(*prev(l));
				nerm.push_back(*l);
			}
		}
		erm = nerm;
	}
	if(s.empty()){
		printf("Draw %d\n", x);
		exit(0);
	}
	if(s.begin()->first == 0){
		printf("White %d\n", x);
		exit(0);
	}
	printf("Black %d\n", x);
	exit(0);
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].first,&a[i].second,&a[i].sex);
		a[i].idx = i;
	}
	if(unimodal()) havesex(0);
	if(collinear()) pass(0);
	while(clock() < 2.4 * CLOCKS_PER_SEC){
		pi v = find_random_vector();
		sort(a, a + n, [&](const pnt &a, const pnt &b){
			return dot(a, v) < dot(b, v);
		});
		for(int i=1; i<n; i++){
			for(int j=1; j<=9 && j<=i; j++){
				if(a[i].sex != a[i-j].sex && chk[a[i].idx] + chk[a[i-j].idx] != 2){
					bool fuck = 0;
					for(int k=i-j+1; k<i; k++){
						if(ccw(a[i], a[i-j], a[k]) == 0){
							fuck = 1;
							break;
						}
					}
					if(!fuck) chk[a[i].idx] = chk[a[i-j].idx] = 1;
				}
			}
		}
	}
//	printf("%d %d %d\n", chk[0], chk[1], chk[2]);
	assert(collinear() || unimodal());
	sort(a, a + n);
	int prv = -1;
	for(int i=0; i<n; i++){
		if(chk[a[i].idx]) continue;
		if(prv == -1){
			prv = i;
			continue;
		}
		bool fucked = 0;
		for(int j=prv+1; j<i; j++){
			if(ccw(a[i], a[j], a[prv]) == 0) fucked = 1;
		}
		if(!fucked && a[i].sex != a[prv].sex){
			chk[a[i].idx] = chk[a[prv].idx] = 1;
		}
		prv = i;
	}
	pass(1);
}

