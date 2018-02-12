#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 100005;

vector<int> gph[MAXN];
int n, a[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	vector<pi> ed;
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
		ed.emplace_back(s, e);
	}
	vector<int> v;
	for(int i=1; i<=n; i++){
		if(a[i] && gph[i].size() % 2){
			v.push_back(i);
		}
	}
	int tot = n;
	for(int i=1; i<=n; i++) if(gph[i].size() & 1) tot ^= i;
	if(v.size() == 0){
		if(tot == 0){
			printf("%d\n", n);
			for(auto &i : ed) printf("%d %d\n", i.first, i.second);
		}
		else puts("-1");
		return 0;
	}
	if(v.size() == 1){
		int i = v[0];
		int updv = tot ^ i;
		if(updv != i && (1 <= updv && updv <= n)){
			if(a[updv]){
				for(auto &i : ed){
					if(i.first == updv) i.first ^= (1<<28);
					if(i.second == updv) i.second ^= (1<<28);
					if(i.first == v[0]) i.first = updv;
					if(i.second == v[0]) i.second = updv;
				}
				printf("%d\n", n);
				for(auto &i : ed) printf("%d %d\n", i.first, i.second);
				return 0;
			}
			puts("-1");
		}
		else if(updv != 0){
			for(auto &i : ed){
				if(i.first == v[0]) i.first = updv;
				if(i.second == v[0]) i.second = updv;
			}
			printf("%d\n", n);
			for(auto &i : ed) printf("%d %d\n", i.first, i.second);
		}
		else{
			puts("-1");
		}
		return 0;
	}
	if((v[0] ^ v[1]) == tot){
		// fucking problem
		if(v.size() == 2){
			puts("-1");
			return 0;
		}
		swap(v[1], v[2]);
	}
	int updv = tot ^ v[0] ^ (1 << 28);
	for(auto &i : ed){
		if(i.first == v[0]) i.first = updv;
		else if(i.first == v[1]) i.first ^= (1<<28);
		if(i.second == v[0]) i.second = updv;
		else if(i.second == v[1]) i.second ^= (1<<28);
	}
	printf("%d\n", n);
	for(auto &i : ed) printf("%d %d\n", i.first, i.second);
}
