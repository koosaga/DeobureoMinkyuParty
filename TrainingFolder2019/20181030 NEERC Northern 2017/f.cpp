#include <bits/stdc++.h>

using namespace std;

using llf = long double;
using lint = long long;
using pli = pair<lint, int>;
using pii = pair<int, int>;
const llf PI = acos(-1);

lint gcd(lint a, lint b) {
	return b ? gcd(b, a % b) : a;
}

/*

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
};*/

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
		ret.var -= 'a' - 1;

		ret.from = now[15];
		if(ret.from == '1') ret.from = 0;
		else ret.from -= 'a' - 1;

		ret.to = now[18];
		if(ret.to == '1') ret.to = 0;
		else ret.to -= 'a' - 1;
	}
	
	return ret;
}

int lines;
statement statements[25];

bool gph[30][30];
bool gph2[30][30];
int deg[30];
bool vis[30];

int par[30];

int get_par(int u) {
	return (par[u] == u) ? u : (par[u] = get_par(par[u]));
}
bool inp[30];

int ways[1<<21];

int main() {
	freopen("fygon20.in", "r", stdin);
	freopen("fygon20.out", "w", stdout);

	for(int u = 0; u <= 26; u++) par[u] = u;

	scanf("%d\n", &lines);
	
	for(int i = 0; i < lines; i++) {
		statement &s = statements[i];
		s = parse();
		if(s.type == 'f') {
			gph[s.from][s.var] = true;
			gph[s.var][s.to] = true;
			inp[s.from] = true;
			inp[s.to] = true;
			inp[s.var] = true;
		}
	}

	int ansk = 0;

	for(int k = 0; k <= 26; k++) {
		for(int i = 0; i <= 26; i++) {
			for(int j = 0; j <= 26; j++) {
				gph[i][j] |= gph[i][k] && gph[k][j];
			}
		}
	}
;

	for(int i = 0; i <= 26; i++) if(inp[i]) {
		for(int j = 0; j <= 26; j++) if(inp[j]) {
			int a = get_par(i);
			int b = get_par(j);
			if(!(gph[i][j] && gph[j][i])) {
				continue;
			}
			//printf("%c %c %d %d\n", i+'a'-1, j+'a'-1, a, b);
			par[a] = b;
		}
	}
	for(int i = 0; i <= 26; i++) if(inp[i] && get_par(i) == i) {
		//printf("%d %c\n", i, i+'a'-1);
		ansk += 1;
	}
	ansk -= 2;

	//printf("ansk = %d\n", ansk);
	//return 0;

	map<int, int> mp;

	auto go = [&mp](int x) {
		x = get_par(x);
		if(mp.find(x) == mp.end()) {
			int sz = mp.size();
			mp[x] = sz;
		}
		return mp[x];
	};

	vector<int> inv(27);
	for(int i = 0; i <= 26; i++) {
		statement &s = statements[i];
		if(s.type == 'f') {
			s.from = go(s.from);
			s.var = go(s.var);
			s.to = go(s.to);
			if(s.from != s.var) {
				inv[s.var] |= 1<<s.from;
			}
			if(s.var != s.to){
				inv[s.to] |= 1<<s.var;
			}
		}
	}

	lint fac = 1;
	for(int i = 1; i <= ansk; i++) {
		fac *= i;
	}

	int numv = mp.size();

	ways[(1<<numv)-1] = 1;
	for(int mask = (1<<numv)-2; mask >= 0; mask--) {
		for(int i = 0; i < numv; i++) {
			if((mask & inv[i]) == inv[i] && ((mask >> i) & 1) == 0) {
				ways[mask] += ways[mask ^ (1<<i)];
			}
		}
	}

	lint g = gcd(ways[0], fac);
	printf("%d %lld/%lld\n", ansk, ways[0] / g, fac / g);
	return 0;
}
