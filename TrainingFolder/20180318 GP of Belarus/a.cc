#include<bits/stdc++.h>
using namespace std;
typedef long long lint;
const lint inf = 2e18;

const int mod = 1e9 + 7;

lint d1[505][505];
lint d2[10][1000005];
lint pwr[1000005];

lint Do(int n, int i, lint k){
	if(n == 0) return 0;
	if(d1[n-1][i] >= k){
		return Do(n-1, i, k);
	}
	return Do(n-1, i-1, k - d1[n-1][i]) + pwr[n-1];
}

using namespace std;
long long nCk(long long n, long long k)
{
    if(n < k) return 0;
    __int128 ans = 1;
    for(int i=1; i<=k; ++i)
    {
        ans *= n-i+1;
        ans /= i;
    }
    return ans;
}


bool nCksafe(long long n, long long k, long long x = inf)
{
    if(n < k) return true;
    if(k > n-k) k = n-k;
    __int128 ans = 1;
    for(int i=1; i<=k; ++i)
    {
        ans *= n-i+1;
        ans /= i;
        if(ans>x) return false;
    }
    return true;
}

lint ipow(lint x, lint p){
    lint ret = 1, piv = x;
    while(p){
        if(p & 1) ret = ret * piv;
        piv = piv * piv;
        ret %= mod;
        piv %= mod;
        p >>= 1;
    }
    return ret;
}

lint query(lint n, lint k){
    if(n==0)
    {
        if(k!=1) return -1;
        else return 0;
    }
    
	if(n <= 500){
		for(int i=0; i<=n; i++){
			if(k <= d1[n][i]){
				return Do(n, i, k) % mod;
			}
			k -= d1[n][i];
		}
		return -1;
	}
	if(n <= 1000000){
		for(int i=0; ; i++){
			if(k <= d2[i][n]){
				lint ans = 0;
				for(int j=i; j; j--){
					int s = 0, e = n;
					while(s != e){
						int m = (s+e+1)/2;
						if(d2[j][m] < k) s = m;
						else e = m-1;
					}
					k -= d2[j][s];
					ans += ipow(2, s);
					n = s;
				}
				return ans % mod;
			}
			k -= d2[i][n];
		}
	}
	
	for(int i=0; ; i++){
	    if(!nCksafe(n, i) || k <= nCk(n, i)){
	        lint ans = 0;
	        for(int j=i; j; j--){
	            lint s = 0, e = n;
	            while(s != e){
	                lint m = (s+e+1)/2;
	                if(nCksafe(m, j) && nCk(m, j) < k) s = m;
	                else e = m-1;
	            }
	            k -= nCk(s, j);
	            ans += ipow(2, s);
	            n = s;
	        }
	        return ans % mod;
	    }
	    k -= nCk(n, i);
	}
}

pair<lint, lint> f(lint x){
    lint newx = max(1LL, (long long)((sqrt(8*x+1)-1)/2 - 3));
    while(newx*(newx+1)/2 < x) ++newx;
    --newx;
    lint A = newx + 1;
    lint B = newx - (x - newx*(newx+1)/2) + 1;
    //printf("<%lld %lld>\n", A, B);
    lint offset = (ipow(2, A) - ipow(2, B) + mod)%mod;
    return make_pair(max(0LL, B-1), offset);
}

int main(){
	for(int i=0; i<505; i++){
		d1[i][0] = 1;
		for(int j=1; j<=i; j++){
			d1[i][j] = min(d1[i-1][j-1] + d1[i-1][j], inf);
		}
	}
	pwr[0] = 1;
	for(int i=0; i<1000005; i++){
		if(i) pwr[i] = (pwr[i-1] << 1) % mod;
		d2[0][i] = 1;
		for(int j=1; j<10 && j<=i; j++){
			d2[j][i] = min(d2[j-1][i-1] + d2[j][i-1], inf);
		}
	}
	int tc;
	cin >> tc;
	while(tc--){
		lint n, k;
		scanf("%lld %lld",&n,&k);
		lint _n, offset;
		tie(_n, offset) = f(n);
		long long ans = query(_n, k);
		if(ans != -1) ans = (ans+offset)%mod;
		printf("%lld\n", ans);
	}
}
