#include <bits/stdc++.h>
using namespace std;

int main(){
	int t, i, j;
	scanf("%d", &t);
	for(i=0;i<t;i++)
	{
		pair<int, int> a[4];
		for(j=0;j<4;j++)
		{
			scanf("%d%d", &a[j].first, &a[j].second);
		}
		
		if(a[1] < a[0])
		    swap(a[0], a[1]);
		if(a[3] < a[2])
		    swap(a[2], a[3]);
		if(a[2] < a[0])
		{
		    swap(a[0], a[2]);
		    swap(a[1], a[3]);
		}

		if(a[0] == a[2] || a[0] == a[3] || a[1] == a[2] || a[1] == a[3] || a[0] == make_pair(0, 0) && a[1] == make_pair(1, 1) && a[2] == make_pair(0, 1) && a[3] == make_pair(1, 0))
			printf("YES\n");
		else
		    printf("NO\n");
	}
	return 0;
}
