#include<bits/stdc++.h>
using namespace std;

vector<long> LEFT;
vector<long> RIGHT;


void add(vector<long>& arr, long x)
{
    int N = arr.size();
    for(int i=0; i<N; ++i)
        arr.push_back(arr[i] + x);
}

int N;
int main()
{
    scanf("%d", &N);
    int a[25];
    for(int i=0; i<N; ++i)
        scanf("%d", a+i);
    LEFT.push_back(0l);
    RIGHT.push_back(0l);
    for(int i=0; i<N/2; ++i)
        add(LEFT, a[i]);
    for(int i=N/2; i<N; ++i)
        add(RIGHT, a[i]);
    sort(LEFT.begin(), LEFT.end());
    sort(RIGHT.begin(), RIGHT.end());
    int ltp = 0;
    int rtp = RIGHT.size() - 1;
    long long d = 0;
    while(ltp < LEFT.size() || rtp >= 0)
    {
        if(ltp == LEFT.size()) --rtp;
        if(rtp == -1) ++ltp;
        if(LEFT[ltp] + RIGHT[rtp] > 0)
            --rtp;
        else
            ++ltp;
    }
}

























