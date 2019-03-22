#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct vec3{
	ll x, y, z;
	vec3(): x(0), y(0), z(0) {}
	vec3(ll a, ll b, ll c): x(a), y(b), z(c) {}
	vec3 operator*(const vec3 &v)const{
		return vec3(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
	}
	vec3 operator-(const vec3 &v)const{
		return vec3(x - v.x, y - v.y, z - v.z);
	}
	vec3 operator-() const{return vec3(-x, -y, -z); }
	ll dot(const vec3 &v) const{ return x * v.x + y * v.y + z * v.z; }
}a[4];

int main(){
	int tc; cin >> tc;
	while(tc--){
		for(int i=0; i<4; i++){
			int x, y, z;
			scanf("%d %d %d",&x,&y,&z);
			a[i] = vec3(x, y, z);
		}
		auto nxt = ((a[2] - a[0]) * (a[1] - a[0]));
		auto dap = nxt.dot(a[2]) - nxt.dot(a[3]);
		dap = abs(dap);
		printf("%.10f\n", dap / 6.0);
	}
}
