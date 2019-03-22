#include <bits/stdc++.h>
using namespace std;

int arr[4];

void solve()
{
	int i;
	for(i=0; i<4; i++)
		scanf("%d", &arr[i]);
	
	sort(arr, arr + 4);
	vector<tuple<int, int, int>> res;
	
	int x = 0;
	for(i=0; i<4; i++)
		x += (1 << arr[i]);
	
	/*if(arr[0] != arr[1] && arr[1] != arr[2] && arr[2] != arr[3] && arr[2] - arr[0] == arr[3] - arr[1])
	{
		res.push_back(make_tuple(x, (1 << arr[0]) + (1 << arr[2]), (1 << arr[1]) + (1 << arr[3])));
		x = (1 << arr[1]) + (1 << arr[3]);
	}
	else */if(arr[0] != arr[1] && arr[1] != arr[2] && arr[2] != arr[3] && arr[1] - arr[0] == arr[3] - arr[2])
	{
		res.push_back(make_tuple(x, (1 << arr[0]) + (1 << arr[1]), (1 << arr[2]) + (1 << arr[3])));
		x = (1 << arr[2]) + (1 << arr[3]);
	}
	
	while(x > 1)
	{
		if(x % 2 == 1)
		{
			res.push_back(make_tuple(x, x-1, 1));
			x = x - 1;
		}
		else
		{
			res.push_back(make_tuple(x, x/2, x/2));
			x = x / 2;
		}
	}
	
	printf("%d\n", (int)res.size());
	for(auto t : res)
	{
		int x, y, z;
		tie(x, y, z) = t;
		printf("%d %d %d\n", x, y, z);
	}
}

int main()
{
	freopen("dividing.in", "r", stdin);
	freopen("dividing.out", "w", stdout);
	int t, i;
	scanf("%d", &t);
	for(i=0; i<t; i++)
		solve();
	return 0;
}
