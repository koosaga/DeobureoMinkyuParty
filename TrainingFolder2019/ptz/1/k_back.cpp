#include <bits/stdc++.h>
using namespace std;

const int MAX_L = 20;
set<string> s;
queue<string> q;

bool cmp(const string &t1, const string &t2)
{
	return t1.size() != t2.size() ? t1.size() > t2.size() : t1 < t2;
}

int main()
{
	string t;
	s.insert(t);
	q.push(t);
	while(!q.empty())
	{
		string t = q.front();
		q.pop();

		int l = t.size();

		if(l+2 <= MAX_L)
		{
			for(int i=0; i<=l; i++)
			{
				string t2 = t.substr(0, i) + "aa" + t.substr(i);
				if(s.insert(t2).second)
					q.push(t2);
			}
		}
		if(l+3 <= MAX_L)
		{
			for(int i=0; i<=l; i++)
			{
				string t2 = t.substr(0, i) + "bbb" + t.substr(i);
				if(s.insert(t2).second)
					q.push(t2);
			}
		}
		if(l+6 <= MAX_L)
		{
			for(int i=0; i<=l; i++)
			{
				string t2 = t.substr(0, i) + "ababab" + t.substr(i);
				if(s.insert(t2).second)
					q.push(t2);
			}
		}
		for(int i=0; i<=l-2; i++)
		{
			if(t.substr(i, 2) == "aa")
			{
				string t2 = t.substr(0, i) + t.substr(i+2);
				if(s.insert(t2).second)
					q.push(t2);
			}
		}
		for(int i=0; i<=l-3; i++)
		{
			if(t.substr(i, 3) == "bbb")
			{
				string t2 = t.substr(0, i) + t.substr(i+3);
				if(s.insert(t2).second)
					q.push(t2);
			}
		}
		for(int i=0; i<=l-6; i++)
		{
			if(t.substr(i, 6) == "ababab")
			{
				string t2 = t.substr(0, i) + t.substr(i+6);
				if(s.insert(t2).second)
					q.push(t2);
			}
		}
	}

	vector<string> v;
	for(string t : s)
		v.push_back(t);

	sort(v.begin(), v.end(), cmp);

	vector<int> cnt(MAX_L+2);
	for(string t : v) {
		if(t.find("aa") == string::npos && t.find("bbb") == string::npos && t.find("ababab") == string::npos) {
			printf("%s\n", t.c_str());

		}
		cnt[t.length()] += 1;
	}

	for(int i = 1; i <= MAX_L; i++) {
		printf("cnt[%d]=%d\n", i, cnt[i]);
	}

	return 0;
}