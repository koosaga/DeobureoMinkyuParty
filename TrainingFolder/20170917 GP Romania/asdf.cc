#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class ChromosomalCrossover2
{
public:
    int s(string a, string b)
    {
        int N = a.size();
        int ans = 0;
        for(int i=0; i<N; ++i)
        {
            for(int j=0; j<N; ++j)
            {
                int cnt = 0;
                for(int k=0; i+k<N && j+k<N; ++k)
                {
                    if(a[i+k] == b[j+k]) ++cnt;
                    else break;
                }
                ans = max(ans, cnt);
            }
        }
        return ans;
    }
    int maximalLength(string A, string B)
    {
        std::cout << A << " " << B << endl;
        int N = A.size();
        int ans = 0;
        for(int i=0; i<(1<<N); ++i)
        {
            string a = "", b="";
            for(int j=0; j<N; ++j)
            {
                if(i&(1<<j))
                {
                    a += A[j]; b += B[j];
                }
                else
                {
                    b += A[j]; a += B[j];
                }
            }
            //std::cout << a << " " << b << endl;
            ans = max(ans, s(a, b));
        }
        return ans;
    }
};

#define pb push_back
class ChromosomalCrossover {
public:
   int calc(string A, int a, string B, int b)
   {
    int N = A.size();
    if(a==b)
    {
        int i=0;
        for(i=0;i+a<N;++i)
        {
            if(A[a+i]!=B[b+i]) return i;
        }
        return i;
    }
    int diff = b-a; int ans = N-b;
    for(int i=0; i<diff; ++i)
    {
        int ma = 0;
        for(int t=0; t<2; ++t)
        {
            int cur = a+i;
            char c = A[cur];
            while(true)
            {
                cur += diff;
                if(cur>=N) break;
                if(B[cur]!=c) swap(A[cur],B[cur]);
                if(B[cur]!=c) break;
                c = A[cur];
            }
            ma = max(ma, cur-b);
            swap(A[a+i],B[a+i]);
        }
        ans = min(ans, ma);
    }
    return ans;
   }
   int maximalLength(string A, string B)
   {
    int n = A.size(); int ans = 0;
    for(int a=0; a<n; ++a) for(int b =0;b<n; ++b)
    {
        int l; if(a<b) l =calc(A, a,B,b);
        else l = calc(B,b,A,a);
        ans = max(ans,l);
    }
   return ans;
   }
};

int main()
{
    int N = 10;
    while(true)
    {
    ChromosomalCrossover a;
    ChromosomalCrossover2 b;
        string A = "", B = "";
        for(int i=0; i<N; ++i) A += "ACGT"[(unsigned)rand()%4];
        for(int i=0; i<N; ++i) B += "ACGT"[(unsigned)rand()%4];
        int ans1 = a.maximalLength(A, B);
        int ans2 = b.maximalLength(A, B);
        if(ans1==ans2) std::cout << A << " " << B << " " << ans1 << endl;
        else
        {
            std::cout << A << " " << B << " " << ans1 << " " << ans2 << endl;
            std::cout << "WTF!!!" << endl;
            return 0;
        }
    }
}







