#include<bits/stdc++.h>
int main()
{
    int N; std::cin >> N; std::cout << N << std::endl;
    int ans = N;
    for(int i=0; i<2*(N-1); ++i)
    {
        int t; std::cin >> t;
        std::cout << t;
        std::cout << (i%2?"\n":" ");
        ans ^= t;
    }
    assert(ans==0);
    puts("OK");
}
