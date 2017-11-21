#include <bits/stdc++.h>
using namespace std;
const int MAXN = 105;
typedef long long lint;

string s;
int n;
int fail[60];

lint su(string &s){
	lint ret = 0;
	for(auto &i : s) ret = ret * 2 + (i - '0');
	return ret;
}

string sex(lint x){
	string ret;
	while(x){
		ret.push_back(x % 2 + '0');
		x >>= 1;
	}
	reverse(ret.begin(), ret.end());
	return ret;
}

lint hap(lint x){
	lint ret = 0;
	for(int i=0; i<60; i++){
		lint s = (1ll << i);
		lint e = (1ll << (i + 1));
		e = min(e, x + 1);
		ret += max(0ll, e - s) * (i + 1);
	}
	return ret;
}

lint solve2(vector<string> v){
	auto a = v[0], b = v[1];
	if(b[0] == '0') return 1e18;
	auto cry = a;
	cry.back()++;
	for(int i=cry.size()-1; i>=0; i--){
		if(cry[i] > '1'){
			cry[i] -= 2;
			if(i > 0) cry[i-1]++;
		}
	}
	a = cry;
	int ok = 0;
	for(int i=1; i<=a.size() && i<=b.size(); i++){
		string l = a.substr(0, i);
		string r = b.substr(b.size() - i, i);
		if(l == r) ok = i;
	}
	string submerge = b + a.substr(ok, a.size() - ok);
	lint k = hap(su(submerge) - 1) + b.size();
	return k;
}


lint num(string x){ return su(x); }

lint solve(vector<string> v){
	lint su = num(v[1]) - 1;
	for(int i=1; i<v.size()-1; i++){
		if(v[i][0] == '0') return 1e18;
		if(num(v[i]) != su + i) return 1e18;
	}
	auto a = sex(su), b = sex(su + v.size() - 1);
	if(a.size() < v[0].size()) return 1e18;
	if(a.substr(a.size() - v[0].size(), v[0].size()) != v[0]) return 1e18;
	if(b.size() < v.back().size()) return 1e18;
	if(b.substr(0, v.back().size()) != v.back()) return 1e18;
	return hap(su + v.size() - 2) + v.back().size();
}

int main(){
	cin >> s;
	n = s.size();
	int p = 0;
	for(int i=1; i<n; i++){
		while(p && s[p] != s[i]) p = fail[p];
		fail[i + 1] = p;
	}
	int cnt = 0;
	p = 0;
	bool penis = 0;
	for(int i=1; i<(1<<16); i++){
		string v = sex(i);
		for(auto &j : v){
			while(p && j != s[p]) p = fail[p];
			if(j == s[p]) p++;
			cnt++;
			if(p == s.size()){
				cout << cnt << endl;
				return 0;
			}
		}
	}
	lint ret = 0;
	if(s[0] == '0') ret += (1ll << n);
	for(int i=0; i<n; i++){
		if(s[i] == '1') ret += (1ll << (n-i-1));
	}
	lint fu = hap(ret);
	for(int i=0; i+1<n; i++){
		vector<string> ret = {s.substr(0, i+1), s.substr(i+1, n-i-1)};
		fu = min(fu, solve2(ret));
		for(int j=i+1; j+1<s.size(); j++){
			vector<string> ret = {s.substr(0, i+1), s.substr(i+1, j-i), s.substr(j+1, n-j-1)};
			fu = min(fu, solve(ret));
			for(int k=j+1; k+1<s.size(); k++){
				vector<string> ret = {s.substr(0, i+1), s.substr(i+1, j-i), s.substr(j+1, k-j), s.substr(k+1, n-k-1)};
				fu = min(fu, solve(ret));
				for(int l=k+1; l+1<n; l++){
					vector<string> ret = {s.substr(0, i+1), s.substr(i+1, j-i), s.substr(j+1, k-j), s.substr(k+1, l-k), s.substr(l+1, n-l-1)};
					fu = min(fu, solve(ret));
				}
			}
		}
	}
	cout << fu;
}
