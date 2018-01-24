#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 3005;
#pragma GCC option("Ofast")
struct pnt{
	int x, y, idx;
	bool operator<(const pnt &a)const{
		return pi(x, y) < pi(a.x, a.y);
	}
	bool operator>(const pnt &a)const{
		return pi(x, y) > pi(a.x, a.y);
	}
}a[MAXN];
vector<pnt> l[MAXN], r[MAXN];
pnt t[MAXN][MAXN];

int n;

int ccw(pnt a, pnt b, pnt c){
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

int dist(pnt a, pnt b){
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void print(pnt x){
	printf("%d %d\n", x.x, x.y);
}

pi nxt[MAXN][MAXN];
int cut[MAXN][MAXN];
int dprk[MAXN][MAXN];

void fuck_communism(){
	for(int p=0; p<n; p++){
		for(int q=0; q<n; q++){
			if(p == q) continue;
			int it = cut[p][q] + 1;
			if(it == n - 1) it = 0;
			it = cut[p][t[p][it].idx-1];
			dprk[p][q] = t[p][it].idx - 1;
		}
	}
}

pi get_rotate(int p, int q){
	return pi(p, dprk[p][q]);
}

void construct_graph(){
	for(int i=0; i<n; i++){
		int ptr = 0;
		for(int j=0; j<l[i].size(); ){
			int e = j;
			while(e < l[i].size() && ccw(a[i], l[i][j], l[i][e]) == 0) e++;
			while(ptr < r[i].size() && ccw(a[i], l[i][j], r[i][ptr]) > 0) ptr++;
			int st = ptr;
			while(ptr < r[i].size() && ccw(a[i], l[i][j], r[i][ptr]) >= 0) ptr++;
			int ed = ptr;
			int sum = (ed - st) + 1 + (e - j);
			pi pos;
			if(ed - st == e - j){
				pos = get_rotate(i, l[i][e-1].idx-1);
			}
			if(ed - st < e - j){
				pos = get_rotate(l[i][j + (e - j) - (ed - st) - 1].idx - 1, i);
			}
			if(ed - st > e - j){
				pos = get_rotate(r[i][st + (ed - st) - (e - j) - 1].idx - 1, i);
			}
			nxt[a[i].idx-1][l[i][e-1].idx-1] = pos;
			j = e;
		}
		ptr = 0;
		for(int j=0; j<r[i].size(); ){
			int e = j;
			while(e < r[i].size() && ccw(a[i], r[i][j], r[i][e]) == 0) e++;
			while(ptr < l[i].size() && ccw(a[i], r[i][j], l[i][ptr]) > 0) ptr++;
			int st = ptr;
			while(ptr < l[i].size() && ccw(a[i], r[i][j], l[i][ptr]) >= 0) ptr++;
			int ed = ptr;
			int sum = (ed - st) + 1 + (e - j);
			pi pos;
			if(ed - st == e - j){
				pos = get_rotate(i, r[i][e-1].idx-1);
			}
			if(ed - st < e - j){
				pos = get_rotate(r[i][j + (e - j) - (ed - st) - 1].idx-1, i);
			}
			if(ed - st > e - j){
				pos = get_rotate(l[i][st + (ed - st) - (e - j) - 1].idx-1, i);
			}
			nxt[a[i].idx-1][r[i][e-1].idx-1] = pos;
			j = e;
		}
	}
}

int vis[MAXN][MAXN];

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].x >> a[i].y;
		a[i].idx = i+1;
	}
	bool good = 0;
	for(int i=2; i<n; i++){
		if(ccw(a[0], a[1], a[i]) != 0) good = 1;
	}
	if(!good){
		sort(a, a+n);
		int p = lower_bound(a, a+n, (pnt){0, 0, 0}) - a;
		int q; cin >> q;
		while(q--){
			int x;
			cin >> x;
			if(x % 2 == 0) print(a[p]);
			else print(a[n-1-p]);
		}
		return 0;
	}
	for(int i=0; i<n; i++){
		int cnt = 0;
		for(int j=0; j<n; j++){
			if(i != j && a[i] < a[j]){
				t[i][cnt++] = a[j];
			}
			else if(i != j){
				pnt x = a[j];
				x.x = 2 * a[i].x - x.x;
				x.y = 2 * a[i].y - x.y;
				t[i][cnt++] = x;
			}
		}
		sort(t[i], t[i] + n - 1, [&](const pnt &x, const pnt &y){
			int t = ccw(a[i], x, y);
			if(t == 0){
				return dist(a[i], x) < dist(a[i], y);
			}
			return t > 0;
		});
		for(int jj=0; jj<n-1; jj++){
			int p = t[i][jj].idx - 1;
			if(a[p] > a[i]) l[i].push_back(a[p]);
			else r[i].push_back(a[p]);
		}
		for(int jj=0; jj<n-1; ){
			int e = jj;
			while(e < n-1 && ccw(a[i], t[i][jj], t[i][e]) == 0) e++;
			for(int j = jj; j < e; j++)
				cut[i][t[i][j].idx - 1] = e-1;
			jj = e;
		}
	}
	fuck_communism();
	construct_graph();
	/*
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			printf("%d %d ", nxt[i][j].first, nxt[i][j].second);
			puts("");
		}
		puts("----");
	}*/
	pi st(-1, -1);
	for(int i=0; i<n; i++){
		if(a[i].x == 0 && a[i].y == 0){
			for(int j=0; j<n-1; j++){
				if(t[i][j].x < 0){
					st.first = i;
					st.second = t[i][j].idx - 1;
				}
			}
			if(st == pi(-1, -1)){
				st.first = i;
				st.second = t[i][0].idx - 1;
			}
		}
	}
	vector<int> seqfirst, seqsecond;
	while(!vis[st.first][st.second]){
		vis[st.first][st.second] = 1;
		auto f = nxt[st.first][st.second];
		if(st.first != f.first){
			seqfirst.push_back(f.first);
		}
		st = f;
	}
	while(vis[st.first][st.second] == 1){
		vis[st.first][st.second] = 0;
		auto f = nxt[st.first][st.second];
		if(st.first != f.first){
			seqsecond.push_back(f.first);
		}
		st = f;
	}
	int q;
	cin >> q;
	int cur = 0;
	while(q--){
		int x;
		cin >> x;
		if(x <= seqfirst.size()) print(a[seqfirst[x-1]]);
		else{
			int p = x - seqfirst.size() - 1;
			p %= seqsecond.size();
			print(a[seqsecond[p]]);
		}
	}
}
