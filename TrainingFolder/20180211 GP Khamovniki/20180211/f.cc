#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
typedef pair<int, int> pi;
char s[MAXN], t[MAXN];
int n, vis[MAXN], func[MAXN];

int prv(int i){
    if(i<=n/2) return 2*i-1;
    return 2*i-n;
}

int fail[MAXN];

pi solve(string s, string t){
	int p = 0;
	int n = s.size();
	for(int i=1; i<n; i++){
		while(p && s[i] != s[p]) p = fail[p];
		if(s[i] == s[p]) p++;
		fail[i + 1] = p;
	}
	t = t + t;
	p = 0;
	vector<int> v;
	for(int i=0; i+1<t.size(); i++){
		while(p && t[i] != s[p]) p = fail[p];
		if(t[i] == s[p]) p++;
		if(p == s.size()){
			v.push_back(i + 1 - n);
			p = fail[p];
		}
	}
	if(v.size() == 0){
		puts("-1");
		exit(0);
	}
	assert(n % v.size() == 0);
	return pi(n / v.size(), v[0]);
}

int ord[MAXN], tmp[MAXN];
int main(){
	scanf("%s %s", s, t);
	n = strlen(s);
	for(int i=1; i<=n; i++){
		func[prv(i)] = i;
	}
	vector<pi> ans;
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			string ns, nt;
			for(int j=i; !vis[j]; j=func[j]){
				ns.push_back(s[j-1]);
				nt.push_back(t[j-1]);
				vis[j] = 1;
			}
			ans.push_back(solve(ns, nt));
		}
	}
	memset(ord, -1, sizeof(ord));
	for(auto &i : ans){
		if(ord[i.first] == -1) ord[i.first] = i.second;
		else if(ord[i.first] != i.second){
			puts("-1");
			return 0;
		}
	}
	int cnt = 0;
	for(int i=1; i<=n; i++){
		if(ord[i] == -1) continue;
		for(int j=ord[i]; j<=n; j+=i) tmp[j]++;
		cnt++;
	}
	for(int i=0; i<=n; i++){
		if(tmp[i] == cnt){
			cout << i << endl;
			return 0;
		}
	}
	cout << -1 << endl;
}

