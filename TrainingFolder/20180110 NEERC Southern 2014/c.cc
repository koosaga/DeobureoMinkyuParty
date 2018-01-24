#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300005;
typedef pair<int, int> pi;

vector<int> gph[MAXN];
vector<pair<string, string>> seq[MAXN];
int n, din[MAXN], dout[MAXN], piv;

void dfs(int x){
	din[x] = ++piv;
	for(auto &i : gph[x]){
		dfs(i);
	}
	dout[x] = piv;
}

struct value{
	string a;
	int s, e;
	string b;
	bool operator<(const value &v)const{
		return make_tuple(a, s, -e) < make_tuple(v.a, v.s, -v.e);
	}
};

char buf[50];

void debug(value v){
//	printf("%s %d %d %s\n", v.a.c_str(), v.s, v.e, v.b.c_str());
}

pair<string, string> readval(){
	scanf("%s", buf);
	pair<string, string> ret;
	for(int i=0; buf[i]; i++){
		if(buf[i] == '='){
			for(int j=0; j<i; j++) ret.first.push_back(buf[j]);
			for(int j=i+1; buf[j]; j++) ret.second.push_back(buf[j]);
		}
	}
	return ret;
}

bool in(value &a, value &b){
	return a.s <= b.s && b.e <= a.e;
}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int p, s;
		scanf("%d %d",&p,&s);
		if(p) gph[p].push_back(i);
		seq[i].resize(s);
		for(auto &j : seq[i]){
			j = readval();
		}
	}
	dfs(1);
	vector<value> v, w;
	for(int i=1; i<=n; i++){
		for(auto &j : seq[i]){
			v.push_back({j.first, din[i], dout[i], j.second});
		}
	}
	sort(v.begin(), v.end());
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[i].a == v[e].a) e++;
		stack<value> stk;
		int last = -1e9;
		int s = w.size();
		for(int j=i; j<e; j++){
			debug(v[j]);
			while(!stk.empty() && !in(stk.top(), v[j])){
				if(last < stk.top().e){
					w.push_back({stk.top().a, last + 1, stk.top().e, stk.top().b});
					
					last = stk.top().e;
				}
				stk.pop();
			}
			if(last < v[j].s - 1){
				if(!stk.empty()) w.push_back({stk.top().a, last + 1, v[j].s - 1, stk.top().b});
				last = v[j].s - 1;
			}
			stk.push(v[j]);
		}
		while(!stk.empty()){
			if(last < stk.top().e){
				w.push_back({stk.top().a, last + 1, stk.top().e, stk.top().b});
				last = stk.top().e;
			}
			stk.pop();
		}
//	puts("NEXT");
//		while(s < w.size()) debug(w[s++]);
	//	puts("END");
		i = e;
	}
	v = w;
	int q;
	scanf("%d",&q);
	while(q--){
		int vtx;
		scanf("%d %s",&vtx, buf);
		string tmp = buf;
		auto l = upper_bound(v.begin(), v.end(), (value){tmp, din[vtx], -987654321, ""});
		if(l == v.begin()){
			puts("N/A");
			fflush(stdout);
			continue;
		}
		l--;
		if(l->a != tmp || !(l->s <= din[vtx] && din[vtx] <= l->e)){
			puts("N/A");
			fflush(stdout);
		}
		else{
			printf("%s\n", l->b.c_str());
			fflush(stdout);
		}
	}
}

