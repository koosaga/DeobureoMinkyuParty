#include <bits/stdc++.h>

using namespace std;

int gcd (int a, int b) {
	return b ? gcd(b, a%b) : a;
}

using llf = __float128;// long double;

using base = complex<llf>;

void fft(vector<base> &a, bool inv) {
	int n = a.size(), j = 0;
	vector<base> roots(n/2);
	for(int i = 1; i < n; i++) {
		int bit = n>>1;
		while(j >= bit) {
			j -= bit;
			bit >>= 1;
		}
		j += bit;
		if(i < j) swap(a[i], a[j]);
	}

	llf ang = 2 * acosl(-1) / n * (inv ? -1 : 1);
	for(int i = 0; i < n/2; i++) {
		roots[i] = base(cosl(ang * i), sinl(ang * i)); // Todo need to reduce time using log n
	}

	for(int i = 2; i <= n; i <<= 1) {
		int step = n / i;
		for(int j = 0; j < n; j += i) {
			for(int k = 0; k < i/2; k++) {
				base u = a[j+k], v = a[j+k+i/2] * roots[step * k];
				a[j+k] = u+v;
				a[j+k+i/2] = u-v;
			}
		}
	}

	if(inv) {
		for(int i = 0; i < n; i++) a[i] /= n;
	}
}

vector<base> multiply(vector<base>&v, vector<base> &w) {
	vector<base> ret(v.size() + w.size() + 1);
	for(int i = 0; i < v.size(); i++) {
		for(int j = 0; j < w.size(); j++) {
			ret[i + j] += v[i] * w[j];
		}
	}
	return ret;
	/*
	vector<base> fv = v, fw = w;
	int n = 2; while(n < v.size() + w.size()) n <<= 1;
	fv.resize(n); fw.resize(n);
	fft(fv, 0); fft(fw, 0);
	for(int i = 0; i < n; i++) fv[i] *= fw[i];
	fft(fv, 1);
	return fv;*/
}

vector<int> get_PHI (int n) {
	llf ang = 2 * acosl(-1) / n;

	vector<base> now(1, base(1, 0));
	int cnt = 1;
	for(int i = 1; i <= n; i++) {
		if(gcd(n, i) == 1) {
			//printf(">> %d %d %ld\n", n,i, now.size());
			vector<base> hang;
			hang.push_back(-base(cosl(ang * i), sinl(ang * i)));
			hang.push_back(base(1, 0));
			now = multiply(now, hang);
			now.resize(++cnt);
		}
	}
	vector<int> ret(now.size());
	for(int i = 0; i < now.size(); i++) {
		ret[i] = round(now[i].real());
		/*if(fabs(now[i].imag()) < 1e-5) {
			printf("?? %.10Lf\n", fabs(now[i].imag()));
		}*/
		assert(fabs(now[i].imag()) < 1e-4);
	}
	return ret;
}

int main() {
	for(int n = 1; n <= 200; n++) {
		vector<int> ans = get_PHI(n);
		printf("PHI(%d):\n", n);
		printf("  prime factorzation: ");
		for(int i = 2, t = n; i <= n; i++) {
			int jisu = 0;
			while(t % i == 0) {
				t /= i;
				jisu += 1;
			}
			if(jisu > 0) {
				printf(" * %d^%d", i, jisu);
			}
		}

		printf("\n  coef 1: ");
		int c0=0, c1=0;
		for(int i = ans.size(); --i >= 0; ) {
			if(ans[i] == 1) {
				printf("%d ", i);
				c0++;
			}
		}
		printf("\n  coef -1: ");
		for(int i = ans.size(); --i >= 0; ) {
			if(ans[i] == -1) {
				printf("%d ", i);
				c1++;
			}
		}
		printf("\n  divisors: ");
		for(int i = n; i >= 1; i--) {
			if(n % i == 0) {
				printf("%d ", i);
			}
		}
		printf("\n  >> # of coef: %d, %d", c0, c1);

		printf("\n  ");
		for(int i = ans.size(); --i >= 0; ) {
			if(ans[i] != 0) {
				//printf("(%d, %d)", i, ans[i]);
				if(ans[i] == 1) putchar('+');
				else if(ans[i] > 0) printf("+%d", ans[i]);
				else if(ans[i] == -1) putchar('-');
				else printf("%d", ans[i]);

				if(i > 0)
				printf(" x^%d",i);
				else if(abs(ans[i]) == 1) putchar('1'); 
				printf(" ");
			}
		}
		puts("");
	}
	return 0;
}
