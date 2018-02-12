#include<bits/stdc++.h>
using namespace std;

int a[3], b[3];
long long c[3];

int main(){
	int n;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x; scanf("%d",&x);
		a[i%3] += x;
	}
	for(int i=0; i<n; i++){
		int x; scanf("%d",&x);
		b[i%3] += x;
	}
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			c[(i+j+2)%3] += 1ll * a[i] * b[j];
		}
	}
	printf("%lld %lld %lld\n", c[0], c[1], c[2]);
}
