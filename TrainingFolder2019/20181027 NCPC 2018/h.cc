#include <bits/stdc++.h>

using namespace std;

using llf = long double;

long long l; int m;

int main() {
	scanf("%lld%d\n", &l, &m);
	vector<pair<string,int>> answer;
	for(int rep = 0; rep < m; rep++) {
		static char line[1000];
		fgets(line, 900, stdin);

		vector<string> tokens(1);
		for(int i = 0; line[i]; i++) {
			if(line[i] == ',') {
				tokens.push_back("");
			}else {
				tokens.back() += line[i];
			}
		}

		int p = atoi(tokens[1].c_str());
		long long c = atoi(tokens[2].c_str());
		long long t = atoi(tokens[3].c_str());
		long long r = atoi(tokens[4].c_str());

		bool good = true;
		const long long WEEK_LEN = 10080;
		for(int weeks = 1; weeks <= 200000; weeks++) {
			long long area = 0;
			area += (weeks * WEEK_LEN / (t + r)) * (c * t);
			area += min(weeks * WEEK_LEN % (t + r) , t) * c;
			if(area < weeks * l) {
				good = false;
				break;
			}
		}

		if(good) {
			if(answer.empty() || answer.back().second > p) {
				answer.clear();
				answer.emplace_back(tokens[0], p);
			}else if(answer.back().second == p) {
				answer.emplace_back(tokens[0], p);
			}
		}

	}

	if(answer.empty()) {
		answer.emplace_back("no such mower", -1);
	}

	for(auto line : answer) {
		puts(line.first.c_str());
	}
	return 0;

}