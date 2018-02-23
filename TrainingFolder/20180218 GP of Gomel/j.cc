#include<bits/stdc++.h>
using namespace std;
int T;
int isJoker()
{
    char buf[3];
    scanf("%s", buf);
    return buf[1] == 'J';
}
int main()
{
    scanf("%d", &T);
    while(T--)
    {
        for(int i=0; i<6; ++i) isJoker();
        int cnt = 0;
        for(int i=0; i<6; ++i) cnt += isJoker();
        if(cnt==2) puts("Johann");
        else puts("Sebastian");
        for(int i=0; i<42; ++i) isJoker();
        scanf("%*s");
    }
}

//RIP for Bach.

