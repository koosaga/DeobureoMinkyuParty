#include <bits/stdc++.h>

using namespace std;

int arr[110][110];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main()
{
    int n, m, x, y, nx, ny, a, d, i, j, k;
    while(1)
    {
        scanf("%d%d", &n, &m);
        if(n == 0 && m == 0)
            return 0;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                scanf("%d", &arr[i][j]);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(arr[i][j] == 0)
                    x = i, y = j;
        for(i=0;i<m;i++)
        {
            scanf("%d", &a);
            for(d = 0; d < 4; d++)
            {
                nx = x + dx[d];
                ny = y + dy[d];
                if(0<=nx && nx<n && 0<=ny && ny<n && arr[nx][ny] == a)
                {
                    swap(arr[x][y], arr[nx][ny]);
                    x = nx;
                    y = ny;
                    break;
                }
            }
        }
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                printf("%d ", arr[i][j]);
        printf("\n");
    }
    return 0;
}

















