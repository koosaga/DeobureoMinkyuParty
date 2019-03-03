#include <bits/stdc++.h>
using llf =  __float128;
using namespace std;
using pi = pair<llf, int>;

int oracle(vector<llf> v){
	sort(v.begin(), v.end());
	int n = v.size();
	llf sum = 0;
	pi ret(1e18, -1);
	for(int i=0; i+1<v.size(); i++){
		int cnt = (i+2) * (i + 1) / 2;
		sum += v[i];
		if(sum < cnt) return 0;
		if(i + 1 < n) ret = min(ret, pi(sum - cnt, i + 1));
	}
	sum += v.back();
	if(fabs((long double)sum - n * (n + 1) / 2) > 1e-2) return 0;
	return ret.second;
}

struct answer{
	vector<vector<int>> perm;
	vector<llf> v;
	int size(){ return v.size(); }
	void resize(int n){
		perm.resize(n);
		v.resize(n);
		for(auto &i : perm) i.resize(n);
	}
};

vector<llf> cx(vector<llf> v, llf c){
	for(auto &i : v) i = i * c;
	return v;
}

vector<llf> add(vector<llf> v, vector<llf> w){
	for(int i=0; i<v.size(); i++) v[i] += w[i];
	return v;
}

llf determine(vector<int> chk, vector<llf> source, vector<llf> direct){
	llf src = 0;
	llf snk = 0;
	llf del = 0;
	int cnt = 0;
	for(int i=0; i<chk.size(); i++){
		if(chk[i]){
			src += source[i];
			del += direct[i];
			snk += ++cnt;
		}
	}
	// src + del * 1/T = snk
	if(fabs((long double)(src - snk)) < 1e-7) return 1;
	return del / (snk - src);
}

answer solve(vector<llf> v){
	if(v.size() == 1){
		answer ans;
		ans.perm.push_back({1});
		ans.v.push_back(1.0);
		return ans;
	}
	int n = v.size();
	vector<llf> p(n);
	for(int i=0; i<n; i++) p[i] = i + 1;
	if(is_sorted(v.begin(), v.end())) reverse(p.begin(), p.end());
    random_shuffle(p.begin(), p.end());
	vector<llf> dir = add(v, cx(p, -1));
	llf s = 0, e = 1.01;
	for(int i=0; i<180; i++){
		llf m = (s + e) / 2;
		if(oracle(add(p, cx(dir, 1 / m)))) e = m;
		else s = m;
	}
	auto meeting_point = add(p, cx(dir, 1 / e)); 
	int k = oracle(meeting_point);
	vector<int> perm(n);
	vector<int> chk(n);
	iota(perm.begin(), perm.end(), 0);
	sort(perm.begin(), perm.end(), [&](const int &a, const int &b){
		return meeting_point[a] < meeting_point[b];
	});
	for(int i=0; i<k; i++) chk[perm[i]] = 1;
	s = determine(chk, p, dir);
	meeting_point = add(p, cx(dir, 1 / s));
	vector<llf> L, R;
	for(int i=0; i<meeting_point.size(); i++){
		if(chk[i]) L.push_back(meeting_point[i]);
		else R.push_back(meeting_point[i] - k);
	}
	auto Lans = solve(L);
	auto Rans = solve(R);
	vector<pi> segs;
	llf sum = 0;
	for(int i=0; i<Lans.size()-1; i++){
		sum += Lans.v[i];
		segs.emplace_back(sum, i + 1);
	}
	sum = 0;
	for(int i=0; i<Rans.size()-1; i++){
		sum += Rans.v[i];
		segs.emplace_back(sum, -(i + 1));
	}
	segs.emplace_back(0, 0);
	segs.emplace_back(1, 0);
	sort(segs.begin(), segs.end());
	answer dap;
	dap.resize(n);
	for(int i=0; i<n-1; i++) dap.v[i] = segs[i+1].first - segs[i].first;
	{
		int prv = 0;
		llf sum = 0;
		for(int i=0; i<Lans.size(); i++){
			sum += Lans.v[i];
			int nxt = prv;
			if(i + 1 == Lans.size()) nxt = n - 1;
			else{
				while(nxt < n-1 && segs[nxt].second != i + 1) nxt++;
			}
			for(int j=prv; j<nxt; j++){
				int p = 0;
				for(int k=0; k<Lans.perm[i].size(); k++){
					while(!chk[p]) p++;
					dap.perm[j][p] = Lans.perm[i][k];
					p++;
				}
			}
			prv = nxt;
		}
	}
	{
		int prv = 0;
		llf sum = 0;
		int K = k;
		for(int i=0; i<Rans.size(); i++){
			sum += Rans.v[i];
			int nxt = prv;
			if(i + 1 == Rans.size()) nxt = n - 1;
			else{
				while(nxt < n-1 && segs[nxt].second != -(i + 1)) nxt++;
			}
			for(int j=prv; j<nxt; j++){
				int p = 0;
				for(int k=0; k<Rans.perm[i].size(); k++){
					while(chk[p]) p++;
					dap.perm[j][p] = Rans.perm[i][k] + K;
					p++;
				}
			}
			prv = nxt;
		}
	}
	for(int i=0; i<n; i++) dap.perm[n-1][i] = p[i];
	for(int i=0; i<n-1; i++) dap.v[i] *= s;
	dap.v[n-1] = 1 - s;
	return dap;
}

bool isp(vector<int> v){
	sort(v.begin(), v.end());
	for(int i=0; i<v.size(); i++){
		if(v[i] != i + 1) return 0;
	}
	return 1;
}

int main(){
srand(6969);
	int n;
	cin >> n;
	vector<llf> v(n);
	for(int i=0; i<n; i++){
		int x; cin >> x;
		v[i] = x;
	}
	if(!oracle(v)){
		puts("-1");
		return 0;
	}
	auto ans = solve(v);
	printf("%d\n", n);
	for(int i=0; i<n; i++){
		if(ans.v[i] < 0) ans.v[i] = 0;
		printf("%.20Lf ", (long double)ans.v[i]);
		for(int j=0; j<n; j++) printf("%d ", ans.perm[i][j]);
		puts("");
		assert(isp(ans.perm[i]));
	}
}


