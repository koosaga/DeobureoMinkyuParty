#include<bits/stdc++.h>
using namespace std;
int arr[202020];
int h, w, n;
pair<int, int> rm[202020];

int findUL(int, int);
int findUR(int x, int y)
{
    int ans = findUL(x, w-1-y);
    if(ans == -1) return ans;
    return (w-1)-ans;
    
}
int findUL(int x, int y)
{
    if(x<=y)
    {
        if((y-x)%2==0)
            return y-x;
        else
            return -1;
    }
    else return findUR(x-y-1, 0);
}
int findTOT(int x, int y)
{
    x %= 2*w;
    int vur = findUR(x, y);
    int vul = findUL(x, y);
    return max(vur, vul);
}
int invarr[202020];
int main()
{
    scanf("%d%d%d",&h,&w,&n);
    for(int i=0; i<n; ++i)
        scanf("%d%d",&rm[i].first, &rm[i].second);
    sort(rm, rm+n);
    for(int i=0; i<202020; ++i) arr[i] = i;
    for(int i=0; i<n; ++i)
    {
        int x = rm[i].first;
        int y1 = rm[i].second-1;
        int y2 = rm[i].second;
        swap(arr[findTOT(x, y1)], arr[findTOT(x, y2)]);
    }
    for(int i=0; i<w; ++i)
       invarr[arr[findTOT(h, i)]] = i+1;
    for(int i=0; i<w; ++i)
        printf("%d\n",invarr[i]);
    
    
    
    
    
    
    
}
