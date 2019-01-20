#include <bits/stdc++.h>

using namespace std;

mt19937 rng(time(0));
int randint(int l, int r)
{
	return uniform_int_distribution<int>(l, r)(rng);
}

int n, v, c;

bool f(vector<int> &arr);
bool g(vector<int> &arr);

map<vector<int>, bool> fm, gm;

// Alice
bool f(vector<int> &arr)
{
	auto it = fm.find(arr);
	if(it != fm.end())
		return it->second;

	for(int i=0; i<c; i++)
	{
		for(int j=1; j<=arr[i]; j+=2)
		{
			arr[i] -= j;
			bool ok = !g(arr);
			arr[i] += j;
			if(ok)
			{
				fm[arr] = 1;
				return 1;
			}
		}
	}
	for(int i=c; i<n; i++)
	{
		for(int j=1; j<=arr[i]; j++)
		{
			arr[i] -= j;
			bool ok = !g(arr);
			arr[i] += j;
			if(ok)
			{
				fm[arr] = 1;
				return 1;
			}
		}
	}
	fm[arr] = 0;
	return 0;
}

// Bob
bool g(vector<int> &arr)
{
	auto it = gm.find(arr);
	if(it != gm.end())
		return it->second;

	for(int i=0; i<n; i++)
	{
		for(int j=1; j<=arr[i]; j++)
		{
			arr[i] -= j;
			bool ok = !f(arr);
			arr[i] += j;
			if(ok)
			{
				gm[arr] = 1;
				return 1;
			}
		}
	}
	gm[arr] = 0;
	return 0;
}

//g++ -std=c++11 -O2 -Wall -Wextra -Wshadow -o d_back d_back.cpp 
int main()
{
	//scanf("%d%d%d", &n, &v, &c);
	n = 7;
	v = 4;
	c = 2;
	
	while(1)
	{
		vector<int> arr;
		for(int i=0; i<c; i++)
			arr.push_back(randint(2, v));
		for(int i=c; i<n; i++)
			arr.push_back(randint(1, v));

		printf("nvc %d %d %d\n", n, v, c);
		for(int i=0; i<c; i++)
			printf("%d ", arr[i]);
		printf(" |  ");
		for(int i=c; i<n; i++)
			printf("%d ", arr[i]);
		puts("");

		{
			int t = 0;
			for(int i=0; i<n; i++)
				t ^= arr[i];
			printf("XOR: %d\n", t);
		}
		{
			int t = 0;
			for(int i=0; i<c; i++)
				t ^= arr[i];
			printf("ODD XOR: %d\n", t);
		}
		{
			int t = 0;
			for(int i=c; i<n; i++)
				t ^= arr[i];
			printf("NOT ODD XOR: %d\n", t);
		}

		bool ok = (int)f(arr);
		printf("res: %d\n", ok);
		if(ok)
			return 0;
	}
	return 0;
}
