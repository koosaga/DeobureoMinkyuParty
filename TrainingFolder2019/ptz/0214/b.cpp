#include<cstdio>
#include<algorithm>
using namespace std;

int n;
long long K, Res[101000];
int w[101000];

struct Frac{
    long long a, b;
    int num;
    bool operator<(const Frac &p)const{
        return a*p.b < p.a*b;
    }
}U[201000];

void Solve(){
	int i, j;
	scanf("%d%lld",&n,&K);
	for(i=1;i<=n;i++){
		scanf("%d",&w[i]);
	}
	long double b = 0.0L, e = 1.1e9L, mid, r = 0.0L;
	for(i=0;i<300;i++){
		mid = (b+e)*0.5L;
		long long s = 0;
		for(j=1;j<=n;j++){
			s += (long long)(w[j]/mid);
		}
		if(s >= K){
			r = mid;
			b = mid;
		}
		else e = mid;
	}
    int cnt = 0;
    long long ss =0;
    for(i=1;i<=n;i++){
        long long t = (long long)(w[i]/r);
        Res[i] = 0;
        if(t){
            U[cnt++] = {w[i],t, i};
            ss += t-1;
            Res[i] = t-1;
        }
        U[cnt++] = {w[i],t+1, i};
    }
    sort(U,U+cnt);
    for(i=cnt-1;i>=0 && ss < K;i--){
        for(j=i;j>=0;j--){
            if(U[j]<U[i])break;
            ss++;
            Res[U[j].num]++;
        }
        i = j+1;
    }
    for(i=1;i<=n;i++)printf("%lld ",Res[i]);
    puts("");
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		Solve();
	}
}

