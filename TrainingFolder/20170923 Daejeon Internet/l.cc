#include<bits/stdc++.h>
using namespace std;
typedef complex<double> base;
void fft(vector<base>&a, bool inv)
{
	int n = a.size(), j = 0;
	vector<base> roots(n/2);
	for(int i=1; i<n; ++i)
	{
		int bit = (n>>1);
		while(j>=bit)
		{
			j-=bit;
			bit>>=1;
		}
		j+=bit;
		if(i<j) swap(a[i], a[j]);
	}
	double ang = 2 * acos(-1) / n * (inv ? -1 : 1 );
	for(int i=0; i<n/2; ++i)
	{
		roots[i] = base(cos(ang*i), sin(ang*i));
	}
	for(int i=2; i<=n; i<<=1)
	{
		int step = n/i;
		for(int j=0; j<n; j += i)
		{
			for(int k=0; k<i/2; ++k)
			{
				base u = a[j+k], v = a[j+k+i/2]*roots[step*k];
				a[j+k] = u+v;
				a[j+k+i/2] = u-v;
			}
		}
	}
	if(inv) for(int i=0; i<n; ++i) a[i] /= n;
}	
using lint = long long;
vector<lint> multiply(vector<lint> &v, vector<lint> &w)
{
	vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
	int n=1; while(n<max(v.size(), w.size())) n<<=1;
	n<<=1; fv.resize(n); fw.resize(n);
	fft(fv, 0); fft(fw, 0); for(int i=0; i<n; ++i) fv[i]*=fw[i];
	fft(fv, 1); vector<lint> ret(n);
	for(int i=0; i<n; ++i) ret[i] = (lint)round(fv[i].real());
	return ret;
}
int n, l, m;
long long w;
vector<long long> a1[10101];
vector<long long> a2[10101];
vector<long long> res[10101];
int main()
{
	scanf("%d%d%d%lld",&n,&m,&l,&w);
	for(int i=0; i<l; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			int t; scanf("%d", &t);
			a1[i].push_back((long long)t);
		}
	}
	for(int i=0; i<l; ++i)
	{
		for(int j=0; j<m; ++j)
		{
			int t; scanf("%d", &t);
			a2[i].push_back((long long)t);
		}
		reverse(a2[i].begin(), a2[i].end());
	}
	
	for(int i=0; i<l; ++i)
	{
		res[i] = multiply(a1[i], a2[i]);
	}
	int ans = 0;
	for(int i=m-1; i<=n-1; ++i)
	{
		long long W = 0;
		for(int j=0; j<l; ++j)
		{
			W += res[j][i];
		}
		if(W>w) ans++;
	}
	printf("%d\n", ans);
	return 0;
}















