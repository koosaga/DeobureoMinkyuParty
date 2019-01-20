#include <bits/stdc++.h>

using namespace std;

mt19937 rng;

int is(vector<int> p) {
	int n = p.size();
	vector<int> dp[2];
	dp[0].resize(n, 1);
	dp[1].resize(n, 1);
	for(int i = n-1; i >= 1; i--) {
		dp[1][p[i]] *= dp[0][i];
		dp[0][p[i]] *= dp[0][i] + dp[1][i];
	}
	return dp[0][0] + dp[1][0] - 1;
}

vector<int> trees[2050];

const int leftm[] = {200, 202, 204, 206, 207, 209, 210, 212, 213, 214, 218, 219, 220, 222, 226, 227, 228, 229, 230, 234, 236, 237, 238, 239, 243, 246, 250, 264, 270, 290, 294, 298, 300, 302, 314, 321, 324, 328, 330, 332, 336, 338, 340, 342, 344, 346, 349, 354, 356, 357, 358, 360, 361, 362, 368, 372, 373, 378, 384, 386, 388, 390, 398, 399, 406, 412, 426, 436, 454, 462, 466, 474, 476, 480, 482, 486, 496, 506, 508, 514, 518, 520, 528, 534, 538, 540, 542, 550, 554, 558, 560, 562, 566, 572, 574, 576, 578, 582, 584, 590, 592, 593, 604, 606, 608, 610, 620, 621, 622, 624, 625, 626, 627, 628, 632, 638, 640, 644, 645, 646, 655, 676, 682, 698, 702, 708, 718, 720, 758, 786, 796, 804, 812, 826, 836, 838, 846, 850, 854, 858, 868, 870, 874, 882, 886, 890, 896, 900, 906, 910, 912, 914, 920, 922, 924, 926, 932, 934, 936, 938, 942, 948, 952, 954, 960, 962, 966, 968, 970, 972, 974, 976, 978, 988, 990, 992, 994, 998, 1000, 1002, 1006, 1008, 1012, 1014, 1016, 1017, 1018, 1022, 1030, 1040, 1042, 1044, 1046, 1062, 1068, 1080, 1082, 1094, 1102, 1110, 1116, 1122, 1128, 1158, 1170, 1178, 1188, 1234, 1246, 1280, 1286, 1332, 1338, 1362, 1382, 1384, 1388, 1396, 1438, 1440, 1458, 1460, 1462, 1468, 1476, 1492, 1512, 1516, 1518, 1522, 1524, 1525, 1526, 1530, 1538, 1540, 1552, 1566, 1568, 1570, 1572, 1580, 1594, 1597, 1602, 1604, 1614, 1622, 1624, 1630, 1634, 1638, 1641, 1642, 1646, 1650, 1654, 1656, 1666, 1670, 1678, 1684, 1686, 1690, 1702, 1710, 1722, 1728, 1746, 1750, 1758, 1762, 1766, 1770, 1790, 1792, 1816, 1822, 1828, 1870, 1922, 1930, 1936};

int main() {
	/*{
		vector<int> p1;
		p1.push_back(-1);
		p1.push_back(0);
		p1.push_back(0);
		p1.push_back(2);
		p1.push_back(3);
		p1.push_back(4);

		printf("%d\n", is(p1));
		return 0;
	}*/

	set<int> cur;
	uniform_int_distribution<int> nrnd(10, 15);
	int cnt = 0;
	for(int rep = 0; cnt < 2000; rep++) {	
		int n = nrnd(rng);
		vector<int> p(n, -1);
		for(int i = 1; i < n; i++) {
			uniform_int_distribution<int> prnd(max(i-4, 0), i-1);
			p[i] = prnd(rng);
		}
		{
			int v = is(p);
			if(v <= 2000 && trees[v].empty()) {
				trees[v] = p;
				cnt += 1;
			}
		}
		if(rep % 10000 == 0) {
			printf("cnt = %d\n", cnt);
		}
		if(rep % 1000000 == 0) {
			printf("printed!");
			FILE *out = fopen("g.out.txt", "w");
			for(int v = 1; v <= 2000; v++) {
				if(!trees[v].empty()) {
					fprintf(out,"%d: (", v);
					for(int j = 0; j < (int)trees[v].size(); j++) {
						fprintf(out,"%d,", trees[v][j]);
					}
					fprintf(out,"),\n");
				}
			}
			fclose(out);
		}
	}

	/*
	for(int m : leftm) {
		uniform_int_distribution<int> nrnd(9, 9);
		printf("m = %d\n", m);
		for(int rep = 0; rep < 1000; rep++) {	
			vector<int> p;
			do {
				p.clear();
				int n = nrnd(rng);
				p.resize(n, -1);
				for(int i = 1; i < n; i++) {
					uniform_int_distribution<int> prnd(0, i-1);
					p[i] = prnd(rng);
				}
			}while(abs(is(p) - m) >= 300);

			int n = p.size();

			int v = is(p);
			if(v <= 2000 && trees[v].empty()) {
				trees[v] = p;
			}
			if(v == m) {
				break;
			}

			for(int rep2 = 0; rep2 < 2000; rep2++) {
				uniform_int_distribution<int> irnd(1, n-1);
				int i = irnd(rng);
				uniform_int_distribution<int> jrnd(0, i-1);
				int j = jrnd(rng);
				int op = p[i];
				p[i] = j;
				if(is(p) == m) {
					trees[m] = p;
					break;
				}else {
					p[i] = op;
				}
			}
			if(!trees[m].empty()) {
				printf("found %d\n", m);
				break;
			}
			/*
			if(rep % 10000 == 0) {
				printf("cnt = %d\n", cnt);
			}
			if(rep % 1000000 == 0) {
			}
		}
		printf("printed!");
		FILE *out = fopen("g.out.txt", "w");
		for(int v = 1; v <= 2000; v++) {
			if(!trees[v].empty()) {
				fprintf(out,"%d: (", v);
				for(int j = 0; j < (int)trees[v].size(); j++) {
					fprintf(out,"%d,", trees[v][j]);
				}
				fprintf(out,"),\n");
			}
		}
		fclose(out);
	}*/

	return 0;
}