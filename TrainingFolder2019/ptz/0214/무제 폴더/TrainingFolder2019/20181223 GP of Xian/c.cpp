#pragma GCC optimize("Ofast")

#include<bits/stdc++.h>
using namespace std;

using lint = long long;
using ulint = unsigned long long;

const int B = 31622;

const int Z = int(1e9) / 64 + 1;
ulint seq[Z];

const int P = 2000093;
vector<int> pos[P];
bool chk[P];

void print_bit(ulint b) {
	for(int i = 0; i < 64; i++) putchar((b >> i) % 2 + '0');
	printf(" " );
}

string get_200(int x) {
	string ret;
	for(int i = x; i < x+200; i++) ret += char(1 - (seq[i>>6] >> (i & 63)) % 2 + '0');
	return ret;
}

int main() {
	for(int p = 2; p < B; p ++) {
		bool good = true;
		for(int i = 2; good && i * i <= p; i++) if(p % i == 0) good = false;
		if(good) {
        	lint p2 = p*p;
			for(lint i = p2; i <= int(1e9); i += p2) {
				seq[i >> 6] |= (ulint)1 << (i & 63);
			}
		}
	}


	std::string s;
	for(int rep = 0; rep < 10; rep++) {
		static char tmp[50]; scanf("%s", tmp);
		s += tmp;
	}

	ulint t[200];
	for(int i = 0; i < 200; i++) {
		t[i] = 0;
		for(int j = 0; j < 64 && i+j < 200; j++) if(s[i+j] == '0') t[i] |= (ulint)1 << j;
		pos[t[i] % P].push_back(i);
		chk[t[i] % P] = true;
	}

	ulint pref[200];
	pref[0] = (s[0] == '0');
	for(int i = 1; i < 64; i++) {
		if(s[i] == '0') pref[i] = pref[i-1] | ((ulint)1 << i);
		else pref[i] = pref[i-1];
	}

	int ans = int(2e9);
	for(int i = 1; i < Z; i++) {
		int u = seq[i] % P;
		if(chk[u]) {
			for(int offset : pos[u]) {
				bool good = true;
				//if(i*64-offset == 95030136)
				//printf("i=%d u=%d offset=%d\n", i, u, offset);
				int x = offset % 64, p = i - offset / 64;
				if(p < 0) continue;
				if(x > 0) {
					//if(i*64-offset == 95030136) printf(" >> %llu %llu\n", pref[x-1], (seq[p-1] >> (64 - x)));
					good &= (pref[x-1] == (seq[p-1] >> (64 - x)));
				}
				for(; x + 64 <= 200 && good; x += 64, p++) {
					good &= (t[x] == seq[p]);
					//if(i*64-offset == 95030136) printf(" >! %llu %llu\n", t[x], seq[p]);
				}
				if(x < 200) {
					good &= (t[x] == (seq[p] & (((ulint)1 << (200 - x)) - 1)));
				}
				//if(i*64-offset == 95030136) printf(" >@ x=%d, %llu %llu\n", x, t[x], (seq[p] & (((ulint)1 << (200 - x)) - 1)));
				if(good) ans = min(ans, (i * 64) - offset);
			}
		}
	}

	if(ans + 200 - 1 > int(1e9)) ans = -1;
	//assert(ans == 992993841);
	printf("%d\n", ans);
	return 0;
}