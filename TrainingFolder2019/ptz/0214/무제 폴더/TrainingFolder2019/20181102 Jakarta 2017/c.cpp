#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using pi = pair<int, int>;
using lint = long long;

lint N;
int K;
char S[int(5.1e4)];
lint ans[int(5.1e4)];

int main(){
	scanf("%lld%d", &N, &K);
	scanf("%s", S);

	K = strlen(S);

	if(S[K - 1] != '=')
	{
		lint l = 1, r = N;
		for(int i = 0; i < K; i++) {
			ans[i] = (S[i] == '>') ? (l++) : (r--);
		}

		auto check = [&](bool v) {
			if(!v) {
				puts("-1");
				exit(0);
			}
		};

		l = 1; r = N;
		for(int i = 0; i < K; i++) {
			lint x = ans[i];
			check(l <= x && x <= r);
			if(S[i] == '>') {
				l = x+1;
			}else if(S[i] == '<') {
				r = x-1;
			}else {
				check(l == r);
			}
		}
		check(l <= r);

		for(int i = 0; i < K; i++) {
			printf("%lld ", ans[i]);
		}

		return 0;
	}

	lint s = 1;
	lint g = N;
	vector<lint> res;
	for(int i = 0; i < K; i++)
	{
		//printf("sg %lld %lld\n", s, g);
		if(g < s)
		{
			puts("-1");
			return 0;
		}

		if(i == K - 1)
		{
			if(s == g)
			{
				res.push_back(s);
				break;
			}
			else
			{
				puts("-1");
				return 0;
			}
		}

		if(K - i - 1 > 100)
		{
			if(S[i] == '<')
			{
				res.push_back(g);
				g--;
			}
			else
			{
				res.push_back(s);
				s++;
			}
			continue;
		}

		lint x = g - s + 1;
		lint l = (S[i] == '<') ? x / 2 : (x + 1) / 2;
		lint r = x - 1;

		//printf("lr %lld %lld\n", l, r);
		lint u = -1;
		while(l <= r)
		{
			lint m = (l + r + 1) / 2;

			lint t = m;
			for(int j = i+1; j < K-1 && t; j++)
			{
				//printf("jt %d %lld\n", j, t);
				if(S[j] == '<')
					t = t / 2;
				else
					t = (t + 1) / 2;
			}
			//printf("lrmt %lld %lld %lld %lld\n", l, r, m, t);
			if(l == r)
			{
				if(t == 1)
					u = m;
				else if(t > 1)
				{
					puts("-1");
					return 0;
				}
				else
					u = x - 1;
				break;
			}

			if(t > 1)
				r = m - 1;
			else
				l = m;
		}

		//printf("u = %lld\n", u);

		if(u == -1)
		{
			puts("-1");
			return 0;
		}

		if(S[i] == '<')
		{
			res.push_back(s + u);
			g = s + u - 1;
		}
		else
		{
			res.push_back(g - u);
			s = g - u + 1;
		}
	}

	s = 1;
	g = N;
	for(int i = 0; i<K-1; i++)
	{
		lint t = res[i];
		if(g < s || t < s || t > g)
		{
			puts("-1");
			return 0;
		}
		if(S[i] == '<')
		{
			if(t - s < g - t)
			{
				puts("-1");
				return 0;
			}
			g = t - 1;
		}
		else
		{
			if(g - t <= t - s)
			{
				puts("-1");
				return 0;
			}
			s = t + 1;
		}
	}
	if(s != g || res[K - 1] != s)
	{
		puts("-1");
		return 0;
	}

	for(lint x : res)
		printf("%lld ", x);

	return 0;
}







