#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;

bool doable(int n, int m, int k, vector<pi> &v, pi q){
	int sx = q.first - k + 1;
	int sy = q.second - k + 1;
	int ex = q.first + k - 1;
	int ey = q.second + k - 1;
	for(auto &i : v){
		if(sx <= i.first && i.first <= ex && sy <= i.second && i.second <= ey){
			return false;
		}
	}
	return true;
}

bool sexgame(int n, int m, int k, vector<pi> SEX){
	for(int i=1; i<=n-k+1;i++){
		for(int j=1; j<=m-k+1; j++){
			if(doable(i, j, k, SEX, pi(i, j))){
				SEX.push_back(pi(i, j));
				if(!sexgame(n, m, k, SEX)) return true;
				SEX.pop_back();
			}
		}
	}
	return false;
}

int brute(int n, int m, int k){
	int ans = 0;
	for(int i=1; i<=n-k+1; i++){
		for(int j=1; j<=m-k+1; j++){
			vector<pi> v;
			v.push_back(pi(i, j));
			if(!sexgame(n, m, k, v)) ans++;
		}
	}
	return ans;
}

int main()
{
    long long n, m, k;
    scanf("%lld%lld%lld", &n, &m, &k);
    //printf("BRUTE%d\n", brute(n, m, k));
    if(n > m)
        swap(n, m);
    
    long long r;
    if(2*k > n)
    {
        if(2*k > m)
            r = (n-k+1)*(m-k+1);
        else if(3*k > m)
            r = (n-k+1)*(3*k-m-1);
        else
            r = (n-k+1)*(1);
    }
    else if(3*k > m)
    {
        r = (3*k-n-1)*(3*k-m-1);
    }
    else if(3*k == n)
    {
        r = 1;
        
        //r += 8*(k-1);
        //r += 4;
    }
    else if(3*k == m)
    {
        r = 3*k-n-1;
        
        r += 4;
        r += 2*(3*k-n-1) - 4;
        r += 6;
    }
    else
        assert(0);
        
    if(k==1)
    {
        if((n*m)%2==0) r = 0;
        else r = n*m;
    }
    
    printf("%lld\n", r);
    return 0;
}
