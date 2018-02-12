#include<iostream> 
#include<cstdio> 
#include<cstring> 
#include<algorithm> 
using namespace std; 
typedef long long ll; 
int n; 
int map[205][205]; 
ll dp[205][205]; 
int dy[2] = { 1,0 }; 
int dx[2] = { 0,1 }; 
  
bool Range(int y, int x) { 
    if (y > n - 1 || x > n - 1)return false; 
    return true; 
} 
ll dfs(int y, int x) { 
    ll &ret = dp[y][x]; 
  
    if (ret != -1)return ret; 
    ret = 0; 
  
    if (y == n - 1 && x == n - 1) { 
        return ret = map[y][x]; 
    } 
    for (int i = 0; i < 2; i++) { 
        int ny = y + dy[i]; 
        int nx = x + dx[i]; 
  
        if (Range(ny, nx)) { 
            ret = max(ret, dfs(ny, nx) + map[y][x]); 
        } 
    } 
    printf("%d %d %lld\n", y, x, ret);
    return ret; 
} 
int main() { 
    memset(dp, -1, sizeof dp); 
    scanf("%d", &n); 
  
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) { 
            scanf("%d", &map[i][j]); 
        } 
    } 
    cout << dfs(0, 0) << endl; 
  
    return 0; 
}
