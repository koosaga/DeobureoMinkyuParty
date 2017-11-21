#include<bits/stdc++.h>
using namespace std;
int N, K;
struct mat
{
    uint32_t arr[32];
    mat()
    {
        memset(arr, 0, sizeof(arr)); 
    }
    mat print() const
    {
        for(int i=0; i<N; ++i)
        {
            for(int j=0; j<N; ++j)
            {
                printf("%d",!!(arr[i]&(1<<j)));
            }
            puts("");
        }
    }
    mat transpose() const
    {
        mat at;
        for(int i=0; i<N; ++i)
        {
            for(int j=0; j<N; ++j)
            {
                if(arr[i]&(1u<<j))
                    at.arr[j] |= 1u<<i;
            }
        }
        return at;
    }
    static mat I()
    {
        mat i;
        for(int x=0; x<N; ++x) i.arr[x] = 1u<<x;
        return i;
    }
    mat mul(const mat& x)
    {
        mat y = x.transpose();
        mat ans;
        for(int i=0; i<N; ++i)
            for(int j=0; j<N; ++j)
                ans.arr[j] |= (__builtin_popcount(arr[i]&y.arr[j])&1) << i;
        return ans;
    }
    uint32_t mul(const uint32_t &v)
    {
        uint32_t ans = 0;
        for(int i=0; i<N; ++i)
            if(__builtin_popcount(arr[i]&v)&1)
                ans |= 1u<<i;
        return ans;
    }
    void rref()
    {
        int nr = 0;
        for(int c=0; c<N; ++c)
        {
            for(int r=nr; r<N; ++r)
            {
                if(arr[r]&(1u<<c))
                {
                    swap(arr[r], arr[nr]);
                    break;
                }
            }
            if(!(arr[nr]&(1u<<c))) continue;
            ++nr;
            for(int i=0; i<N; ++i)
            {
                if(i==nr) continue;
                if(arr[i]&(1u<<c))
                    arr[i] ^= arr[nr];
            }
        }
    }
};
bool tmain()
{
    scanf("%d%d", &N, &K); if(N==0) return false;
    mat I = mat::I();
    mat A[32];
    for(int i=0; i<N-1; ++i)
    {
        A[0].arr[i] = 1u<<(i+1);
    }
    for(int j=0; j<K; ++j)
    {
        int t; scanf("%d", &t); t--;
        A[0].arr[N-1] |= 1u<<t;
    }
    for(int i=1; i<N; ++i)
        A[i] = A[i-1].mul(A[i-1]);
    
    uint32_t s = 0; char ss[50];
    uint32_t e = 0; char ee[50];
    scanf("%s%s", ss, ee);
    
    for(int i=0; i<N; ++i)
    {
        if(ss[i] == 'r') s |= 1<<i;
        if(ee[i] == 'r') e |= 1<<i;
    }
    
    if(s==e)
    {
        puts("0");
        return true;
    }
    if(s==0 || e== 0)
    {
        puts("*");
        return false;
    }
    
    for(int i=0; i<N; ++i)
    {
        cout << A[i].mul(s) << endl;
    }
    return true;
}


int main()
{
    N = 32;
    mat T; for(int i=0; i<N; ++i) T.arr[i] = 1u<<(N-1);
    while(tmain());
}
