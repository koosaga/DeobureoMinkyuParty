#include<bits/stdc++.h>
using namespace std;

struct pos
{
	long long x, y;
	bool operator <(const pos &a) const
	{
		return x != a.x ? x < a.x : y < a.y;
	}
};

long long ccw(pos a, pos b, pos c){
	int dx1 = b.x - a.x;
	int dy1 = b.y - a.y;
	int dx2 = c.x - a.x;
	int dy2 = c.y - a.y;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

pos arr[100010];
long long area(int s, int g)
{
	if(g < s)
		return 0LL;
	vector<pos> L, R;
	for(int i=s; i<=g; i++){
		while(L.size() >= 2 && ccw(L[L.size()-2], L.back(), arr[i]) <= 0){
			L.pop_back();
		}
		L.push_back(arr[i]);
	}
	for(int i=g; i>=s; i--){
		while(R.size() >= 2 && ccw(R[R.size()-2], R.back(), arr[i]) <= 0){
			R.pop_back();
		}
		R.push_back(arr[i]);
	}
	long long ans = 0;
	for(int i=2; i<L.size(); i++) ans += ccw(L[0], L[i-1], L[i]);
	for(int i=2; i<R.size(); i++) ans += ccw(R[0], R[i-1], R[i]);
	return ans;
}

vector<int> com;
int n;
long long s;
long long diff(int x)
{
	return abs(area(0, com[x] - 1) - area(com[x], n - 1));
}

int main()
{
	int i;
	scanf("%d%lld", &n, &s);
	s *= 2;
	for(i=0;i<n;i++)
		scanf("%lld%lld", &arr[i].x, &arr[i].y);

	sort(arr, arr+n);

	for(i=0;i<=n;i++)
		if(i == 0 || i == n || arr[i-1].x != arr[i].x)
			com.push_back(i);

	int a, b, m;
	a = 0;
	b = (int)com.size() - 1;
	while(a < b)
	{
		m = (a + b + 1) / 2;

		if(area(0, com[m] - 1) > area(com[m], n-1))
			b = m-1;
		else
			a = m;
	}

	int x = a;

	a = 0;
	b = x;

	long long q1 = diff(a);
	long long q2 = diff(b);

	long long minkyu= 1e18;
	auto minkyu_fucking_jaji = [&](const long long &a, const long long &b){
		if(abs(a - s) == abs(b - s)) return a < b;
		return abs(a - s) < abs(b - s);
	};
	if(q1 >= s && q2 >= s)
	{
		long long ans = min(q1, q2);
		minkyu = min(minkyu, ans, minkyu_fucking_jaji);
	}
	else if(q1 <= s && q2 <= s)
	{
		long long ans = max(q1, q2);
		minkyu = min(minkyu, ans, minkyu_fucking_jaji);
	}

	while(a < b)
	{
		m = (a + b) / 2;

		if(diff(m) > s)
			a = m + 1;
		else
			b = m;
	}

	q1 = diff(a);
	q2 = diff(a - 1);

	if(abs(q1 - s) <= abs(q2 - s))
		minkyu = min(minkyu, q1, minkyu_fucking_jaji);
	else
		minkyu = min(minkyu, q2, minkyu_fucking_jaji);



	a = x+1;
	b = (int)com.size() - 1;

	q1 = diff(a);
	q2 = diff(b);

	if(q1 >= s && q2 >= s)
	{
		minkyu = min(minkyu, min(q1, q2), minkyu_fucking_jaji);
	}
	else if(q1 <= s && q2 <= s)
	{
		minkyu = min(minkyu, max(q1, q2), minkyu_fucking_jaji);
	}

	while(a < b)
	{
		m = (a + b + 1) / 2;

		if(diff(m) > s)
			b = m - 1;
		else
			a = m;
	}

	q1 = diff(a);
	q2 = diff(a + 1);

	if(abs(q1 - s) <= abs(q2 - s))
		minkyu = min(minkyu, q1, minkyu_fucking_jaji);
	else
		minkyu = min(minkyu, q2, minkyu_fucking_jaji);



	
	printf("%.10f\n", minkyu * 0.5);
}









