#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;

int n, a[MAXN];
int l[MAXN], r[MAXN];
int par[MAXN];
int low[10000005], las[10000005];

bool solve(int s, int e, int x){
	if(s > e) return true;
	int p1 = s, p2 = e;
	int rt = -1;
	while(p1 <= p2){
		if(l[p1] < s && r[p1] > e){
			rt = p1;
			break;
		}
		p1++;
		if(p1 > p2) break;
		if(l[p2] < s && r[p2] > e){
			rt = p2;
			break;
		}
		p2--;
	}
	if(rt == -1) return false;
	par[rt] = x;
	if(!solve(s, rt-1, rt) || !solve(rt+1, e, rt)) return false;
	return true;
}

int main(){
	for(int i=2; i<=10000000; i++){
		for(int j=i; j<=10000000; j+=i){
			if(!low[j]) low[j] = i;
		}
	}
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	for(int i=1; i<=n; i++){
		for(int j=a[i]; j!=1; j/=low[j]){
			l[i] = max(l[i], las[low[j]]);
		}
		for(int j=a[i]; j!=1; j/=low[j]){
			las[low[j]] = i;
		}
	}
	memset(las, 0x3f, sizeof(las));
	for(int i=n; i; i--){
		r[i] = 1e9;
		for(int j=a[i]; j!=1; j/=low[j]){
			r[i] = min(r[i], las[low[j]]);
		}
		for(int j=a[i]; j!=1; j/=low[j]){
			las[low[j]] = i;
		}
	}
	if(!solve(1, n, 0)) puts("impossible");
	else for(int i=1; i<=n; i++) printf("%d ", par[i]);
}
