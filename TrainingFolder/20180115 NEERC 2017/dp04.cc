#include<iostream> 
#include<string> 
#include<cstring> 
#include<algorithm> 
#define MOD 1000000007 
#define ll long long 
using namespace std; 
  
ll cache[5001][5001]; 
int N; 
string input; 
  
ll solve(int n, int k) { 
    if (n == 1 && k == 0) return 1; 
    if (n < 0 || k < 0) return 0; 
    if (n == k) return 1; 
    if (k > n) return 0; 
    ll& ret = cache[n][k]; 
    if (ret != -1) return ret; 
  
    ret = 0; 
    ret += 2 * solve(n - 1, k + 1) + solve(n - 1, max(0, k - 1)); 
    ret %= MOD; 
    return ret; 
} 
  
int main() { 
    memset(cache, -1, sizeof(cache)); 
    cin >> N; 
    cin >> input; 
  
    cout << solve(N, input.size()); 
}
