#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;

using lint = long long;
namespace MR
{
    lint mul(lint a, lint b, lint p)
    {
        return (__int128)a*b%p;
    }
    lint ipow(lint x, lint y, lint p)
    {
        lint ret = 1, piv = x % p;
        while(y)
        {
            if(y&1) ret = mul(ret, piv, p);
            piv = mul(piv, piv, p);
            y >>= 1;
        }
        return ret;
    }
    bool MR(lint x, lint a)
    {
        if(x%a==0) return 0;
        lint d = x-1;
        while(1)
        {
            lint tmp = ipow(a, d, x);
            if(d&1) return (tmp != 1 && tmp != x-1);
            else if(tmp==x-1) return 0;
            d >>= 1;
        }
    }
    bool isPrime(lint x)
    {
        for(auto &i: {2,3,5,7,11,13,17,19,23,29,31,37})
        {
            if(x==i) return 1;
            if(x>40 && MR(x, i)) return 0;
        }
        if(x<=40) return 0;
        return 1;
    }
}
namespace PR
{
    lint f(lint x, lint n, lint c)
    {
        return (c+MR::mul(x, x, n))%n;
    }
    void rec(lint n, vector<lint> &v)
    {
        if(n==1) return;
        if(n%2==0)
        {
            v.push_back(2);
            rec(n/2, v);
            return;
        }
        if(MR::isPrime(n))
        {
            v.push_back(n);
            return;
        }
        lint a, b, c;
        while(1)
        {
            a = rand()%(n-2)+2;
            b = a;
            c = rand()%20 + 1;
            do
            {
                a = f(a,n,c);
                b = f(f(b, n, c), n, c);
            }while(__gcd(abs(a-b),n)==1);
            if(a!=b) break;
        }
        lint x = __gcd(abs(a-b), n);
        rec(x, v);
        rec(n/x, v);
    }
    vector<lint> factorize(lint n)
    {
        vector<lint> ret;
        rec(n, ret);
        sort(ret.begin(), ret.end());
        return ret;
    }
}

typedef pair<lint, lint> pi;

vector<pi> factors;
vector<pi> nfct;
vector<lint> dvs;
lint dp1[111111];
lint dp2[111111];
lint pwr[111111];

int nxt[111111][60];

void bktk(int x, lint v){
	if(x == factors.size()) dvs.push_back(v);
	else{
		for(int i=0; i<=factors[x].second; i++){
			bktk(x + 1, v);
			v *= factors[x].first;
		}
	}
}

pi bktk2(int x, lint v){
	if(x == nfct.size()){
		auto l = lower_bound(dvs.begin(), dvs.end(), v) - dvs.begin();
		return pi(dp1[l], dp2[l]);
	}
	pi ans(0, 0);
	for(int i=0; i<=nfct[x].second; i++){
		auto k = bktk2(x + 1, v);
		v *= nfct[x].first;
		ans.first += k.first;
		ans.second += k.second;
	}
	return ans;
}

int main(){
	srand(time(0));
    lint n;
    cin >> n;
    pwr[0] = 1;
    for(int i=1; i<111111; i++) pwr[i] = (pwr[i-1] << 1) % mod;
    auto x = PR::factorize(n);
    for(int i=0; i<x.size(); ){
    	int e = i;
    	while(e < x.size() &&x[e] == x[i]){
    		e++;
		}
		factors.push_back(pi(x[i], e - i));
		i = e;
	}
	bktk(0, 1);
	sort(dvs.begin(), dvs.end());
	memset(nxt, -1, sizeof(nxt));

	for(int i=0; i<dvs.size(); i++){
		for(int j=0; j<factors.size(); j++){
			if(dvs[i] > n / factors[j].first) continue;
			if(n % (dvs[i] * factors[j].first)) continue;
			auto l = lower_bound(dvs.begin(), dvs.end(), dvs[i] * factors[j].first);
			nxt[i][j] = l - dvs.begin();
		}
	}
	dp1[0] = dp2[0] = 1;
	int exp = 0;
	for(int i=1; i<dvs.size(); i++){
		lint x = dvs[i];
		nfct.clear();
		vector<int> v = {0};
		for(int j=0; j<factors.size(); j++){
			int cnt = 0;
			while(x % factors[j].first == 0){
				x /= factors[j].first;
				cnt++;
			}
			int cur = v.size();
			for(int i=1; i<=cnt; i++){
				for(int k=0; k<cur; k++){
					v.push_back(nxt[v[(i - 1) * cur + k]][j]);
				}
			}	
		}
		for(auto &j : v){
			if(i==j)continue;
			dp1[i] += dp1[j];
			dp2[i] += dp2[j];
		}
		dp1[i] = mod - dp1[i] % mod + pwr[v.size()] - 1;
		dp2[i] = mod - dp2[i] % mod + dp1[i];
		dp1[i] %= mod;
		dp2[i] %= mod;
	}
	cout << dp2[dvs.size() - 1]<<endl;
}
