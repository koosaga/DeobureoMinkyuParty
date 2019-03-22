#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

#define left asd
#define right asdf

using lint = long long;

int n, m;
int hp[150];
int rev[150];

int _pref[150];
int *pref = _pref + 10;

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		int h, s; scanf("%d%d", &s, &h);
		hp[s-1] = h;
		rev[s-1] = i+1;
	}

	for(int i = 0; i < n; i++) {
		pref[i] = pref[i-1] + (rev[i] > 0);
	}

	vector<int> a_(n);
	for(int i = 0; i < n; i++) {
		scanf("%d", &a_[i]);
	}

	for(int x = 0; x < n; x++) {
		
		auto go = [&a_](int l, int r) {
			vector<int> a = a_;

			vector<int> ord;
			vector<bool> used(n);
			for(int i = 0; i < n; i++) {
				if(l <= i && i < r) continue;
				if(r < i && i <= l) continue;
				used[i] = true;
			}

			while(true) {
				int p = -1;
				for(int i = l; i != r; ) {
					if(!used[i] && hp[i] > 0) {
						int tot = hp[i];
						bool good = true;
						for(int j = i; j != l; j += (l < r) ? -1 : 1) {
							tot += a[j];
							if(tot < 0) good = false;
						}
						tot += a[l];
						if(tot < 0) good = false;
						if(good) p = i;
					}	
					if(l < r) i++; else i--;
				}

				if(p == -1) {
					break;
				}

				for(int i = p; i >= 0 && i < n && !used[i]; ) {
					used[i] = true;
					a[i] = 0;
					if(rev[i]) ord.push_back(i);
					if(l < r) i--; else i++;
				}
			}
			return ord;
		};

		{
			vector<int> t = go(x, -1);
			if(t.size() == pref[x] && pref[x] > 0) {
				int tmp = a_[x];
				a_[x] = 0;
				vector<int> u = go(x, n);
				a_[x] = tmp;
				if(u.size() == m - pref[x-1]) {
					printf("%d\n", x+1);
					vector<bool> used(n);
					for(int i : t) if(!used[i]) used[i]=true, printf("%d ", rev[i]);
					for(int i : u) if(!used[i]) used[i]=true, printf("%d ", rev[i]);
					return 0;
				}
			}
		}

		{
			vector<int> t = go(x, n);
			if(t.size() == pref[x] && pref[x] > 0) {
				int tmp = a_[x];
				a_[x] = 0;
				vector<int> u = go(x, -1);
				a_[x] = tmp;
				if(u.size() == m - pref[x-1]) {
					printf("%d\n", x+1);
					vector<bool> used(n);
					for(int i : t) if(!used[i]) used[i]=true, printf("%d ", rev[i]);
					for(int i : u) if(!used[i]) used[i]=true, printf("%d ", rev[i]);
					return 0;
				}
			}
		}

	}

	puts("-1");

	return 0;
}