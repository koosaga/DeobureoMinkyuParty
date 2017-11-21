#include<bits/stdc++.h>

using namespace std;

char arr[1000010];
char stk[1000010];
int s;

char pri[1000010];
int p;

char o2c(char x)
{
    if(x == '(')
        return ')';
    if(x == '{')
        return '}';
    return ']';
}

char c2o(char x)
{
    if(x == ')')
        return '(';
    if(x == '}')
        return '{';
    return '[';
}

int main()
{
    char x;
    int i;
    scanf("%s", arr);
    for(i=0;arr[i];i++)
    {
        x = arr[i];
        if(x == '(' || x == '{' || x == '[')
        {
            stk[s++] = x;
        }
        else
        {
            if(s == 0)
                pri[p++] = c2o(x);
            else
            {
                if(o2c(stk[--s]) != x)
                {
                    printf("NIE");
                    return 0;
                }
            }
        }
    }
    
    for(i=p-1;i>=0;i--)
        printf("%c", pri[i]);
    printf("%s", arr);
    for(i=s-1;i>=0;i--)
        printf("%c", o2c(stk[i]));
    return 0;
}




