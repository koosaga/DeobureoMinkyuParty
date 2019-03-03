#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 100005;
using pi = pair<int, int>;
const int a[52] = {
	1, 1, 2, 1, 
	0, 0, 1, 1, 
	0, 1, 0, 0, 
	0, 2, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0, 
	0, 0, 0, 0,
	1, 1, 1, 1,
	1, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0};

int n; lint k;
char str[MAXN];
int A[MAXN], B[MAXN], M[MAXN];

auto toi = [](char c){
	if(isupper(c)) return 2 * (c - 'A');
	return 2 * (c - 'a') + 1;
};
auto toa = [](int c){
	if(c % 2) return 'a' + c / 2;
	return 'A' + c / 2;
};

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x < MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
}

pi v1[MAXN], v2[MAXN];
int prefix_min[MAXN], rev[MAXN], chk[MAXN];

void satisfy(int m){ // clear no need
	for(int i=0; i<n; i++){
		v1[i + 1] = pi(A[i], i);
		v2[i + 1] = pi(B[i], i);
	}
	sort(v1 + 1, v1 + n + 1);
	sort(v2 + 1, v2 + n + 1);
	prefix_min[n + 1] = 1e9;
	for(int i=n; i; i--){
		rev[v2[i].second] = i;
		prefix_min[i] = min(M[v2[i].second], prefix_min[i + 1]);
	}
	pi ret(2e9, -1);
	lint running_sum = 0;
	for(int i=0; i<=n && i <= m; i++){
		running_sum += v1[i].first;
		if(i % 2 == m % 2){
			int w = (m - i) / 2;
			int last_pos = 1e9;
			lint total_sum = running_sum;
			for(int j=1; j<=n; j++){
				if(chk[j]) continue;
				w--;
				total_sum += v2[j].first;
				if(w == 0){
					last_pos = j;
					break;
				}
			}
			if(last_pos < 1e8 && total_sum < 2e9) ret = min(ret, pi(total_sum, i));
		}
		else{
			int w = (m - i + 1) / 2;
			int last_pos = 1e9;
			lint total_sum = running_sum;
			for(int j=1; j<=n; j++){
				if(chk[j]) continue;
				w--;
				total_sum += v2[j].first;
				if(w == 0){
					last_pos = j;
					break;
				}
			}
			if(last_pos < 1e8 && total_sum < 2e9){
				total_sum += prefix_min[last_pos + 1];
				ret = min(ret, make_tuple(total_sum, i, last_pos));
			}
		}
		if(i < v1.size()){
			int idx_v2 = rev[v1[i].second];
			chk[idx_v2] = 1;
		}
	}
	memset(chk, 0, sizeof(chk));
	for(int i=1; i<=ret.second; i++) up[v1[i].second] = 1;
	if(ret.second % 2 == m % 2){
		int w = (m - ret.second) / 2;
		for(int i=1; i<=n; i++){
			if(!up[v2[i].second]){
				up[v2[i].second] = 2;

	}
	else{
		int w = (m + 1 - ret.second) / 2;
		for(int i=1; i<=w; i++) if(!up[v2[i].second]) up[v2[i].second] = 2;
	}
}

int main(){
	cin >> n >> k;
	if(k < 0 || k > 2 * n){
		puts("-1");
		return 0;
	}
	int sum = 0;
	scanf("%s", str);
	for(int i=0; i<n; i++){
		sum += a[toi(str[i])];
	}
	if(sum == k){
		cout << "0\n" << str << endl;
		return 0;
	}
	if(sum < k){
		vector<int> v;
		for(int i=0; i<n; i++) v.push_back(toi(str[i]));
		memset(A, 0x3f, sizeof(A));
		memset(B, 0x3f, sizeof(B));
		memset(M, 0x3f, sizeof(M));
		for(int i=0; i<v.size(); i++){
			for(int j=0; j<52; j++){
				if(a[v[i]] - a[(v[i]+j)%52] == -1){
					A[i] = j;
					break;
				}
			}
			for(int j=0; j<52; j++){
				if(a[v[i]] - a[(v[i]+j)%52] == -2){
					B[i] = j;
					break;
				}
			}
			for(int j=0; j<52; j++){
				if(a[v[i]] - a[(v[i]+j)%52] == +1){
					M[i] = j;
					break;
				}
			}
		}
		int need = k - sum;
		satisfy(need);
	}
	else{
		vector<int> v;
		for(int i=0; i<n; i++) v.push_back(toi(str[i]));
		memset(A, 0x3f, sizeof(A));
		memset(B, 0x3f, sizeof(B));
		memset(M, 0x3f, sizeof(M));
		for(int i=0; i<v.size(); i++){
			for(int j=0; j<52; j++){
				if(a[v[i]] - a[(v[i]+j)%52] == +1){
					A[i] = j;
					break;
				}
			}
			for(int j=0; j<52; j++){
				if(a[v[i]] - a[(v[i]+j)%52] == +2){
					B[i] = j;
					break;
				}
			}
			for(int j=0; j<52; j++){
				if(a[v[i]] - a[(v[i]+j)%52] == -1){
					M[i] = j;
					break;
				}
			}
		}
		int need = sum - k;
		satisfy(need);
	}
}
