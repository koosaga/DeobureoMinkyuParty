#include<bits/stdc++.h>
using namespace std;
int H, W;

struct board
{
    char dat[6][6];
};

board fucked;
board result;


vector<int> n2v(int x);
int v2n(vector<int> x);
board v2b(vector<int> x);
vector<int> b2v(board x);
vector<vector<int> > mapper;

double matrix[252][252];
double b[252];

double inv[252][252];

void Gaussian()
{
    int N = mapper.size(); 
    for(int i=0; i<N; ++i) inv[i][i] = 1;
    for(int i=0; i<N; ++i)
    {
        int maxi = i;
        for(int j=i+1; j<N; ++j)
            if(abs(matrix[maxi][i])<abs(matrix[j][i]))
                maxi = j;
        for(int j=0; j<N; ++j)
        {
            swap(matrix[maxi][j], matrix[i][j]);
            swap(inv[maxi][j], inv[i][j]);
        }
        double targ = matrix[i][i];
        for(int j=0; j<N; ++j)
        {
            matrix[i][j] /= targ;
            inv[i][j] /= targ;
        }
        for(int j=0; j<N; ++j)
        {
            if(j==i) continue;
            targ = matrix[j][i];
            for(int k=0; k<N; ++k)
            {
                matrix[j][k] -= matrix[i][k] * targ;
                inv[j][k] -= inv[i][k] * targ;
            }
        }
    }
}

void calculateTransition()
{
    for(int A=0; A<mapper.size(); ++A)
    {
        for(int i=1; i<=H; ++i)
            for(int j=1; j<=W; ++j)
            {
                board TX = v2b(n2v(A));
        
                for(int ii = 0; ii < i; ++ii)
                    for(int jj=0; jj < j; ++jj) 
                        TX.dat[ii][jj] = 'W';
                        
                int B = v2n(b2v(TX));
                for(int ii = 0; ii < i; ++ii)
                    for(int jj=0; jj < j; ++jj) 
                        TX.dat[ii][jj] = 'B';
                int C = v2n(b2v(TX));
                matrix[A][B] += 1.0/(2*H*W);
                b[A] += (1.0*i*j)/(2*H*W);
                matrix[A][C] += 1.0/(2*H*W);
                b[A] += (1.0*i*j)/(2*H*W);

            }
    }
}

//board -> vector -> number


vector<int> n2v(int x)
{
    return mapper[x];
}
int v2n(vector<int> x)
{
    assert(binary_search(mapper.begin(), mapper.end(), x));
    return lower_bound(mapper.begin(), mapper.end(), x) - mapper.begin();
}

void init()
{
    //length W, number: [0, H]
    int possible = 1; for(int i=0; i<W; ++i) possible *= (H+1);
    for(int b = 0; b<possible; ++b)
    {
        int bb = b;
        vector<int> r;
        for(int i=0; i<W; ++i)
        {
            r.push_back(bb%(H+1));
            bb /= (H+1);
        }
        bool sorted = true;
        for(int i=0; i<W-1; ++i)
            if(r[i] > r[i+1])
                sorted = false;
        if(sorted) mapper.push_back(r);
    }
    sort(mapper.begin(), mapper.end());
}

board v2b(vector<int> x)
{
    board res;
    for(int j=0; j<W; ++j)
    {
        for(int i=0; i<H-x[j]; ++i)
            res.dat[i][j] = 'B'^'W'^result.dat[i][j];
        for(int i=H-x[j]; i<H; ++i)
            res.dat[i][j] = result.dat[i][j];
    }
    return res;
}
vector<int> b2v(board x)
{
    vector<int> matchcount;
    for(int j=0; j<W; ++j)
    {
        int i;
        for(i=H-1; i>=0; --i)
        {
            if(result.dat[i][j] != x.dat[i][j]) break;
        }
        matchcount.push_back(H-1-i);
    }
    for(int j=W-2; j>=0; --j)
        matchcount[j] = min(matchcount[j+1], matchcount[j]);
    return matchcount;
}


int main()
{
    scanf("%d%d", &H, &W);
    for(int i=0; i<H; ++i)
        scanf("%s", fucked.dat[i]);
    for(int i=0; i<H; ++i)
        scanf("%s", result.dat[i]);
    init();
    
    calculateTransition();
    
    int N = mapper.size();

    b[N-1] = 0;
    for(int i=0; i<N; ++i)
        matrix[N-1][i] = 0;

    for(int i=0; i<N; ++i)
    {
        for(int j=0; j<N; ++j)
        {
            matrix[i][j] = -matrix[i][j];
        }
        matrix[i][i] += 1;
    }

    Gaussian();

    int x = v2n(b2v(fucked));
    double ans = 0;
    for(int i=0; i<N; ++i)
        ans += inv[x][i] * b[i];
    printf("%.12f\n", ans);
    return 0;
        
}


























