#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

bool cmp(string a, string b){
	if(a.size() != b.size()) return a.size() < b.size();
	return a < b;
}

struct par{
	string s, t;
	bool operator<(const par &p)const{
		return cmp(t, p.t);
	}
}a[MAXN];

string s;
int n; 
char buf1[1005], buf2[1005];

string sub(string s, string t){
	reverse(s.begin(), s.end());
	reverse(t.begin(), t.end());
	for(int i=0; i<t.size(); i++){
		s[i] -= t[i] - '0';
		if(s[i] < '0'){
			s[i] += 10;
			s[i+1] -= 1;
		}
	}
	for(int i=t.size(); i<s.size(); i++){
		if(s[i] < '0'){
			s[i] += 10;
			s[i+1] -= 1;
		}
	}
	while(s.size() > 1 && s.back() == '0') s.pop_back();
	reverse(s.begin(), s.end());
	return s;
}

int main(){
	cin >> n >> s;
	for(int i=0; i<n; i++){
		scanf("%s %s", buf1, buf2);
		a[i].s = buf1;
		a[i].t = buf2;
	}
	sort(a, a + n);
	vector<string> dap;
	for(int i=n-1; i>=0; i--){
		if(cmp(s, a[i].t)) continue;
		s = sub(s, a[i].t);
		dap.push_back(a[i].s);
	}
	if(s != "0") dap.clear();
	cout << dap.size() << endl;
	for(auto &i : dap) cout << i << endl;
}
