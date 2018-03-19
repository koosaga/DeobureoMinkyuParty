#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 1000005;

int n, a[MAXN];
int nxt[MAXN];

int fuck(int s, int e, int x){
	return max(e - s + 1 - x + 1, 0);
}

int real_solve(int s, int m, int e, int x){
	return fuck(s, e, x) - fuck(s, m-1, x) - fuck(m+1, e, x);
}

lint solve(){
	deque<int> stk;
	lint ans = 0;
	int curmax = 0;
	for(int i=1; i<=n; i++){
		curmax = max(curmax, nxt[i]);
		while(!stk.empty() && stk.front() <= curmax){
			int previous_record = stk.front();
			stk.pop_front();
			if(stk.size()){
				ans += real_solve(previous_record + 1, stk.front(), i - 1, a[stk.front()]);
			}
		}
		while(!stk.empty() && a[stk.back()] <= a[i]){
			int val = stk.back();
			stk.pop_back();
			if(stk.size()){
				ans += real_solve(stk.back() + 1, val, i - 1, a[val]);
			}
		}
		stk.push_back(i);
		if(a[stk.front()] <= i - curmax) ans++;
	}
	while(stk.size()){
		int val = stk.back();
		stk.pop_back();
		if(stk.size()){
			ans += real_solve(stk.back() + 1, val, n, a[val]);
		}
	}
	return ans;
}

int main(){
	scanf("%d",&n);
	map<int, int> mp;
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		nxt[i] = mp[a[i]];
		mp[a[i]] = i;
	}
	cout << solve() << endl;
}
