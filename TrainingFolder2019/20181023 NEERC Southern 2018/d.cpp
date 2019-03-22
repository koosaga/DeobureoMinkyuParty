#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

int n, k;

int main(){
scanf("%d%d" , &n,&k);

long long ans = 0;
long long must = 0;
long long may = 0;
for(int i = 0; i < n; i++) {
scanf("%lld", &may);
long long x = (must + k - 1) / k;
ans += x;
must += may;
must -= x * k;
must = max(must, 0ll);
}
ans += (must + k - 1) / k;
printf("%lld\n", ans);
return 0;
}
