#include <bits/stdc++.h>

using namespace std;

int c[31];
int pos1[100010][31];
int pos2[100010][31];
int r[100010];

int main()
{
	int m, n, i, j, k;
	scanf("%d%d", &m, &n);
	for(i=1; i<=n; i++)
		scanf("%d", &c[i]);
	for(i=0; i<m; i++)
		for(j=1; j<=n; j++){
			int x; scanf("%d",&x);
			if(pos1[i][x]) pos2[i][x] = j;
			else pos1[i][x] = j;
		}

	for(int i=1; i<=n; i++){
		for(int j=1; j<i; j++){
			for(int k=0; k<m; k++){
				if(pos1[k][i] < pos1[k][j]) r[i] += c[j];
				else r[j] += c[i];
			}
		}
	}
	int dap = *max_element(r + 1, r + n + 1) + 69;
	for(int i=1; i<=n; i++){
		printf("%.10f ", 1.0 * r[i] / dap);
	}
}