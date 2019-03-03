#include <bits/stdc++.h>

using namespace std;

const int AL = 1, BL = -1;

int cmp(vector<int> a, vector<int> b) {
	#define a1 a[0]
	#define a2 a[1]
	#define a3 a[2]
	#define b1 b[0]
	#define b2 b[1]
	#define b3 b[2]

	if(a.size() > b.size()) {
		return -cmp(b, a);
	}

	while(!a.empty() && !b.empty() && a.front() == b.front()) {
		a.erase(a.begin());
		b.erase(b.begin());
	}
	if(a.size() == b.size()) {
		while(!a.empty() && !b.empty() && a.back() == b.back()) {
			a.pop_back();
			b.pop_back();
		}
	}

	if(a.empty() && b.empty()) {
		return 0;
	}
	if(!a.empty() && b.empty()) {
		return AL;
	}
	if(a.empty() && !b.empty()) {
		return BL;
	}


	if(a.size() == 1 && b.size() == 1) {
		return a < b ? AL : (a == b ? 0 : BL);
	}
	if(a.size() == 1 && b.size() == 2) {
		if(a1 + 1 >= min(b2, b1+1)) {
			return BL;
		}
		return AL;
	}
	if(a.size() == 1 && b.size() == 3) {
		if(a1 + 2 >= min({b3, b2+1, b1+2})) {
			return BL; // hypo
		}
		return AL;
	}
	if(a.size() == 2 && b.size() == 2) {
		int va = min(a2, a1+1);
		int vb = min(b2, b1+1);
		if(va != vb) {
			return va < vb ? AL : BL;
		}
		int ra = a2 + (a1+1) - va;
		int rb = b2 + (b1+1) - vb;
		if(ra == rb) {
			return 0;
		}
		return ra < rb ? AL : BL;
	}
	if(a.size() == 2 && b.size() == 3) {
		int va = min(a2+1, a1+2);
		int vb = min({b3, b2+1, b1+2});
		if(va != vb) {
			return va < vb ? AL : BL;
		}

		if(vb == b1 + 2) {
			int ua = a2+1 + a1+2 - va;
			int ub = min(b3, b2+1);
			return ua < ub ? AL : BL;
		}

		return BL;
	}
	if(a.size() == 3 && b.size() == 3) {
		int va = min({a3, a2+1, a1+2});
		int vb = min({b3, b2+1, b1+2});
		if(va != vb) {
			return va < vb ? AL : BL;
		}

		if(va == a1+2 && vb == b1+2) {
			int ua = min(a3, a2+1);
			int ub = min(b3, b2+1);
			if(ua != ub) {
				return ua < ub ? AL : BL;
			}
			int wa = a3 + (a2+1) - ua;
			int wb = b3 + (b2+1) - ub;
			if(wa == wb) {
				return 0;
			}
			return wa < wb ? AL : BL;
		}

		if(vb == b1+2) {
			return -cmp(b, a);
		}


		if(va == a3 || va == a2+1) {
			int ua = a3 + (a2+1) - va;
			int ub = b3 + (b2+1) - vb;
			if(ua != ub) {
				return ua < ub ? AL : BL;
			}

			int wa = a1+2;
			int wb = b1+2;
			if(wa == wb) {
				return 0;
			}
			return wa < wb ? AL : BL;
		}

		if(va == a1+2) {
			
			return BL;
		}
	}


	assert(false);
}

vector<int> read_vector(int n) {
	vector<int> ret(n);
	for(int &x : ret) scanf("%d", &x);
	return ret;
}

void solve()
{
	int an, bn;
	scanf("%d%d", &an, &bn);
	vector<int> a = read_vector(an);
	vector<int> b = read_vector(bn);
	/*for(int x : a) printf("%d ", x);printf(",");
	for(int x : b) printf("%d ", x);puts("");
*/
	if(a == b) {
		puts("0");
		return;
	}

	printf("%d\n", cmp(a, b));
}

int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
		solve();
	return 0;
}