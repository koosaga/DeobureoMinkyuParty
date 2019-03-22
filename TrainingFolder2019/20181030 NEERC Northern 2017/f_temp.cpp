#include <bits/stdc++.h>

using namespace std;

using llf = long double;
using lint = long long;
using pli = pair<lint, int>;
using pii = pair<int, int>;
const llf PI = acos(-1);

using bigint = lint;

bigint gcd (bigint a, bigint b) {
	return b ? gcd(a, b % a) : a;
}

struct frac {
	bigint j, m;
	frac(bigint j_ = 0, bigint m_ = 1): j(j_), m(m_) { }

	frac operator+ (frac other) {
		frac ret(j * other.m + m * other.j, m * other.m);
		bigint g = gcd(ret.j, ret.m);
		return ret;
	}

	frac operator- (frac other) {
		frac ret(j * other.m - m * other.j, m * other.m);
		bigint g = gcd(ret.j, ret.m);
		return ret;
	}

	frac operator* (frac other) {
		frac ret(j * other.j, m * other.m);
		bigint g = gcd(ret.j, ret.m);
		return ret;
	}
};

const int NUM_VAR = 26;
struct hang {
	frac coef;
	vector<int> num; // ('a'+i) ^ num[i]

	hang(frac coef_ = frac(), vector<int> num_ = vector<int>(NUM_VAR)): num(num_), coef(coef_) { }

	hang operator* (const hang &other) {
		hang ret;
		for(int i = 0; i < NUM_VAR; i++) {
			ret.num[i] = num[i] + other.num[i];
		}
		ret.coef = coef * other.coef;
		return ret;
	}

	hang integrate(char var) {
		var -= 'a';
		hang ret = *this;
		ret.num[var] += 1;
		ret.coef *= frac(1, ret.num[var]);
		return ret;
	}

	hang substitute(char f, char t) {
		hang ret = *this;
		f -= 'a';
		t -= 'a';
		ret.num[t] += ret.num[f];
		ret.num[f] = 0;
		return ret;
	}
};

struct statement {
	int step;
	char type;
	char var, from, to;
};

const int ONE_INDENT = 4;
statement parse() {
	static char line[200];

	fgets(line, 150, stdin);
	int num_indent = 0;
	while(line[num_indent] == ' ') {
		num_indent += 1;
	}

	statement ret;
	ret.step = num_indent / ONE_INDENT;
	// for X in range(A, B):
	// 01234567890123456789

	char *now = line + num_indent;
	if(now[0] == 'l' && now[1] == 'a' && now[2] == 'g') {
		ret.type = 'l';
	}else {
		ret.type = 'f';
		ret.var = now[4];
		ret.from = now[15];
		ret.to = now[18];
	}
	
	return ret;
}

int lines;
statement statements[25];

vector<hang> go(int &i, int step) {
	vector<hang> ret;
	while(i < lines) {
		statement &s = statements[i];
		if(s.step < step) {
			break;
		}
		/*
			for(int rep=0;rep<step;rep++) fputs(" ",stderr);
			{
			fprintf(stderr,"%d: %d %c %c %c %c\n", i, s.step, s.type, s.var, s.from, s.to);

			}*/

		i += 1;
		if(s.type == 'l') {
			ret.push_back(hang(1));
		}else {
			vector<hang> ch = go(i, step+1);
			// s.var, s.from, s.to
			// 
			for(hang h : ch) {
				hang h_i = h.integrate(s.var);
				if(s.to != '1') {
					
				}
			}
		}
	}
	return ret;
}

int main() {
	freopen("fygon20.in", "r", stdin);
	freopen("fygon20.out", "w", stdout);

	scanf("%d\n", &lines);
	for(int i = 0; i < lines; i++) {
		statements[i] = parse();
/*
		statement &s = statements[i];
		printf("%d %c %c %c %c\n", s.step, s.type, s.var, s.from, s.to);
*/
	}

	int i = 0;
	vector<hang> ret = go(i, 0);

	return 0;
}
