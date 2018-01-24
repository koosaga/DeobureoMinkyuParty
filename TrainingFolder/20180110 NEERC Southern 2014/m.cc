#include<bits/stdc++.h>
using namespace std;
stack<pair<int, int> > place[26];
stack<int> size[26];
char buf[5050];
int N;
int main()
{
    fgets(buf, 5050, stdin);
    sscanf(buf, "%d", &N);
    for(int j=0; j<N; ++j)
    {
        fgets(buf, 5050, stdin);
        for(int i=0; buf[i]; ++i)
        {
            if(buf[i]=='{')
            {
                for(int i=0; i<26; ++i)
                    size[i].push(place[i].size());
            }
            else if(buf[i] == '}')
            {
                for(int i=0; i<26; ++i)
                {
                    while(place[i].size()!=size[i].top())
                        place[i].pop();
                    size[i].pop();
                }
            }
            else if('a'<=buf[i] && buf[i] <= 'z')
            {
                if(place[buf[i]-'a'].size() != 0)
                {
                    printf("%d:%d: warning: shadowed declaration of %c, the shadowed position is %d:%d\n", j+1, i+1, buf[i], place[buf[i]-'a'].top().first, place[buf[i]-'a'].top().second);

                }
                place[buf[i]-'a'].emplace(j+1, i+1);
            }
        }
    }
    return 0;   
}
