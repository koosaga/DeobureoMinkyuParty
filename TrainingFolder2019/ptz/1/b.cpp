#include <bits/stdc++.h>

using namespace std;

int arr[200010];
int idx[200010];
int bp;
void addv(int x, int v)
{
	x++;
	while(x < 200010){
		idx[x] = max(idx[x], v);
		x += x & -x;
	}
}
int getv(int x, int y)
{
	if(y < x)
		return 0;

	assert(x == 0);
	y++;
	int ret = 0;
	while(y){
		ret = max(ret, idx[y]);
		y -= y & -y;
	}
	return ret;
}

vector<int> com;
int cidx(int x)
{
	return upper_bound(com.begin(), com.end(), x) - com.begin() - 1;
}

int pos[200010];

int main()
{
	int n, k, i;
	scanf("%d%d", &n, &k);
	for(i=0; i<n; i++)
		scanf("%d", &arr[i]);

	for(bp=1; bp<n; bp *= 2);

	for(i=0; i<n; i++)
		com.push_back(arr[i]);
	sort(com.begin(), com.end());
	com.erase(unique(com.begin(), com.end()), com.end());

	int p = min_element(arr, arr + n) - arr;

	for(i=0; i<n; i++)
		pos[i] = cidx(arr[i]);

	int s = 2;
	int g = 2e9;
	while(s < g)
	{
		int x = s + (g - s) / 2;

		if(arr[p] > x)
		{
			s = x + 1;
			continue;
		}

		memset(idx, 0, sizeof idx);

		addv(cidx(arr[p]), 1);
		bool ok = 0;
		for(i = p+1; i<p+n; i++)
		{
			int c = i % n;
			int t = arr[c] <= x ? getv(0, cidx(x - arr[c])) + 1 : 0;
			addv(pos[c], t);

			if(t >= k)
			{
				ok = 1;
				break;
			}
		}

		if(ok)
			g = x;
		else
			s = x + 1;
	}

	printf("%d\n", s);
	return 0;
}




