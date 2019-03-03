#include <bits/stdc++.h>
using namespace std;
using lint = long long;

int main(){
	double GR = (sqrt(5) - 1) / 2; 
	for(lint i=100; i<=2147483647; i++){
		int repa = (int)round(GR * i);
		for(int j=repa - 2; j<=repa + 2; j++){
			lint diff = 1ll * i * i - 1ll * j * j - 1ll * i * j;
			if(diff <= 30 && diff >= -30){
				fprintf(stderr, "v.eb(%d,%d);\n", i, j);
				printf("v.eb(%d,%d);\n", i, j);
			}
		}
	}
}

