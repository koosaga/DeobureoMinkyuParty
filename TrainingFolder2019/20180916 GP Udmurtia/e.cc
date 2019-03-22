#include<bits/stdc++.h>

using namespace std;

#ifdef LOCAL
int ans[1010];
int tmp[1010];
#endif


int mem[1010][1010];

int cnt = 0;
int query(int a, int b)
{
	assert(a <= b);
	if(mem[a][b] != -1)
		return mem[a][b];

	cnt++;
	if(cnt > 18000)
		return -1;

	#ifndef LOCAL
		printf("? %d %d\n", a, b);
		fflush(stdout);

		scanf("%d", &mem[a][b]);
	#else
		if(rand() % 2)
			mem[a][b] = tmp[b] - tmp[a - 1];
		else
		{
			int t = rand() % (b - a + 1);
			if(t == tmp[b] - tmp[a - 1])
				t++;
			mem[a][b] = t;
		}
	#endif
	return mem[a][b];
}

int arr[1010];
int sum[1010];
int res[1010];
int pref[1010];

const int N = 1000;
const int C = 85;
const int X1 = 18;
const int X2 = 18;
const int X3 = 18;
const int K = 38;
const int ABS = 10;

int main()
{
	int i, j;
	memset(mem, -1, sizeof mem);

#ifdef LOCAL
	srand(clock());
	for(i=1;i<=1000;i++)
		ans[i] = rand() % 2;

	for(i=1;i<=1000;i++)
		tmp[i] = tmp[i-1] + ans[i];
#endif

/*
	printf("! ");
	for(i=1;i<=1000;i++)
		printf("%d", res[i]);
	printf("\n");
	fflush(stdout);
**/
	for(int i = 1; i <= C; i++) {
		for(int rep = 0; rep < K; rep++) {
			int t = query(i, N-rep) - query(i+1, N-rep);
			if(t == 1) {
				sum[i] += 1;
			}else if(t == 0) {
				sum[i] -= 1;
			}
			if(abs(sum[i]) > ABS) {
				break;
			}
		}
		if(sum[i] > 0) {
			res[i] = 1;
		}else {
			res[i] = 0;
		}
		pref[i] = pref[i-1] + res[i];
	}


	for(int i = C+1; i <= N; i++) {
		int a[2] = {0,0};
		for(int j = 1; j <= (i <= 129 ? X1 : i <= 650+32-54 ? X2 : X3); j++) {
			int t = query(j, i) - (pref[i-1] - pref[j-1]);
			if(0 <= t && t <= 1) {
				a[t] += 1;
			}
			if(abs(a[0] - a[1]) > ABS - i/200) {
				break;
			}
		}
		if(a[0] > a[1]) {
			res[i] = 0;
		}else {
			res[i] = 1;
		}
		pref[i] = pref[i-1] + res[i];
	}


#ifdef LOCAL

int xx = 0,yy=0;
	for(i=1;i<=1000;i++)
	{
		if(ans[i] != res[i])
		{
			if(i<=C)xx++; else yy++;
			//puts("WRONG");
			//return 0;
			printf("%d\n", i);
		}
	}
printf("xx = %d\n", xx);
printf("yy = %d\n", yy);
printf("cnt = %d\n", cnt);
	printf("! ");
	for(int i = 0; i < 1000; i++) putchar((res[i+1] ^ ans[i+1]) ? '#' : '.');
		puts("");
#else
	printf("! ");
	for(int i = 0; i < 1000; i++) putchar(res[i+1] + '0');
		puts("");
	fflush(stdout);
#endif
	
	return 0;
}
