#include<bits/stdc++.h>
using namespace std;
int N, s, dt;
struct Contest
{
    int ind;
    int D;
    int L;
    int H;
};
int contestback[1048576];
vector<Contest> con[1048576];

void solve()
{
    //skill, fatigue, last contest, my contest
    set<pair< pair<int, int>, pair<int, int> > > S;
    pair< pair<int, int>, pair<int, int> > zerofatigue = make_pair(make_pair(s, 0), make_pair(-1, -1));
    S.insert(zerofatigue);
    for(int d=0; d<1000050; ++d)
    {
        vector<pair<pair<int, int>, pair<int, int> > > V;
        for(auto x: S)
        {
            x.first.second /= 2;
            if(x.first.second == 0)
            {
                if(zerofatigue.first.first < x.first.first)
                    zerofatigue = x;
            } else V.push_back(x);
        }
        
        if(con[d].size()!=0)
        {
            sort(con[d].begin(), con[d].end(), [](const Contest& a, const Contest& b)
            {
                return a.L < b.L;
            });
            pair< pair<int, int>, pair<int, int> > minfatigue = make_pair(make_pair(-1, 0x7f7f7f7f), make_pair(-1, -2));
            auto it1 = S.rbegin();
            auto it2 = con[d].rbegin();
            auto Do1 = [&](set<pair< pair<int, int>, pair<int,int> > >::reverse_iterator it)
            {
                if(it->first.second < minfatigue.first.second)
                    minfatigue = *it;
            };
            auto Do2 = [&](vector<Contest>::reverse_iterator it)
            {
                if(minfatigue.second.second == -2) return;
                int fatigue = minfatigue.first.second;
                V.push_back(make_pair(make_pair(it->H - fatigue, fatigue + dt), make_pair(minfatigue.second.second, it->ind)));
                contestback[it->ind] = minfatigue.second.second;
                //printf(">%d %d<\n",it->ind, minfatigue.second.second);
            };
            while(it1!=S.rend() || it2 != con[d].rend())
            {
                
                if(it1==S.rend())
                    Do2(it2++); 
                else if(it2 == con[d].rend())
                    Do1(it1++); 
                else
                {
                    if(it1->first.first>=it2->L)
                        Do1(it1++);
                    else
                        Do2(it2++);
                }
            }
        }
        S.clear();
        for(auto x: V) S.insert(x);
        S.insert(zerofatigue); //simpler implementation
        /*{
            for(auto x: S)
            {
                cout << x.first.first << " " << x.first.second << " " <<
                        x.second.first << " " << x.second.second << endl;
            }
            cout << endl;
        }*/
    }
    printf("%d ", zerofatigue.first.first);
    int start = zerofatigue.second.second;
    vector<int> myV;
    while(start != -1)
    {
        myV.push_back(start);
        start = contestback[start];
    //    printf("%d\n", start);
    }
    reverse(myV.begin(), myV.end());
    printf("%d\n",(int)myV.size());
    for(auto x: myV) printf("%d ", x);
        puts("");
    return ;
    
}
int main()
{
    scanf("%d%d%d", &N, &s, &dt);
    for(int i=0; i<N; ++i)
    {
        int d, h, l; scanf("%d%d%d", &d, &l, &h);
        con[d].push_back({i+1, d, l, h});
    }
    solve();
}
