#include<bits/stdc++.h>
using namespace std;
int c[100][100];
int p[100][100][100];

using real_t = long double;
using VD = vector<real_t>;
using VVD=  vector<VD>;
const real_t EPS = 1e-9;

struct Simplex
{
    int m, n;
    vector<int> B, N;
    VVD D;
    Simplex(const VVD& A, const VD& b, const VD& c)
    : m(b.size()), n(c.size()), N(n+1), B(m), D(m+2, VD(n+2))
    {
        for(int i=0; i<m; ++i) for(int j=0; j<n; ++j) D[i][j] = A[i][j];
        for(int i=0; i<m; ++i) B[i] = n+i, D[i][n] = -1, D[i][n+1] = b[i];
        for(int j=0; j<n; ++j) N[j] = j, D[m][j] = -c[j];
        N[n]=-1; D[m+1][n] = 1;
    }
    void Pivot(int r, int s)
    {
        real_t inv = 1/D[r][s];
        for(int i=0; i<m+2; ++i)
            for(int j=0; j<n+2; ++j)
                if(i!=r&&j!=s)
                    D[i][j] -= D[r][j]*D[i][s]*inv;
        for(int i=0; i<m+2; ++i) if(i!=r) D[i][s] *= -inv;
        for(int j=0; j<n+2; ++j) if(j!=s) D[r][j] *= inv;
        D[r][s] = inv; swap(B[r], N[s]);
    }
    bool Phase(bool p)
    {
        int x = m +p;
        while(true)
        {
            int s = -1;
            for(int j=0; j<n; ++j)
            {
                if(!p && N[j] ==-1) continue;
                if(s==-1||D[x][j]<D[x][s]) s= j;
            }
            if(D[x][s]>-EPS) return true;
            int r= -1;
            for(int i=0; i<m; ++i)
            {
                if(D[i][s]<=EPS) continue;
                if(r==-1 || D[i][n+1]/D[i][s]<D[r][n+1]/D[r][s]) r=i;
            }
            if(r==-1) return false;
            Pivot(r, s);
        }
    }
    real_t solve(VD &x)
    {
        int r = 0;
        for(int i=1; i<m; ++i) if(D[i][n+1]<D[r][n+1]) r=i;
        if(D[r][n+1]<-EPS)
        {
            Pivot(r, n);
            if(!Phase(1)||D[m+1][n+1]<-EPS) return -1/0.0;
            for(int i=0; i<m; ++i) if(B[i] == -1)
            {
                int s = min_element(D[i].begin(), D[i].end() -1) - D[i].begin();
                Pivot(i, s);
            }
        }
        if(!Phase(0)) return 1/0.0;
        x = VD(n);
        for(int i=0; i<m; ++i) if(B[i]<n) x[B[i]] = D[i][n+1];
        return D[m][n+1];
    }
};

int main()
{
    int N, M;
    scanf("%d%d",&N, &M);
    VVD A;
    VD B;
    for(int i=0; i<M; ++i)
        for(int j=0; j<N; ++j)
        {
            scanf("%d",&c[i][j]);
            int sum =0;
            for(int k=0;k<=N; ++k)
            {
                scanf("%d", &p[i][j][k]);
                sum += p[i][j][k];
            }
            
            VD x;
            for(int k=0; k<=N; ++k)
                x.push_back(-p[i][j][k]/(real_t)sum);
            x[j] += 1;
            A.push_back(x);
            B.push_back((real_t)c[i][j]);
        }
    {
        VD x;
        for(int k=0; k<N; ++k)
            x.push_back(0);
        x.push_back(1);
        
        A.push_back(x);
        B.push_back(0.0);
    }
    /*
    for(int i=0; i<A.size(); ++i)
    {
        for(auto x: A[i]) cout << x << " " ;
        cout << B[i] << endl;
    }
    */
    VD C;
    C.push_back((real_t)1);
    for(int i=0; i<N; ++i) C.push_back((real_t)0);
    VD blank;
    printf("%.12Lf\n", Simplex(A, B, C).solve(blank));
    return 0;
}
