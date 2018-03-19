#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1010101;
int N;
char sex[MAXN + 1];
char xes[MAXN + 1];
bool ok()
{
    for(int i=0; i<N; ++i)
        if(sex[i] == '2' || sex[i] == '3') return true;
    return false;
}
void iter()
{
    for(int i=0; i<N; ++i) xes[i] = '0';
    for(int i=0; i<N; ++i)
    {
        if(sex[i] % 2 == 1) xes[i] += 1;
        if(i!=0 && sex[i-1] > '1') xes[i] += 1;
        if(sex[i+1] > '1') xes[i] += 1;
    }
    for(int i=0; i<N; ++i) sex[i] = xes[i];
    return;
}
int main()
{
    scanf("%s", sex);
    N = strlen(sex);
    while(ok())
        iter();
    puts(sex);
}
