#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+11;
int N;
int a[MAXN];
int ans[MAXN];
int invans[MAXN];
vector<int> prc;
int qq = -1;
int solve(int x, int y)
{
    if(x==y) return 0;
    if(ans[x]>=y) return 0;
    int ret = (x+y)&1;
    int cnt = lower_bound(prc.begin(), prc.end(), x+y) -prc.begin();
    ret ^= cnt&1;
    ret ^= !qq;
    return ret;
}


int dp1[MAXN], dp2[MAXN];

int main()
{
    scanf("%d", &N);
    for(int i=0; i<N; ++i) scanf("%d", a+i);
    dp1[N-1] = dp2[N-1] = N-1;
    for(int i=N-2; i>=0; i--){
        if(a[i] >= a[i+1]) dp1[i] = dp1[i+1];
        else dp1[i] = i;
        if(a[i] <= a[i+1]) dp2[i] = dp2[i+1];
        else dp2[i] = i;
    }
    for(int i=0; i<N; i++) ans[i] = max(dp1[i], dp2[i]);
    vector<int> A, B;
    A.push_back(0); B.push_back(0);

    for(int i=0; i<N; ++i)
    {
		if(i!=0 && ans[i] != ans[i-1])
		{
		    if(qq==-1) qq = ans[i-1]+i;
		    A.push_back(ans[i-1]+i);
            B.push_back(ans[i]+i);	
            if(A[A.size()-1] %2 != A[A.size()-2]%2)  
            {
                if(B[B.size()-2]%2 == A[A.size()-1]%2)
                    prc.push_back(B[B.size()-2]);
                else
                    prc.push_back(B[B.size()-2]-1);
            }
		}        
    }
    qq%=2;

    int q; scanf("%d",&q);
    while(q--){
        int s, e;
        scanf("%d %d",&s,&e);
        s = s + 1;
        e = N - e;
        s--;
        e--;
        printf(solve(s, e) ? "Alice\n" : "Bob\n");
    }
}
