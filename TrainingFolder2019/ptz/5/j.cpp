#include <bits/stdc++.h>

using llf = long double;
using lint = long long;

using namespace std;

namespace miller_rabin {
	inline lint mul(lint x, lint y, lint mod) { return (__int128)x * y % mod; }
	lint ipow(lint x, lint y, lint p) {
		lint ret = 1, piv = x % p;
		while(y) {
			if(y & 1) ret = mul(ret, piv ,p);
			piv = mul(piv, piv, p);
			y >>= 1;
		}
		return ret;
	}

	bool miller_rabin(lint x, lint a) {
		if(x % a == 0) return 0;
		lint d = x - 1;
		while(true) {
			lint tmp = ipow(a,d,x);
			if(d&1) return tmp!=1 && tmp!=x-1;
			else if(tmp == x-1) return 0;
			d >>= 1;
		}
	}

	bool is_prime (lint x) {
		for(auto &i : {2,3,5,7,11,13,17,19,23,29,31,37}) {
			if(x == i) return 1;
			if(x > 40 && miller_rabin(x, i)) return 0;
		}
		if(x <= 40) return 0;
		return 1;
	}
};

/*
vector<lint> last_1;

void go_1 (lint n, lint p) {
	if(p == lint(1e18)) {
		return;
	}
	char s[20];
	sprintf(s, "%lld", n);
	int l = strlen(s);

	for(int x : {8, 0}) {
		bool good = true;
		for(int mask = 1; mask < (1<<l); mask++) {
			lint v = 0, c = 1;
			for(int i = 0; i < l; i++) if((mask >> i) & 1) c *= 10, v = v * 10 + s[i] - '0';
			if(miller_rabin::is_prime(v + c * x)) {
				good = false;
				break;
			}
		}
		if(good) {
			if(x > 0) printf("%lld\n", n + p * x);
			if(x > 0) last_1.push_back(n + p * x);
			go_1(n + p * x, p * 10);
		}
	}
}*/

/*
vector<lint> last_9;

void go_9 (lint n, lint p, bool has_4) {
	if(p == lint(1e18)) {
		return;
	}
	char s[20];
	sprintf(s, "%lld", n);
	int l = strlen(s);

	for(int x : {4, 6, 0}) {
		bool good = true;
		for(int mask = 1; mask < (1<<l); mask++) {
			lint v = 0, c = 1;
			for(int i = 0; i < l; i++) if((mask >> i) & 1) c *= 10, v = v * 10 + s[i] - '0';
			if(miller_rabin::is_prime(v + c * x)) {
				good = false;
				break;
			}
		}
		if(good) {
			if(x > 0 && (has_4 || (x == 4))) printf("%lld\n", n + p * x);
			if(x > 0) last_9.push_back(n + p * x);
			go_9(n + p * x, p * 10, has_4 | (x == 4));
		}
	}
}


last_9.push_back(9);
go_9(9, 10, 0);
for(lint x : last_9) {
	printf("%lld ", x);
}
puts("");
*/
vector<lint> last_1;

vector<lint> last_9 = {9LL, 49LL, 469LL, 649LL, 4669LL, 6049LL, 6649LL, 46669LL, 60049LL, 60649LL, 66049LL, 66649LL, 466669LL, 600049LL, 600649LL, 606049LL, 606649LL, 660049LL, 666049LL, 4666669LL, 6000049LL, 6000649LL, 6006049LL, 6006649LL, 6060049LL, 6066049LL, 6600049LL, 6660049LL, 46666669LL, 60000049LL, 60000649LL, 60006049LL, 60006649LL, 60060049LL, 60066049LL, 60600049LL, 60660049LL, 466666669LL, 600000049LL, 600000649LL, 600006049LL, 600006649LL, 600060049LL, 600066049LL, 600600049LL, 600660049LL, 4666666669LL, 6000000049LL, 6000000649LL, 6000006049LL, 6000006649LL, 6000060049LL, 6000066049LL, 6000600049LL, 6000660049LL, 46666666669LL, 60000000049LL, 60000000649LL, 60000006049LL, 60000006649LL, 60000060049LL, 60000066049LL, 60000600049LL, 60000660049LL, 466666666669LL, 600000000049LL, 600000000649LL, 600000006049LL, 600000006649LL, 600000060049LL, 600000066049LL, 600000600049LL, 600000660049LL, 4666666666669LL, 6000000000049LL, 6000000000649LL, 6000000006049LL, 6000000006649LL, 6000000060049LL, 6000000066049LL, 6000000600049LL, 6000000660049LL, 46666666666669LL, 60000000000049LL, 60000000000649LL, 60000000006049LL, 60000000006649LL, 60000000060049LL, 60000000066049LL, 60000000600049LL, 60000000660049LL, 466666666666669LL, 600000000000049LL, 600000000000649LL, 600000000006049LL, 600000000006649LL, 600000000060049LL, 600000000066049LL, 600000000600049LL, 600000000660049LL, 4666666666666669LL, 6000000000000049LL, 6000000000000649LL, 6000000000006049LL, 6000000000006649LL, 6000000000060049LL, 6000000000066049LL, 6000000000600049LL, 6000000000660049LL, 46666666666666669LL, 60000000000000049LL, 60000000000000649LL, 60000000000006049LL, 60000000000006649LL, 60000000000060049LL, 60000000000066049LL, 60000000000600049LL, 60000000000660049LL, 600000000000000049LL, 600000000000000649LL, 600000000000006049LL, 600000000000006649LL, 600000000000060049LL, 600000000000066049LL, 600000000000600049LL, 600000000000660049LL};


lint pow3[20];
// last_1: 81, 801, 8001, 80001, ... (881 is prime)


// case 1: only 0, 4, 6, 8
lint case_1 (lint n) {
	lint ret = 0;
	char s[20]; sprintf(s, "%lld", n);
	int l = strlen(s);

	for(int i = 0; i < l; i++) {
		bool same = false;
		for(int c : {0, 4, 6, 8}) {
			if(c + '0' < s[i]) {
				ret += 1ll << ((l - i - 1) * 2);
			}else if(c + '0' == s[i]) {
				same = true;
			}else {
				break;
			}
		}
		if(!same) {
			break;
		}
	}

	bool good = true;
	for(int i = 0; i < l; i++) good &= (s[i] == '0' || s[i] == '4' || s[i] == '6' || s[i] == '8');
	if(good) ret += 1;
	return ret;
}

lint pow10[19];

bool check(lint n) {
	char s[20];
	sprintf(s, "%lld", n);
	int l = strlen(s);

	bool good = true;
	for(int mask = 1; mask < (1<<l); mask++) {
		lint v = 0;
		for(int i = 0; i < l; i++) if((mask >> i) & 1) v = v * 10 + s[i] - '0';
		if(miller_rabin::is_prime(v)) {
			good = false;
			break;
		}
	}

	return good;
}

lint naive_solve (lint n) {
	lint ret = 0;
	for(lint i = 1; i <= n; i++) {
		/*char s[20]; sprintf(s, "%lld", i);

		bool has_1 = false, only_even = true;
		for(char c : s) {
			if(!c) break;
			has_1 |= c == '1';
			only_even &= (c % 2 == 0);

		}*/
		//if((has_1 || only_even) && 
		if(check(i)) {
			ret += 1;
		}
	}
	return ret;
}

lint solve (lint n) {
	if(n == lint(1e18)) {
		return solve(n-1) + 1;
	}

	char s[20]; sprintf(s, "%lld", n);
	int l = strlen(s);

	lint ret = case_1(n) - 1;

	// case 2/3: ends with 1
	{
		for(lint pref : last_1) {
			char tmp[30];
			sprintf(tmp, "%lld", pref);
			int tmp_len = strlen(tmp);
			for(int cur_len = tmp_len; cur_len < 18; cur_len++) {
				string s1 = tmp;
				while(s1.size() < cur_len) s1 += '0';
				string s2 = tmp;
				while(s2.size() < cur_len) s2 += '8';

				lint f, t;
				sscanf(s1.c_str(), "%lld", &f);
				sscanf(s2.c_str(), "%lld", &t);

				if(n < f) {
					continue;
				}
				if(t <= n) {
					ret += 1ll << ((cur_len - tmp_len) * 2);
					continue;
				}

				assert(cur_len > tmp_len);
				ret += case_1(n % pow10[cur_len - tmp_len]);
			}
		}	
	}

	// case 4: ends with 9
	{
		for(lint pref : last_9) {
			char tmp[30];
			sprintf(tmp, "%lld", pref);
			int tmp_len = strlen(tmp);
			for(int cur_len = tmp_len; cur_len < 18; cur_len++) {
				string s1 = tmp;
				while(s1.size() < cur_len) s1 += '0';
				string s2 = tmp;
				while(s2.size() < cur_len) s2 += '8';

				lint f, t;
				sscanf(s1.c_str(), "%lld", &f);
				sscanf(s2.c_str(), "%lld", &t);

				if(n < f) {
					continue;
				}
				if(t <= n) {
					ret += 1ll << ((cur_len - tmp_len) * 2);
					continue;
				}

				assert(cur_len > tmp_len);
				ret += case_1(n % pow10[cur_len - tmp_len]);
			}
		}
	}

	return ret;
}

int main() {
	pow10[0] = 1;
	for(int i = 1; i <= 18; i++) pow10[i] = pow10[i-1] * 10;

	pow3[0] = 1;
	for(int i = 1; i <= 18; i++) pow3[i] = pow3[i-1] * 3;

	last_1.push_back(1);
	last_1.push_back(91);
	last_1.push_back(901);
	for(int i = 1; i < 18; i++) {
		last_1.push_back( 1 + 8 * pow10[i]);
		for(int j = i+1; j < 18; j++) {
			lint n = 1 + 8 * pow10[i] + 9 * pow10[j];
			last_1.push_back(n);
		}
	}



// last_9:
 // 4 is first 
//   -> 4000...006666..669 (40609 is prime)
//   -> 46666...6609 (if |6| >= 2, then |0| = 1 bcz 466009, 466069 is prime)
//   -> 4600..0009, 4600..00069
// 6 is first -> use precomputed answer

/*
	for(int num_0 = 0; num_0 < 18; num_0++) {
		for(int num_6 = 0; num_0 + num_6 < 18; num_6++) {
			string s;
			s += '4';
			for(int i = 0; i < num_0; i++) s += '0';
			for(int i = 0; i < num_6; i++) s += '6';
			s += '9';
			if(s.length() < 18) {
				lint x; sscanf(s.c_str(), "%lld", &x);
				if(check(x)) {
					last_9.push_back(x);
				}				
			}
		}
	}

	for(int num_6 = 2; num_6 < 18; num_6++) {
		string s;
		s += '4';
		for(int i = 0; i < num_6; i++) s += '6';
		s += "09";
		if(s.length() < 18) {
			lint x; sscanf(s.c_str(), "%lld", &x);
			if(check(x)) {
				last_9.push_back(x);
			}				
		}
	}

	for(int num_0 = 0; num_0 < 18; num_0++) {
		string s;
		s += "46";
		for(int i = 0; i < num_0; i++) s += '0';
		s += "9";
		if(s.length() < 18) {
			lint x; sscanf(s.c_str(), "%lld", &x);
			if(check(x)) {
				last_9.push_back(x);
			}				
		}
	}

	for(int num_0 = 0; num_0 < 18; num_0++) {
		string s;
		s += "46";
		for(int i = 0; i < num_0; i++) s += '0';
		s += "69";
		if(s.length() < 18) {
			lint x; sscanf(s.c_str(), "%lld", &x);
			if(check(x)) {
				last_9.push_back(x);
			}				
		}
	}

	last_9.push_back(9);
	sort(last_9.begin() ,last_9.end());
	last_9.resize(unique(last_9.begin(), last_9.end()) - last_9.begin());
	for(lint x : last_9) printf("%lldLL, ", x);
*/

	for(lint n = 1; n <= 1000; n++) {
		if(solve(n) != naive_solve(n)) {
			printf("%lld %lld %lld\n", n, solve(n), naive_solve(n));
			break;
		}
	}
//	printf("%lld %lld\n", solve(21891), naive_solve(21891));
	return 0;



	return 0;
}