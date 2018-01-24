#include<bits/stdc++.h>
using namespace std;
const int ALPHACOUNT = 26;
const char ALPHASTART = 'a';

void* bp = nullptr;

int tp = 1;
int mymalloc();

struct Node
{
    int dp;
    int value[ALPHACOUNT];   
    void InsertString(char* x)
    {
        if(x[0] == '\0') return;
        int nextIndex = x[0]-ALPHASTART;
        if(!value[nextIndex])
            value[nextIndex] = mymalloc();
        else
            dp ^= 1 + (((Node*)bp) + value[nextIndex])->dp;
        (((Node*)bp) + value[nextIndex])->InsertString(x+1);
        dp ^= 1+(((Node*)bp) + value[nextIndex])->dp;
    }
};

Node fuckmemory[100000*41];

int mymalloc()
{
    fuckmemory[tp].dp = 0;
    fill(fuckmemory[tp].value, fuckmemory[tp].value + ALPHACOUNT, 0);
    return tp++;
}




void tmain()
{
    bp = fuckmemory; tp = 0;
    int N;
    char inp[256];
    Node* trie = ((Node*)bp) + mymalloc(); 
    
    scanf(" %d", &N);
    for(int i=0; i<N; ++i)
    {
        scanf(" %s", inp);
        trie->InsertString(inp);
    }
    
    int Q;
    scanf(" %d", &Q);
    for(int i=0; i<Q; ++i)
    {
        scanf(" %s", inp);
        trie->InsertString(inp);
        if(trie->dp == 0) puts("2");
        else puts("1");
    }
    return;
    
}


int T;
int main()
{
    scanf("%d", &T);
    for(int i=1; i<=T; ++i)
    {
        printf("Case %d:\n", i);
        tmain();
    }
}













