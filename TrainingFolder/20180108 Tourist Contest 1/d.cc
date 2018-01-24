#include<bits/stdc++.h>
using namespace std;

int n;
char arr[1000010];

// reverse order
int res1[1000010];
int tmp[1000010];

int Do(int *c){
	int ans = 0;
	for(int i=0; i<5; i++) ans += min(c[i], c[9-i]);
	return ans;
}

void update(int *cnt, vector<int> &v){
	int p = 9;
	while(v.size() < n){
		while(cnt[p] == 0) p--;
		int ans = p;
		cnt[p]--;
		while(cnt[p] == 0) p--;
		ans += p;
		cnt[p]--;
		v.push_back(ans);
	}
}

void update2(int *cnt, vector<int> &v){
	int p = 0;
	while(v.size() < n){
		while(cnt[p] == 0) p++;
		int ans = p;
		cnt[p]--;
		while(cnt[p] == 0) p++;
		ans += p;
		cnt[p]--;
		v.push_back(ans);
	}
}
string strize(vector<int> &v){
	string s;
	for(int i=(int)v.size()-1; i; i--){
		v[i-1] += v[i] / 10;
		v[i] %= 10;
	}
	for(int i=0; i<v.size(); i++)s.push_back(v[i] + '0');
	return s;
}

string solve1(){
	int cnt[10] = {};
	for(int i=0; i<2*n; i++) cnt[arr[i] - '0']++;
	int matc = Do(cnt);
	if(matc == n){
		vector<int> v(n, 0);
		v.back() = 1;
		return strize(v);
	}
	string ans = "";
	ans.push_back('0' - 1);
	for(int i=max(0, matc - 2); i<=matc; i++){
		vector<int> v;
		for(int j=8; j>=0; j--){
			bool jok = 0;
			for(int k=0; k<=j; k++){
				cnt[j-k]--;
				cnt[k]--;
				if(Do(cnt) >= i && cnt[j-k] >= 0 && cnt[k] >= 0){
					int ncnt[10] = {};
					memcpy(ncnt, cnt, sizeof(cnt));
					int k = i;
					for(int i=5; i<=9; i++){
						int mdf = min({ncnt[i], ncnt[9-i], k});
						ncnt[i] -= mdf;
						ncnt[9-i] -= mdf;
						k -= mdf;
					}
					vector<int> v(i, 9);
					v.push_back(j);
					update(ncnt, v);
					ans = max(ans, strize(v));
					jok = 1;
				}
				cnt[j-k]++;
				cnt[k]++;
			}
			if(jok) break;
		}
	}
	if(ans.size()!= n){
		ans.resize(n +10);
		return ans;
	}
	for(int i=0; i<ans.size(); i++){
		ans[i] = '0' + '9' - ans[i];
	}
	ans.back()++;
	for(int i=(int)ans.size()-1; i>0; i--){
		if(ans[i] > '9'){
			ans[i-1]++;
			ans[i] -= 10;
		}
	}
	if(ans.front() > '9'){
		ans.front() -= 10;
		ans = "1" + ans;
	}
	int frn = 0;
	while(frn < ans.size() && ans[frn] == '0') frn++;
	ans = ans.substr(frn, ans.size() - frn);
	if(ans.empty()) ans = "0";
	return ans;
}

string solve2(){
	int cnt[10] = {};
	for(int i=0; i<2*n; i++) cnt[arr[i] - '0']++;
	int matc = Do(cnt);
	if(matc == n){
		return string(n + 10, '0');
	}
	string ans = "";
	ans.push_back('9' + 1);
	for(int i=max(0, matc - 2); i<=matc; i++){
		vector<int> v;
		for(int j=10; j<=18; j++){
			bool jok = 0;
			for(int k=0; k<=j; k++){
				if(k >= 10 || j - k >= 10) continue;
				cnt[j-k]--;
				cnt[k]--;
				if(Do(cnt) >= i && cnt[j-k] >= 0 && cnt[k] >= 0){
					int ncnt[10] = {};
					memcpy(ncnt, cnt, sizeof(cnt));
					int k = i;
					for(int i=9; i>=5; i--){
						int mdf = min({ncnt[i], ncnt[9-i], k});
						ncnt[i] -= mdf;
						ncnt[9-i] -= mdf;
						k -= mdf;
					}
					vector<int> v(i, 9);
					v.push_back(j);
					update2(ncnt, v);
					ans = min(ans, strize(v));
					jok = 1;
				}
				cnt[j-k]++;
				cnt[k]++;
			}
			if(jok) break;
		}
	}
	if(ans.size()!= n) ans.resize(n +10);
	int frn = 0;
	while(frn < ans.size() && ans[frn] == '0') frn++;
	ans = ans.substr(frn, ans.size() - frn);
	if(ans.empty()) ans = "0";
	return ans;
}

bool cmp(string s, string t){
    if(s.size() != t.size()) return s.size() < t.size();
    return s < t;
}

void solve()
{
	memset(res1, 0, sizeof(res1));
    int l, i, j, k;
    scanf("%s", arr);
   
    int cnt[10];
    memset(cnt, 0, sizeof cnt);
    
    l = strlen(arr);
    n = l/2;
    
    for(i=0; i<l; i++)
        cnt[arr[i] - '0']++;
    
    
    for(i=1;i<=5;i++)
    {
        if(!cnt[i] || !cnt[10-i])
            continue;
            
        cnt[i]--;
        cnt[10-i]--;
        
        bool ok = 1;
        for(j=1;j<=4;j++)
        {
            if(cnt[j] != cnt[9-j])
            {
                ok = 0;
                break;
            }
        }
        if(ok)
        {
            if(cnt[0] < cnt[9] || (cnt[9] - cnt[0]) % 2 == 1)
                ok = 0;
        }
        
        if(ok)
        {
            printf("0\n");
            return;
        }
          
        cnt[i]++;
        cnt[10-i]++;
    }
    
    bool found = 0;
    for(i=10; i<=18; i++)
    {
        for(j=1; j<=9; j++)
        {
            if(i-j>=10 || !cnt[j] || !cnt[i-j])
                continue;
            
            cnt[j]--;
            cnt[i-j]--;
            
            memset(tmp, 0, sizeof tmp);
            
            int p = 9, pc = cnt[9];
            for(k=0; k<l-2; k++)
            {
                while(!pc)
                {
                    p--;
                    pc = cnt[p];
                }
                
                tmp[k/2] += p;
                pc--;
            }
            tmp[n-1] += i - 10;
            
            for(k=0; k<n; k++)
            {
                while(tmp[k] >= 10)
                {
                    tmp[k] -= 10;
                    tmp[k+1]++;
                }
            }
            
            cnt[j]++;
            cnt[i-j]++;
            
            if(!found)
            {
                found = 1;
                for(k=0; k<n; k++)
                    res1[k] = tmp[k];
            }
            else
            {
                bool cha = 0;
                for(k=n-1;k>=0;k--)
                {
                    if(tmp[k] < res1[k])
                    {
                        cha = 1;
                        break;
                    }
                    if(tmp[k] > res1[k])
                        break;
                }
                if(cha)
                {
                    for(k=0; k<n; k++)
                        res1[k] = tmp[k];
                }
            }
        }
        if(found)
            break;
    }
    string x = solve1();
    string y = solve2();
    string z;
    for(int i=0; i<n; i++) z.push_back(res1[i] + '0');
    if(found == 0) z.resize(n + 1);
    reverse(z.begin(), z.end());
    cout << min({x, y, z}, cmp) << endl;
}

int main()
{
	freopen("done.in", "r", stdin);
	freopen("done.out", "w", stdout);
    int t, i;
    scanf("%d", &t);
    for(i=0;i<t;i++)
        solve();
    return 0;
}
