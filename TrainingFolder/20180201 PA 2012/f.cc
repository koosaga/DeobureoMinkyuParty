#include<bits/stdc++.h>
using namespace std;
char a[1010101];
char t[1010101];
int d, n;
stack<int> s;
stack<int> tt;
int divide(int a, int b)
{
    if(a>0 || a%b==0) return a/b;
    return a/b-1;
}
int mod(int a, int b)
{
    if(b==0) puts("FUCKINGSHIT");
    return (a%b+b)%b;
}

enum FROM{parent, altparent, ccw, child, cw};

void printAngle(pair<FROM, int> x)
{
    switch(x.first)
    {
        case parent: printf("parent"); break;
        case altparent: printf("altparent"); break;
        case ccw: printf("ccw"); break;
        case child: printf("child"); break;
        case cw: printf("cw"); break;
    }
    printf(",%d\n", x.second);
    return;
}

int main()
{
    scanf("%s%s", a, t);
    d = strlen(a); a[d] = '0'; a[d+1] = 0; //robust
    n = strlen(t);
    s.push(0);
    
    long long ans = 0;
    int difference = 0;
    pair<FROM, int> angle = make_pair(parent, 0);
    for(int i=0; i<n-1; ++i)
    {
        //printf("%d %d %d %d\n", i, s.size(), s.top()+difference, (a[s.size() - 1] - '0' - 1));
        //fflush(stdout);
        //printAngle(angle); //suicide angle;
        //printf("%d, <<%d>>\n",(int)s.size(), a[s.size()-1]-'0');

        bool altexists = s.size() != 1 &&
            mod(s.top()+difference, (a[s.size() - 1] - '0' - 1)) == 0;

        //printf("ALT%d\n", altexists);


        for(int _=0; _<t[i]-'0'; ++_)
        {
            switch(angle.first)
            {
                case parent:
                    if(altexists) angle = make_pair(altparent, 0);
                    else angle = make_pair(ccw, 0);
                    break;
                case altparent:
                    angle = make_pair(ccw, 0);
                    break;
                case ccw:
                    if(a[s.size()] != '0')
                        angle = make_pair(child, 0);
                    else
                        angle = make_pair(cw, 0);
                    break;
                case child:
                    angle = make_pair(child, angle.second+1);
                    if(angle.second == a[s.size()] - '0')
                        angle = make_pair(cw, 0);
                    break;
                case cw:
                    angle = make_pair(parent, 0);
                    break;
            }
            //printAngle(angle);
        }
        int dest, pdest;
        switch(angle.first)
        {
            case parent:
                dest = difference + s.top(); s.pop();
                //puts("HERE");
                pdest = divide(dest, a[s.size()] - '0' - 1);
                //printf("-%d %d-\n", dest, pdest);
                //printf("-%d %d-\n", difference, pdest);
                //puts("THERE");
                //printf("<<%d>>\n",a[s.size()]-'0');
                angle = make_pair(child, mod(dest, a[s.size()] - '0' - 1));
                ans += difference + pdest;
                if(!tt.empty()) difference = tt.top() + pdest; tt.pop();
                break;
            case altparent:
                dest = difference + s.top(); s.pop();
                pdest = divide(dest, a[s.size()] - '0' - 1) - 1;
                //printf("-%d %d-\n", dest, pdest);
                //printf("-%d %d-\n", difference, pdest);
                angle = make_pair(child, a[s.size()] - '0' - 1);
                ans += difference+ pdest;
                difference = pdest;
                break;
            case ccw:
                --difference;
                angle = make_pair(cw, 0);
                break;
            case cw:
                ++difference;
                angle = make_pair(ccw, 0);
                break;
            case child:
                tt.push(difference);
                s.push(angle.second);
                if(angle.second == a[s.size()-1]-'0' - 1)
                    angle = make_pair(altparent, 0);
                else
                    angle = make_pair(parent, 0);
                difference = 0;
                break;
        }
    }
    ans -= (n-2);
    ans /= 2;
    assert(ans%2==0);
    printf("%lld\n", ans);
}
















