#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <numeric>
#include <functional>
#include <tuple>
#include <complex>
#include <bitset>
#include <random>

using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

char arr[100000];
char stk[100000];
char val[100] = "SLB()[], ";

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	bool u;
	int w, s, c, n, i, j;
	long long r;
	scanf("%d ", &w);

	fgets(arr, 100000, stdin);

	n = strlen(arr);

	for (i = 0; i < n; i++) {
		if (arr[i] <= 32)
			continue;

		u = 1;
		for (j = 0; j < 9; j++) {
			if (arr[i] == val[j]) {
				u = 0;
				break;
			}
		}
		if (u) {
			printf("-1");
			return 0;
		}
	}

	s = 0;
	for (i = 0; i < n; i++) {
		if (arr[i] == '(' || arr[i] == '[')
			stk[s++] = arr[i];
		else if (arr[i] == ')' || arr[i] == ']') {
			if (s == 0 || arr[i] == ')' && stk[s - 1] == '[' || arr[i] == ']' && stk[s - 1] == '(') {
				printf("-1");
				return 0;
			}
			s--;
		}
	}
	if (s != 0) {
		printf("-1");
		return 0;
	}

	s = 0;
	c = 0;
	for (i = 0; i < n; i++) {
		if (arr[i] <= 32)
			continue;

		if (s == 0) {
			if (arr[i] == 'S')
				s = 1;
			else if (arr[i] == 'L' || arr[i] == 'B')
				s = 2;
			else {
				printf("-1");
				return 0;
			}
		}
		else if (s == 1) {
			if (arr[i] == ',')
				s = 0;
			else if (arr[i] == ')' || arr[i] == ']') {
				c--;
				if (c < 0) {
					printf("-1");
					return 0;
				}
			}
			else {
				printf("-1");
				return 0;
			}
		}
		else if (s == 2) {
			if (arr[i] == '(' || arr[i] == '[') {
				s = 0;
				c++;
			}
			else {
				printf("-1");
				return 0;
			}
		}
	}

	if (s != 1 || c != 0) {
		printf("-1");
		return 0;
	}

	r = 1;
	for (i = 0; i < n; i++) {
		if (arr[i] == ',')
			r += 0;
		else if (arr[i] == 'S')
			r += 0;
		else if (arr[i] == 'B')
			r += 1;
		else if (arr[i] == 'L')
			r += w;
	}
	printf("%lld", r);
	return 0;
}