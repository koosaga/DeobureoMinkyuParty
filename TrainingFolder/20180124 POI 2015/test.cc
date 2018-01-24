#include<bits/stdc++.h>
using namespace std;
int fildl[1010101];
int main()
{
    set<int> V;
    for(int i=0; i<(1<<25); ++i)
    {
        int ans = 0;
        for(int j=0; j<25; ++j)
        {
            if(i&(1<<j)) ans += (j+1)*(j+1);
        }
        V.insert(ans);
        fildl[ans] = 1;
    }
    int cnt = 0;
    printf("{");
    for(int i=0; i<2500; ++i)
        if(!fildl[i])
        { ++cnt;
            printf("%d, ", i);}
    puts("}");    printf("%d\n", cnt);

}
