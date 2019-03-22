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
vector<int> tok;

vector<int> ah1;
vector<int> ah2;
vector<int> th1;
vector<int> th2;

int p1pow[1000010];
int p2pow[1000010];

void append_tok(int x)
{
	tok.push_back(x);
	{
		int prv = (th1.empty() ? 0 : th1.back());
		th1.push_back((1LL * prv * p1 + x + 1) % q);
	}
	{
		int prv = (th2.empty() ? 0 : th2.back());
		th2.push_back((1LL * prv * p2 + x + 1) % q);
	}
}

void append_ans(int x)
{
	ans.push_back(x);
	{
		int prv = (ah1.empty() ? 0 : ah1.back());
		ah1.push_back((1LL * prv * p1 + x + 1) % q);
	}
	{
		int prv = (ah2.empty() ? 0 : ah2.back());
		ah2.push_back((1LL * prv * p2 + x + 1) % q);
	}
}

pair<int, int> get_seg_tok(int l, int r)
{
	//printf("gst %d %d\n", l, r);
	if(r == l - 1)
		return {-1, -1};
	if(l == 0)
		return { th1[r], th2[r] };
	return { (th1[r] - 1LL * th1[l - 1] * p1pow[r - l + 1] % q + q) % q,
	         (th2[r] - 1LL * th2[l - 1] * p2pow[r - l + 1] % q + q) % q };
}

pair<int, int> get_seg_ans(int l, int r)
{
	//printf("gsa %d %d\n", l, r);
	if(r == l - 1)
		return {-1, -1};
	if(l == 0)
		return { ah1[r], ah2[r] };
	return { (ah1[r] - 1LL * ah1[l - 1] * p1pow[r - l + 1] % q + q) % q,
	         (ah2[r] - 1LL * ah2[l - 1] * p2pow[r - l + 1] % q + q) % q };
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
		
		int ml = idx[i];
		int mr = idx[i] + len[i] - 1;
		
		tok.clear();
		th1.clear();
		th2.clear();
		for(j = mr; j>=ml; j--)
			append_tok(mod[j]);
		
		int lt = (int)tok.size();
		int la = (int)ans.size();
		
		//printf("i lt la %d %d %d\n", i, lt, la);
		
		int s = 1;
		for(int t = 2; t <= lt; t++)
		{
			int s1 = 0;
			int g1 = max(0, min({lt, la, t - s}));
			while(s1 < g1)
			{
				int x1 = (s1 + g1 + 1) / 2;
				//printf("sgx1 %d %d %d\n", s1, g1, x1);
				if(get_seg_ans(la - x1, la - 1) == get_seg_tok(lt - s - x1, lt - s - 1))
					s1 = x1;
				else
					g1 = x1 - 1;
			}
			if(s1 == max(0, min({lt, la, t - s})))
			{
				int s2 = 0;
				int g2 = max(0, la - (t - s));
				while(s2 < g2)
				{
					int x2 = (s2 + g2 + 1) / 2;
					//printf("sgx2 %d %d %d\n", s2, g2, x2);
					if(get_seg_ans(la - (t - s) - x2, la - (t - s) - 1) ==
					   get_seg_ans(la - x2, la - 1))
						s2 = x2;
					else
						g2 = x2 - 1;
				}
				if(s2 == max(0, la - (t - s)))
				{
					// s is prefix
				}
				else
				{
					if(ans[la - (t - s) - 1 - s2] > ans[la - 1 - s2])
						s = t;
				}
			}
			else
			{
				if(ans[la - 1 - s1] > tok[lt - s - 1 - s1])
					s = t;
			}
		}
		
		cnt[i] = s;
		for(j=ml+s-1; j>=ml; j--)
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


