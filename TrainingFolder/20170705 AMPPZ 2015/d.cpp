#include <bits/stdc++.h>
using namespace std;

int n, m, k, a[250005], b[250005];
long long int ans;

int main(){
    scanf("%d %d %d",&n,&m,&k);
    for(int i=0; i<n; i++) scanf("%d",&a[i]);
    for(int i=0; i<m; i++) scanf("%d",&b[i]);
    sort(b, b+m);
    for(int i=0; i<n; i++){
        ans += upper_bound(b, b+m, a[i] + k) - lower_bound(b, b+m, a[i] - k);
    }
    cout << ans;
}
