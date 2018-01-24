#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n, ret[MAXN];
long long arr[MAXN];
bool fin[MAXN];
bool fix[MAXN];

void check(int x)
{
    x = (x%n + n) % n;
    
    if(fin[x])
        return;
    
    int y = (x+1) % n;
    
    if(!fix[x] && !fix[y])
    {
        if(arr[x] > 2*arr[y])
        {
            fin[x] = 1;
            ret[x] = x;
            
            fix[x] = 1;
            fix[y] = 1;
            
            arr[x] /= 2;
            
            check(x-1);
            check(x+1);
        }
        else if(arr[y] > 2*arr[x])
        {
            fin[x] = 1;
            ret[x] = y;
            
            fix[x] = 1;
            fix[y] = 1;
            
            arr[y] /= 2;
            
            check(x-1);
            check(x+1);
        }
    }
    else if(fix[x] && fix[y])
    {
        fin[x] = 1;
        if(arr[x] >= arr[y])
            ret[x] = x;
        else
            ret[x] = y;
    }
    else if(fix[x] && !fix[y])
    {
        if(arr[x] > arr[y])
        {
            fin[x] = 1;
            ret[x] = x;
            
            fix[y] = 1;
            
            check(x+1);
        }
        else if(arr[y] > 2*arr[x])
        {
            fin[x] = 1;
            ret[x] = y;
            
            fix[y] = 1;
            
            arr[y] /= 2;
            
            check(x+1);
        }
    }
    else if(!fix[x] && fix[y])
    {
        if(arr[y] > arr[x])
        {
            fin[x] = 1;
            ret[x] = y;
            
            fix[x] = 1;
            
            check(x-1);
        }
        else if(arr[x] > 2*arr[y])
        {
            fin[x] = 1;
            ret[x] = x;
            
            fix[x] = 1;
            
            arr[x] /= 2;
            
            check(x-1);
        }
    }
}

int main()
{
	scanf("%d", &n);
	for(int i=0;i<n;i++){
		scanf("%lld",&arr[i]); arr[i] *= 2;
	}
	
	for(int i=0;i<n;i++)
	    check(i);
	
	for(int i=0;i<n;i++)
	    if(!fin[i])
	        ret[i] = (i+1) % n;

	for(int i=0; i<n; i++) printf("%d ", ret[i] + 1);
	return 0;
}
