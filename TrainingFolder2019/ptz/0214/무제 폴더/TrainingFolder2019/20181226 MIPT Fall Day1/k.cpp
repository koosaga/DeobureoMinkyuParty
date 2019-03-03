#include <bits/stdc++.h>

using namespace std;

vector<int> removals[1<<9][13];
int freq[13];

double max_exp[1<<9], min_exp[1<<9];
int score[1<<9];

int main() {
	for(int mask = 0; mask < (1<<9); mask++) {
		for(int i = 0; i < 9; i++) if((mask >> i) & 1) score[mask] = score[mask] * 10 + i + 1;
		
		for(int submask = mask; submask > 0; submask = (submask - 1) & mask) {
			int sum = 0;
			for(int i = 0; i < 9; i++) if((submask >> i) & 1) sum += i+1;
			if(sum <= 12) removals[mask][sum].push_back(submask);
		}
	}

	max_exp[0] = min_exp[0] = 0;

	for(int a = 1; a <= 6; a++) for(int b = 1; b <= 6; b++) {
		freq[a+b] += 1;
	}

	for(int mask = 1; mask < (1<<9); mask++) {
		for(int sum = 2; sum <= 12; sum++) {
			double cur_min = 1e9, cur_max = -1e9;
			for(int submask : removals[mask][sum]) {
				assert((mask & submask) == submask);
				cur_min = min(cur_min, min_exp[mask ^ submask]);
				cur_max = max(cur_max, max_exp[mask ^ submask]);
			}
			if(removals[mask][sum].empty()) {	
				cur_min = cur_max = score[mask];
			}
			min_exp[mask] += cur_min * freq[sum] / 36.0;
			max_exp[mask] += cur_max * freq[sum] / 36.0;
		}
	}

	char tmp[15]; int d1, d2; scanf("%s%d%d", tmp, &d1, &d2);
	int mask = 0; for(char *c = tmp; *c != 0; c++) mask |= 1 << (*c - '0' - 1);

	double min_ans = 1e9; int min_way = -1;
	double max_ans = -1e9; int max_way = -1;

	for(int submask : removals[mask][d1 + d2]) {
		if(min_ans > min_exp[mask ^ submask]) {
			min_ans = min_exp[mask ^ submask];
			min_way = score[submask];
		}
		if(max_ans < max_exp[mask ^ submask]) {
			max_ans = max_exp[mask ^ submask];
			max_way = score[submask];
		}
	}

	if(min_way == -1) {
		min_ans = atoi(tmp);
	}
	if(max_way == -1) {
		max_ans = atoi(tmp);
	}

	printf("%d %.10lf\n", min_way, min_ans);
	printf("%d %.10lf\n", max_way, max_ans);


	return 0;
}