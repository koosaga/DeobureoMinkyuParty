#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

lint w, tot;

int main(){
	int n;
	scanf("%lld %d",&w,&n);
	while(n--){
		int x, y;
		scanf("%d %d",&x,&y);
		tot += 1ll * x * y;
	}
	printf("%lld\n", tot / w);
}
