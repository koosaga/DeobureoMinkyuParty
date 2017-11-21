#include<bits/stdc++.h>
int main()
{
    int K;
    std::vector<int> a;
    scanf("%d", &K);
    for(int i=100; i>=4; --i)
    {
        int cnt = i*(i-1)*(i-2)*(i-3)/24;
        while(K>=cnt)
        {
            K-=cnt;
            a.push_back(i);
        }
    }
    a.push_back(0);
    reverse(a.begin(), a.end());
    for(int i=0; i<(int)a.size()-1; i++)
    {
        for(int j=0;j<a[i+1]-a[i];++j)
        {
            putchar('a');
        }
        putchar('b');
    }
    puts(" aaaab");
}
