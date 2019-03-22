#include<cstdio>
#include<algorithm>
#include<vector>
#define N_ 201000
using namespace std;
int n, Dep[N_];
vector<int>E[N_];
void DFS(int a){
	for(auto &x : E[a]){
		Dep[x]=Dep[a]+1;
		DFS(x);
	}
}
void Solve(){
	double p;
	scanf("%d%lf",&n,&p);
	int i, a, b;
	for(i=1;i<=2*n;i++)E[i].clear();
	for(i=1;i<n;i++){
		scanf("%d%d",&a,&b);
		E[n+i].push_back(a);
		E[n+i].push_back(b);
	}
	DFS(2*n-1);
	if(p<1e-9 || p > 1-(1e-9)){
		for(i=1;i<=n;i++){
			printf("%d ",i);
		}
		puts("");
	}
	else{
		int Mn = 1e9;
		for(i=1;i<=n;i++)Mn = min(Mn, Dep[i]);
		for(i=1;i<=n;i++)if(Mn==Dep[i])printf("%d ",i);
		puts("");
	}
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		Solve();
	}
}