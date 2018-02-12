#include<bits/stdc++.h>
using namespace std;
const int MOD = 10000000;
int N;
string usable;
int tp = 0;
string str1[20];
string str2[20];
void Do(string, int);
map<vector<int>, int > M;
vector<vector<int> > VV;
vector<vector<int> > transition;
pair<bool, vector<int> > apply(vector<int> x, char c)
{
    for(int i=0; i<tp; ++i)
    {
        if(x[i] == -(int)(str1[i].size())) c=c;
        else if(x[i] == (int)(str2[i].size())) c=c;
        else if(c == str1[i][0]) x[i] = -1;
        else if(c == str2[i][0]) x[i] = 1;
        else if(x[i] < 0 && c == str1[i][-x[i]]) --x[i];
        else if(x[i] > 0 && c == str2[i][ x[i]]) ++x[i];
        else x[i] = 0;
        //hukanou
        if(x[i] == (int)str2[i].size()) return make_pair(false, x);
    }
    return make_pair(true, x);
}
int dfs(vector<int> x)
{
    if(M.find(x) != M.end()) return M[x];
    M[x] = VV.size();
    VV.push_back(x);
    int Mx = VV.size()-1;
    transition.push_back(vector<int>(0));
    for(int i=0; i<(int)usable.size(); ++i)
    {
        auto res = apply(x, usable[i]);
        if(res.first)
            transition[Mx].push_back( dfs(res.second));
        //add transition x->res
    }
    return Mx;
}
vector<int> DP[501];
int main()
{
    string buf;
    cin >> N >> usable >> buf;
    reverse(usable.begin(), usable.end());
    reverse(buf.begin(), buf.end()); buf = buf + "|";
    string buf2 = "";
    for(char x: buf)
    {
        if(x == '|')
        {
            Do(buf2, tp++);
            buf2 = "";
        }
        else buf2 += x;
    }
    vector<int> x(tp, 0);
    dfs(x);
    
    //printf("%d\n", (int)VV.size());
    //fflush(stdout);
    
    DP[0].resize(VV.size());
    DP[0][0] = 1;
    for(int i=1; i<=N; ++i)
    {
        DP[i].resize(VV.size());
        for(int j=0; j<VV.size(); ++j)
            for(auto x: transition[j])
            {
                DP[i][x] = (DP[i][x] + DP[i-1][j])%MOD;
            }
    }     
    int ans = 0;
    for(int i=0; i<VV.size(); ++i)
    {
        bool flag = true;
        for(int j=0; j<VV[i].size(); ++j)
        {
            if(VV[i][j] == str2[j].size())
            {
                flag = false;
                break;
            }
        }
        if(flag) ans = (ans+DP[N][i])%MOD;
        //printf("%3d: %3d\n", i, DP[N][i]);    
    }
    printf("%d\n", ans);
    return 0;
    
    for(int i=0; i<tp; ++i)
        cout << str1[i] << " " << str2[i] << endl;
    
    for(auto y: M)
    {
        printf("%3d:", y.second);
        for(auto z: y.first)
            printf("%3d ", z);
        puts("");
    }
    int xx = 0;
    for(auto v: transition)
    {
        printf("%3d:", xx++);
        for(auto y: v) printf("%3d", y);
        puts("");
    }
}
void Do(string x, int ind)
{
    string buf = "";    
    for(char y: x)
    {
        if(y=='>')
        {
            str1[ind] = buf;
            buf = "";
        }
        else buf += y;
    }
    str2[ind] = buf;
}
