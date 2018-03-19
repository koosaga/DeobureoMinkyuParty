#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
using pi = pair<string, int>;

int n, k;
string str[1005];

set<pair<string, int>> s;

int main(){
	cin >> n >> k;
	for(int i=0; i<n; i++){
		cin >> str[i];
		for(int j=0; j+k-1<str[i].size(); j++){
			string sub = str[i].substr(j, k);
			s.insert(make_pair(sub, i));
		}
	}
	string ans;
	while(!s.empty()){
		int sufficient_length = min(k, (int)ans.size() + 1);
		string nxt;
		nxt.push_back('z' + 1);
		for(int i=0; i<sufficient_length; i++){
			string l;
			for(int j=ans.size()-i; j<ans.size(); j++) l.push_back(ans[j]);
			auto it = s.lower_bound(pi(l, -1));
			if(it != s.end()){
				auto x = it->first;
				bool ok = 1;
				for(int j=0; j<i; j++){ if(x[j] != l[j]) ok = 0; }
				if(ok){
					nxt = min(nxt, x.substr(i, k - i));
				}
			}
		}
		ans += nxt;
		string suff;
		for(int i=0; i<k; i++) suff.push_back(ans[ans.size() - k + i]);
		auto it = s.lower_bound(pi(suff, -1));
		vector<int> v;
		while(it != s.end()){
			if(it->first != suff) break;
			v.push_back(it->second);
			it++;
		}
		sort(v.begin(), v.end());
		v.resize(unique(v.begin(), v.end()) - v.begin());
		for(auto &i : v){
			for(int j=0; j+k-1<str[i].size(); j++){
				string sub = str[i].substr(j, k);
				s.erase(make_pair(sub, i));
			}
		}
	}
	cout << ans << endl;
}

