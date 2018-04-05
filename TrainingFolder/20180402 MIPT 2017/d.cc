#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
void FUCK()
{
    puts("NO");
    exit(0);
}

int rotate(vector<int> AA, vector<int> SS){
	vector<int> fail(AA.size() + 1);
	int n = AA.size();
	int p = 0;
	for(int i=1; i<n; i++){
		while(p && AA[i] != AA[p]) p = fail[p];
		if(AA[i] == AA[p]) p++;
		fail[i + 1] = p;
	}
	for(int i=0; i<n; i++){
		SS.push_back(SS[i]);
	}
	p = 0;
	for(int i=0; i<SS.size(); i++){
		while(p && SS[i] != AA[p]) p = fail[p];
		if(SS[i] == AA[p]) p++;
		if(p == n){
			// SS[i - n + 1, i] == AA
			return i - n + 1;
		}
	}
	FUCK();
}

vector<pair<int, int> > solvepoly(set<int> A, set<int> S, int T, int K)
{
    set<int> mypoly;
    for(auto x: A)
        mypoly.insert(x);
    for(auto x: S)
    {
        x += K;
        if(mypoly.find(x) != mypoly.end()) mypoly.erase(x);
        else mypoly.insert(x);
    }
    bool mT = T<0;
    T = abs(T);
    vector<pair<int, int> > V;
    while(
        !mypoly.empty() &&
    *mypoly.rbegin() - *mypoly.begin() >= T)
    {
        int x = *mypoly.begin();
        mypoly.erase(x);
        if(!mT)
            V.emplace_back(1, x);
        else
            V.emplace_back(1, x+T);
        if(mypoly.find(x+T) != mypoly.end()) mypoly.erase(x+T);
        else mypoly.insert(x+T);
    }
    if(!mypoly.empty()) FUCK();
    return V;
}


int findK(set<int> A, set<int> S, int T)
{
    T = abs(T);
    vector<int> AA(T);
    vector<int> SS(T);
    for(auto x: A)
        AA[(x%T+T)%T]^=1;
    for(auto x: S)
        SS[(x%T+T)%T]^=1;
    return (T-rotate(AA, SS))%T;
}


pair<vector<pair<int, int> >, int>
solve(vector<pair<int, int> > A, vector<pair<int, int> > S, int T)
{
    set<int> sA, sS;
    for(auto x: A)
    {
        if(x.first%2==0) continue;
        if(sA.find(x.second) != sA.end()) sA.erase(x.second);
        else sA.insert(x.second);
    }
    for(auto x: S)
    {
        if(x.first%2==0) continue;
        if(sS.find(x.second) != sS.end()) sS.erase(x.second);
        else sS.insert(x.second);
    }
    if(T==0)
    {
        if(sA.size() != sS.size()) FUCK();
        int K = 0;
        if(sA.size() == 0 && sS.size() == 0)
            K = 0;
        else
            K = *sA.begin()-*sS.begin();
        return make_pair(solvepoly(sA, sS, T, K), K);
    }
    int K = findK(sA, sS, T);
    return make_pair(solvepoly(sA, sS, T, K), K);
}

const int MAXN = 200005;
char buf[MAXN];
int main(){
    scanf("%s",buf);
    int n;
    scanf("%d",&n);
    vector<pair<int, int>> A(n), S;
    for(auto &i : A){
    	i.first = 1;
    	scanf("%d",&i.second);
	}
	int pos = 0;
	map<int, int> mp;
	for(int i=0; buf[i]; i++){
		if(buf[i] == 'X') mp[pos]++;
		if(buf[i] == 'L') pos--;
		if(buf[i] == 'R') pos++;
	}
	for(auto &i : mp) S.push_back(pi(i.second, i.first));
	int T = pos;
	vector<pair<int, int>> ans;
	int K;
	tie(ans, K) = solve(A, S, T);
	sort(ans.begin(), ans.end(), [&](const pi &a, const pi &b){
		return a.second < b.second;
	});
	ans.push_back(pi(0, K));
	int curp = 0;
	string ret;
	for(int i=0; i<ans.size(); i++){
		while(curp > ans[i].second){
			curp--;
			ret.push_back('L');
		}
		while(curp < ans[i].second){
			curp++;
			ret.push_back('R');
		}
		for(int j=0; j<ans[i].first; j++) ret.push_back('X');
	}
	ret += "LR";
	puts(ret.c_str());
}
