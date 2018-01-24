#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 10000005;

int sum[MAXN];
bool ok[MAXN];
int n;
char a[200005];
bool grp[200005];

void submit(int s){
	vector<string> ret;
	for(int i=0; i<n; i++){
		if(grp[i]){
			string str;
			str.push_back(a[i]);
			str.push_back(a[i+1]);
			ret.push_back(str);
			i++;
			continue;
		}
		else{
			string str = {a[i]};
			ret.push_back(str);
		}
	}
	for(int i=0; i<ret.size(); i++){
		printf("%s", ret[i].c_str());
		if(i + 1 < ret.size()) printf("+");
	}
	puts("");
	if(s >= 10){
		vector<int> a;
		int bs = sum[s];
		while(s){
			a.push_back(s % 10);
			s /= 10;
		}
		reverse(a.begin(), a.end());
		for(int i=0; i<a.size(); i++){
			printf("%d", a[i]);
			if(i + 1 < a.size()) printf("+");
		}
		puts("");
		if(bs >= 10) printf("%d+%d", bs/10, bs%10);
		else printf("%d", bs);
	}
	else{
		printf("%d\n%d\n", s,s);
	}
	exit(0);
}

int main(){
	for(int i=1; i<MAXN; i++){
		sum[i] = sum[i/10] + (i%10);
	}
	for(int i=0; i<MAXN; i++){
		if(sum[sum[i]] <= 9) ok[i] = 1;
	}
	scanf("%d %s", &n, a);
	int sum = 0;
	for(int i=0; i<n; i++) sum += a[i] - '0';
	if(ok[sum]) submit(sum);
	for(int i=0; i+1<n; i+=2){
		sum -= a[i]-'0';
		sum -= a[i+1]-'0';
		sum += (a[i] - '0') * 10 + (a[i+1] - '0');
		grp[i] = 1;
		if(ok[sum]) submit(sum);
	}
	for(int i=0; i+1<n; i+=2){
		sum+= a[i]-'0';
		sum+= a[i+1]-'0';
		sum-= (a[i] - '0') * 10 + (a[i+1] - '0');
		grp[i] = 0;
		if(ok[sum]) submit(sum);
	}

	for(int i=1; i+1<n; i+=2){
		sum -= a[i]-'0';
		sum -= a[i+1]-'0';
		sum += (a[i] - '0') * 10 + (a[i+1] - '0');
		grp[i] = 1;
		if(ok[sum]) submit(sum);
	}
	for(int i=1; i+1<n; i+=2){
		sum+= a[i]-'0';
		sum+= a[i+1]-'0';
		sum-= (a[i] - '0') * 10 + (a[i+1] - '0');
		grp[i] = 0;
		if(ok[sum]) submit(sum);
	}
	assert(0);
}
