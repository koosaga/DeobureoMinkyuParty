#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
typedef long long lint;
typedef pair<int, int> pi;

int a[4];
int b[805][15];

void place(int x, int y, int c, int l){
	for(int i=x; i<x+l; i++) b[i][y] = c;
}

int main(){
	cin >> a[0] >> a[1] >> a[2] >> a[3];
	if(a[3] % 2 == 0){
		b[1][1] = b[1][2] = b[2][1] = 1;
		b[1][3] = b[1][4] = b[2][4] = 2;
		int cnt = 3;
		int pos = 1;
		for(int i=0; i<a[3] / 2 - 1; i++){
			if(pos == 1){
				b[cnt][pos] = b[cnt+1][pos] = b[cnt+1][pos+1] = cnt;
				b[cnt][pos+3] = b[cnt+1][pos+3] = b[cnt+1][pos+4] = cnt+1;
				cnt += 2;
			}
			else{
				b[cnt][pos] = b[cnt+1][pos-1] = b[cnt+1][pos] = cnt;
				b[cnt][pos+3] = b[cnt+1][pos+3] = b[cnt+1][pos+2] = cnt+1;
				cnt += 2;
			}
			pos = 3 - pos;
		}
		int m0 = a[0] % 2;
		int m1 = a[1] % 2;
		int m2 = a[2] % 2;
		if(m0 == 0 && m1 == 0 && m2 == 0){
			int pos2 = cnt;
			for(int i=0; i<a[0] / 2 - 1; i++){
				place(pos2, pos, cnt++, 1);
				place(pos2, pos+3, cnt++, 1);
				pos2 += 1;
			}
			for(int i=0; i<a[1] / 2 - 1; i++){
				place(pos2, pos, cnt++, 1);
				place(pos2, pos+3, cnt++, 1);
				pos2 += 2;
			}
			for(int i=0; i<a[2] / 2; i++){
				place(pos2, pos, cnt++, 1);
				place(pos2, pos+3, cnt++, 1);
				pos2 += 3;
			}
			b[pos2][pos] = b[pos2+1][pos] = cnt++;
			b[pos2][pos+3] = b[pos2+1][pos+3] = cnt++;
			b[pos2][pos+1] = cnt++;
			b[pos2][pos+2] = cnt++;
		}
		if(m0 == 0 && m1 == 1 && m2 == 0){
			int pos2 = cnt;
			for(int i=0; i<a[0] / 2 - 1; i++){
				place(pos2, pos, cnt++, 1);
				place(pos2, pos+3, cnt++, 1);
				pos2 += 1;
			}
			for(int i=0; i<a[1] / 2; i++){
				place(pos2, pos, cnt++, 1);
				place(pos2, pos+3, cnt++, 1);
				pos2 += 2;
			}
			for(int i=0; i<a[2] / 2; i++){
				place(pos2, pos, cnt++, 1);
				place(pos2, pos+3, cnt++, 1);
				pos2 += 3;
			}
			b[pos2][pos] = cnt++;
			b[pos2][pos+1] = b[pos2][pos+2] = cnt++;
			b[pos2][pos+3] = cnt+;
		}
		if(m0 == 1 && m2 == 1 && m1 == 0){
			for(int i=0; i<a[0] / 2 ; i++){
				place(pos2, pos, cnt++, 1);
				place(pos2, pos+3, cnt++, 1);
				pos2 += 1;
			}
			for(int i=0; i<a[1] / 2; i++){
				place(pos2, pos, cnt++, 1);
				place(pos2, pos+3, cnt++, 1);
				pos2 += 2;
			}
			for(int i=0; i<a[2] / 2; i++){
				place(pos2, pos, cnt++, 1);
				place(pos2, pos+3, cnt++, 1);
				pos2 += 3;
			}
			b[pos2][pos] = cnt++;
			for(int i=pos+1; i<pos+4; i++){
				b[pos2][i] = cnt;
			}
		}
		if(m0 == 1 && m1 == 1 && m2 == 1){
			for(int i=0; i<a[0] / 2 ; i++){
				place(pos2, pos, cnt++, 1);
				place(pos2, pos+3, cnt++, 1);
				pos2 += 1;
			}
			for(int i=0; i<a[1] / 2; i++){
				place(pos2, pos, cnt++, 1);
				place(pos2, pos+3, cnt++, 1);
				pos2 += 2;
			}
			for(int i=0; i<a[2] / 2; i++){
				place(pos2, pos, cnt++, 1);
				place(pos2, pos+3, cnt++, 1);
				pos2 += 3;
			}
			b[pos2][pos] = cnt++;
			b[pos2][pos+3] = cnt;
			b[pos2+1][pos+3] = cnt++;
			for(int i=pos+0; i<pos+3; i++){
				b[pos2][i] = cnt;
			}
		}
		puts("800 10");
		for(int i=0;i <800; i++){
			for(int j=0; j<10; j++){
				printf("%d ", b[i][j]);
			}
		}
		return 0;
	}
	b[1][1] = b[1][2] = b[2][1] = 1;
	b[1][3] = b[1][4] = b[2][4] = 2;
	b[3][1] = b[3][2] = b[4][2] = 3;
	int pos = 2;
	int lst = 5;
	int cnt = 4;
	for(int i=0; i<a[3] / 2 - 1; i++){
		if(pos == 2){
			place(lst, pos, cnt, 1);
			place(lst, pos-1, cnt, 2);
			cnt++;
			place(lst-2, pos+2, cnt, 1);
			place(lst-2, pos+3, cnt, 2);
			cnt++;
		}
		else{
			place(lst, pos, cnt, 1);
			place(lst, pos+1, cnt, 2);
			cnt++;
			place(lst-2, pos+4, cnt, 1);
			place(lst-2, pos+3, cnt, 2);
			cnt++;
		}
		pos = 3 - pos;
		lst += 2;
	}
	int m0 = a[0] % 2;
	int m1 = a[1] % 2;
	int m2 = a[2] % 2;
	if(m0 * 1 + m1 * 2 + m2 * 3 == 1){
		place(lst - 2, 6 - pos, cnt, 2);
		for(int i=0; i<3; i++){
			for(int j=0; j<a[i]/2; j++){
				place(lst, pos, cnt, i+1);
				cnt++;
				place(lst, pos+2, cnt, i+1);
				cnt++;
				lst += i+1;
			}
		}
		place(lst-1, pos+1, cnt, 1);
	}
	if(m0 * 1 + m1 * 2 + m2 * 3 == 3){
		for(int i=0; i<3; i++){
			for(int j=0; j<a[i]/2; j++){
				place(lst, pos, cnt, i+1);
				cnt++;
				place(lst, pos+2, cnt, i+1);
				cnt++;
				lst += i+1;
			}
		}
		for(int i=0; i<3; i++){
			b[lst][pos+i] = cnt;
		}
	}
	if(m0 * 1 + m1 * 2 + m2 * 3 == 5){

	}
}
