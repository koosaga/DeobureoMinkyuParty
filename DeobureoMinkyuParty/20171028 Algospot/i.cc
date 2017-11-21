#include <bits/stdc++.h>

using namespace std;

struct str
{
    long long a, b;
};

stack<str> stk;
map<string, long long> val;

bool isr = false;
string rrr;

char tmp[10010];

int main()
{
    char *p, *q;
    int n, m, k, t, i;
    long long a, b, x;
    scanf("%d", &n);
    for(i=0;i<n;i++)
    {
        scanf("%lld%*s%s", &x, tmp);
        val[tmp] = x;
    }
    scanf("%d", &m);
    for(i=0;i<m;i++)
    {
        scanf(" ");
        fgets(tmp, 10010, stdin);
        
        p = strtok(tmp, ". \n");
        q = strtok(NULL, ". \n");
        
        if(strcmp(p, "Take") == 0)
        {
            isr = true;
            rrr = q;
        }
        else if(strcmp(p, "Put") == 0)
        {
            if(isr && (rrr == q))
                stk.push({1, 0});
            else
                stk.push({0, val[q]});
        }
        else if(strcmp(p, "Add") == 0)
        {
            if(isr && (rrr == q))
                stk.top().a++;
            else
                stk.top().b += val[q];
        }
        else if(strcmp(p, "Remove") == 0)
        {
            if(isr && (rrr == q))
                stk.top().a--;
            else
                stk.top().b -= val[q];
        }
    }
    
    scanf("%s", tmp);
    
    k = strlen(tmp);
    
    if(k != stk.size())
    {
        printf("This %s is so undercooked!", rrr.c_str());
        return 0;
    }
    
    x = -1;
    for(i=0;i<k;i++)
    {
        a = stk.top().a;
        b = stk.top().b;
        stk.pop();
        
        t = tmp[i];
        
        if(a == 0)
        {
            if(b != t)
            {
                printf("This %s is so undercooked!", rrr.c_str());
                return 0;
            }
        }
        else
        {
            if((t-b)/a < 0 || (t-b)%a != 0)
            {
                printf("This %s is so undercooked!", rrr.c_str());
                return 0;
            }
            
            if(x == -1)
                x = (t-b)/a;
            else if(x != (t-b)/a)
            {
                printf("This %s is so undercooked!", rrr.c_str());
                return 0;
            }
        }
    }
    if(x == -1)
        x = 0;
    
    printf("%lld", x);
    return 0;
}












