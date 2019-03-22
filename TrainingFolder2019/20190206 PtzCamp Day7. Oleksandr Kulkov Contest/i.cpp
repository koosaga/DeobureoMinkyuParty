#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;

int n;
char str[MAXN];
int fresh[MAXN]; // [0, i] ~ [fresh[i], i] is newly discovered distinct string

bool inside(int l, int r, int l2, int r2){
	string s(str + l, str + r);
	string t(str + l2, str + r2);
	if(t.find(s) != string::npos) return 1;
	return 0;
}

int cnt[MAXN];

int main(){
	scanf("%s", str);
	n = strlen(str);
	for(int i=0; i<n; i++){
		int ptr = i;
		while(inside(ptr, i + 1, 0, i)) ptr--;
		fresh[i] = ptr;
	}
	unsigned long long distinct = 0;
	unsigned long long ret = 0;
	for(int i=0; i<n; i++){
		printf("%d %d\n", i, fresh[i]);
		distinct += fresh[i] + 1;
		for(int j=0; j<=i; j++) cnt[j]++;
		// move anchor
		if(fresh[i] < i){
			int k = i - 1;
			while(!inside(fresh[i] + 1, i + 1, k+1-(i-fresh[i]), k+1)) k--; 
			for(int j=k-(i-fresh[i])+1; j<=k; j++) cnt[j]--;
		}
		for(int j=0; j<=fresh[i]; j++){
			ret += 1ll * (j+1) * cnt[j];
		}
		for(int j=fresh[i] + 1; j<=i; j++){
			ret += 1ll * (fresh[i] + 1) * cnt[j];
		}
	}
	cout << distinct << endl;
	cout << ret << endl;
	ret -= distinct;
	ret = distinct * (distinct - 1) / 2 -  ret;
	cout << ret << endl;
}
