#include<bits/stdc++.h>
using namespace std;
int N, M;
int c1, c2;
int A[1010101];
int B[1010101];
int main()
{
	scanf("%d%d",&N,&M);
	scanf("%d%d",&c1,&c2);
	for(int i=0; i<N; ++i) scanf("%d", A+i);
	for(int i=0; i<M; ++i) scanf("%d", B+i);
	A[N] = -1e9; A[N+1] = -1e9;  A[N+2] = 1e9; A[N+3] = 1e9;N += 4;
	sort(A, A+N); 
	int minv = 1e9;
	int minans = 0;
	for(int i=0; i<M; ++i)
	{
		auto it = lower_bound(A, A+N, B[i]);
		auto it2 = it; ++it2;
		auto it3 = it; --it3;
		if(minv>abs(B[i]-*it))
			minv = abs(B[i]-*it), minans = 0;;
		if(minv==abs(B[i]-*it))
			++minans; 
		if(minv>abs(B[i]-*it2))
			minv = abs(B[i]-*it2), minans = 0;
		if(minv==abs(B[i]-*it2))
			++minans; 
		if(minv>abs(B[i]-*it3))
			minv = abs(B[i]-*it3), minans = 0;
		if(minv==abs(B[i]-*it3))
			++minans; 
	}
	printf("%d %d\n", minv+abs(c1-c2), minans);
}