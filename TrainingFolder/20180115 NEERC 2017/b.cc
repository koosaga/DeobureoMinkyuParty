#include<bits/stdc++.h>
using namespace std;
pair<int, int> v(int a, int b, int c, int t)
{
    pair<int, int> ans;
    switch(t%5)
    {
        case 0:
            ans = make_pair(2*a+c, 2*a+2*b);
            break;
        case 1:
            ans = make_pair(a+b+c,2*a+2*b);
            break;
        case 2:
            ans = make_pair(2*a+b, a+b+2*c);
            break;
        case 3:
            ans = make_pair(a+b+c, a+b+2*c);
            break;
        case 4:
            ans = make_pair(3*b+a+c,a+c);
            break;
    }
    if(t>=5)
    {
        ans = make_pair(ans.second, ans.first);
    }
    return ans;
}

int a[3];
int w, h;
int main()
{
    scanf("%d%d%d%d%d",a,a+1,a+2,&w,&h);
    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<3; ++j)
        {
            for(int k=0; k<3; ++k)
            {
                if(i==j || j==k || k==i) continue;
                for(int t=0; t<10; ++t)
                {
                    pair<int, int> ret = v(a[i], a[j], a[k], t);
                    if(ret.first <= w && ret.second <= h)
                    {
                        puts("Yes");
                        return 0;
                    }
                }
            }
        }
    }
    puts("No");
    return 0;
}
