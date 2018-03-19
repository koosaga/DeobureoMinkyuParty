#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;

char a[MAXN], b[MAXN];

int main(){
	scanf("%s %s", a, b);
	int a1 = 0, b1 = 0;
	for(int i=0; a[i]; i++) a1 = (a1 * 10 + a[i] - '0') % 100000;
	for(int i=0; b[i]; i++) b1 = (b1 * 10 + b[i] - '0') % 100000;
	a1 += 100000 - b1;
	a1 %= 100000;
	if(a1 > 90000) printf("%d\n", a1 - 100000);
	else printf("%d\n", a1);
}
