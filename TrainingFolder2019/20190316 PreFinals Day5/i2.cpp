#include <bits/stdc++.h>
using namespace std;

const int p1 = 29;
const int p2 = 31;
const int q = 1000000007;

char arr[1000010];
int mod[1000010];

bool beg[1000010];
int len[1000010];
int idx[1000010];

int cnt[1000010];
char res[1000010];
vector<int> ans;
vector<int> ah1;
vector<int> ah2;

int p1pow[1000010];
int p2pow[1000010];

void append_ans(int x)
{
	ans.push_back(x);
	{
		int prv = (ah1.empty() ? 0 : ah1.back());
		ah1.push_back((1LL * prv * p1 + x) % q);
	}
	{
		int prv = (ah2.empty() ? 0 : ah2.back());
		ah2.push_back((1LL * prv * p2 + x) % q);
	}
}

pair<int, int> get_seg(int l, int r)
{
	if(l == 0)
		return { ah1[r], ah2[r] };
	return { (ah1[r] - 1LL * ah1[l - 1] * p1pow[r - l + 1] % q + q) % q,
	         (ah2[r] - 1LL * ah2[l - 1] * p2pow[r - l + 1] % q + q) % q };
}

// [? .. l - 1]
// [? .. x - 1]
int get_max_len(int x)
{
	int l = (int)ans.size();
	int s = 0;
	int g = x;
	while(s < g)
	{
		int m = (s + g + 1) / 2;
		if(get_seg(l - m, l - 1) == get_seg(x - m, x - 1))
			s = m;
		else
			g = m - 1;
	}
	return s;
}

int main()
{
	int n, i, j;
	fgets(arr, 1000010, stdin);
	n = strlen(arr);
	
	while(n > 0 && arr[n - 1] == '\n')
		n--;
	
	p1pow[0] = 1;
	p2pow[0] = 1;
	for(i=1; i<1000010; i++)
	{
		p1pow[i] = 1LL * p1pow[i-1] * p1 % q;
		p2pow[i] = 1LL * p2pow[i-1] * p2 % q;
	}
	
	int m = 0;
	bool u = 1;
	int p = -1;
	int c;
	for(i=0; i<n; i++)
	{
		if(isalpha(arr[i]))
		{
			if(u)
			{
				p = i;
				beg[i] = 1;
				u = 0;
				c = 0;
			}
			mod[m] = tolower(arr[i]) - 'a';
			idx[i] = m;
			m++;
			c++;
		}
		else
		{
			u = 1;
			if(p != -1)
			{
				len[p] = c;
				p = -1;
			}
		}
	}
	if(p != -1)
	{
		len[p] = c;
		p = -1;
	}
	
	for(i=n-1; i>=0; i--)
	{
		if(!beg[i])
			continue;
		
		int p = (int)ans.size() - 1;
		int x = idx[i];
		bool ok = 0;
		for(j=idx[i] + 1; j<idx[i] + len[i]; j++)
		{
			if(p == -1 || mod[j] > ans[p])
			{
				ok = 1;
				break;
			}
			
			if(mod[j] < ans[p])
			{
				x = j;
				p = (int)ans.size() - 1;
				continue;
			}
			
			p--;
		}
		
		// do the hash
		if(!ok && x < idx[i] + len[i] - 1)
		{
			int l = (int)ans.size();
			int s = 0;
			int mxt = idx[i] + len[i] - 1 - x;
			
			for(int t = 1; t <= mxt; t++)
			{
				int r1 = get_max_len(l - s);
				if(r1 >= t - s)
				{
					int r2 = get_max_len(l - t + s);
					if(r2 >= l - t + s)
					{
						// s is good
					}
					else
					{
						if(ans[l - 1 - r2] < ans[l - t + s - 1 - r2])
							s = t;
					}
				}
				else
				{
					if(ans[l - s - 1 - r1] < ans[l - 1 - r1])
						s = t;
				}
			}
			
			x += s;
		}
		
		cnt[i] = x - idx[i] + 1;
		for(j=x; j>=idx[i]; j--)
			append_ans(mod[j]);
	}
	
	int r = 0;
	for(i=0; i<n; i++)
	{
		if(beg[i])
		{
			for(j=i; j<i+cnt[i]; j++)
				res[r++] = arr[j];
			if(cnt[i] < len[i])
				res[r++] = '.';
			i += len[i] - 1;
		}
		else
			res[r++] = arr[i];
	}
	
	puts(res);
	return 0;
}


