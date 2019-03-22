#include <bits/stdc++.h>

using namespace std;

char S[300500];

int main() {
	scanf("%s", S);
	int N =strlen(S);

	long long ans1 = 0;
	{
		auto go = [](string s) {
			long long m = 1, v = 0;
			for(char c : s) {
				if(c == '*') {
					m *= v;
					v = 0;
				}else {
					v = v * 10 + c - '0';
				}
			}
			return m * v;
		};

		string t;
		for(int i = 0; i < N; i++) {
			if(S[i] == '+') {
				ans1 += go(t);
				t = "";
			}else {
				t.push_back(S[i]);
			}
		}
		ans1 += go(t);
	}

	long long ans2 = 0;
	{
		long long v = 0;
		char last = '+';
		for(int i = 0; i < N; i++) {
			if(S[i] == '+' || S[i] == '*') {
				if(last == '+') ans2 += v;
				else if(last == '*') ans2 *= v;
				v = 0;
				last = S[i];
			}else {
				v = v * 10 + S[i] - '0';
			}
		}
				if(last == '+') ans2 += v;
				else if(last == '*') ans2 *= v;
	}

	long long ans; scanf("%lld", &ans);
	if(ans == ans1 && ans != ans2) {
		puts("M");
	}else if(ans != ans1 && ans == ans2) {
		puts("L");
	}else if(ans == ans1 && ans == ans2) {
		puts("U");
	}else {
		puts("I");
	}
	return 0;
}