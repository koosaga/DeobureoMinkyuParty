#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef pair<int, int> pi;
typedef unsigned long long dat;

struct bs{
	dat a[1563];
	void set(int v){
		a[v >> 6] ^= (1ull << (v & 63));
	}
	int lsb(){
		for(int i=0; i<1563; i++){
			if(a[i]){
				for(int j=0; j<64; j++){
					if((a[i] >> j) & 1){
						return j + 64 * i + 1;
					}
				}
			}
		}
		return -1;
	}
	void clear(){ for(int i=0; i<1563; i++) a[i] = 0; }
	bs operator^(const bs &b)const{
		bs ret;
		for(int i=0; i<1563; i++){
			ret.a[i] = a[i] ^ b.a[i];
		}
		return ret;
	}
};

int n, a[MAXN];

struct seg{
	bs tree[4100];
	int lim;
	void init(int n, int *a){
		for(lim = 1; lim <= 1 + n/64; lim <<= 1);
		for(int j=0; j<n; j++){
			tree[j/64 + lim].set(a[j] - 1);
		}
		for(int j=lim-1; j; j--){
			tree[j] = tree[2*j] ^ tree[2*j+1];
		}
	}
	void set(int x, int v){
		tree[x/64 + lim].set(a[x]-1);
		tree[x/64 + lim].set(v-1);
		a[x] = v;
		x >>= 6;
		x += lim;
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] ^ tree[2*x+1];
		}
	}
	bs query(int l, int r){
		l += lim;
		r += lim;
		bs ret;
		ret.clear();
		while(l < r){
			if(l % 2 == 1) ret = ret ^ tree[l++];
			if(r % 2 == 0) ret = ret ^ tree[r--];
			l >>= 1;
			r >>= 1;
		}
		if(l == r) ret = ret ^ tree[l];
		return ret;
	}
}seg;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d",&a[i]);
	seg.init(n, a);
	while(true){
		int q;
		scanf("%d",&q);
		if(q == 0) break;
		while(q--){
			int t, x, y;
			scanf("%d %d %d",&t,&x,&y);
			if(t == 1){
				seg.set(x - 1, y);
			}
			else{
				int l = x - 1;
				int r = y - 1;
				if(r - l <= 200){
					bs aux;
					aux.clear();
					for(int i=l; i<=r; i++) aux.set(a[i]-1);
					printf("%d\n", aux.lsb());
				}
				else{
					bs aux;
					aux.clear();
					while(l % 64 != 0) aux.set(a[l++] - 1);
					while(r >= 0 && r % 64 != 63) aux.set(a[r--] - 1);
					l = l / 64;
					if(r == -1) r = -1;
					else r = r / 64;
					aux = aux ^ seg.query(l, r);
					printf("%d\n", aux.lsb());
				}
			}
		}
		fflush(stdout);
	}
}
