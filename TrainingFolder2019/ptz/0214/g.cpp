#include<cstdio>
#include<algorithm>
#include<map>
#include<string>
using namespace std;
int n = 9;
char w[20][20][20];
map<string,int>Map1[9], Map2[9], Map3[9];
int main(){
	int TC, i, j;
	scanf("%d",&TC);
	while(TC--){
		for(i=0;i<9;i++){
			Map1[i].clear();
			Map2[i].clear();
			Map3[i].clear();
		}
		int ck1 = 0;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				scanf("%s",w[i][j]);
				if(Map1[i][w[i][j]])ck1=1;
				Map1[i][w[i][j]]=1;
				if(Map2[j][w[i][j]])ck1=1;
				Map2[j][w[i][j]]=1;
				if(Map3[(i/3)*3+(j/3)][w[i][j]])ck1=1;
				Map3[(i/3)*3+(j/3)][w[i][j]]=1;
			}
		}

		if(!ck1)puts("all 3");
		else puts("not");
	}
}
