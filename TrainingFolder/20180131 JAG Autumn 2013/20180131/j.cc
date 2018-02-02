#include<bits/stdc++.h>
using namespace std;

char inp[3][3100];

int arr[6100];
int qqq[6100];
int flip[26];
int can[6100];

mt19937 rng(0x9801);
int randint(int a, int b)
{
    return uniform_int_distribution<int>(a, b)(rng);
}

int main()
{
    int m, i, j;
    scanf("%d", &m);
    for(i=0;i<3;i++)
        scanf("%s", inp[i]);
    
    for(i=0;i<m;i++)
    {
        for(j=0;j<3;j++)
        {
            char t = inp[j][3*i + 1];
            if(islower(t))
            {
                arr[6*i + 2*j] = t - 'a' + 1;
                qqq[6*i + 2*j] = 0;
            }
            else
            {
                arr[6*i + 2*j] = t - 'A' + 1;
                qqq[6*i + 2*j] = 1;
            }
            
            t = inp[j][3*i + 2];
            if(islower(t))
            {
                arr[6*i + 2*j + 1] = t - 'a' + 1;
                qqq[6*i + 2*j + 1] = 0;
            }
            else
            {
                arr[6*i + 2*j + 1] = t - 'A' + 1;
                qqq[6*i + 2*j + 1] = 1;
            }
        }
    }
    
    for(i=0; i<m; i++)
        for(j=0; j<3; j++)
            if(arr[6*i + 2*j] != arr[6*i + 2*j + 1] || qqq[6*i + 2*j] == qqq[6*i + 2*j + 1])
                can[6*i + 2*j] = 1;
    
    int endtime = CLOCKS_PER_SEC * 2.9;
    while(clock() < endtime)
    {
        for(i=1; i<=26; i++)
            flip[i] = randint(0, 1);
        
        for(int b=0; b<500 && clock() < endtime; b++)
        {
            bool ok = 1;
            for(i=0; i<6*m; i+=6)
            {
                if((qqq[i] ^ flip[arr[i]]) & (qqq[i+1] ^ flip[arr[i+1]]))
                    continue;
                
                if((qqq[i+2] ^ flip[arr[i+2]]) & (qqq[i+3] ^ flip[arr[i+3]]))
                    continue;
                
                if((qqq[i+4] ^ flip[arr[i+4]]) & (qqq[i+5] ^ flip[arr[i+5]]))
                    continue;
                
                int t = randint(0, 2);
                switch(t)
                {
                case 0:
                    if(can[i])
                    {
                        if(!(qqq[i] ^ flip[arr[i]]))
                            flip[arr[i]] = !flip[arr[i]];
                        if(!(qqq[i+1] ^ flip[arr[i+1]]))
                            flip[arr[i+1]] = !flip[arr[i+1]];
                        break;
                    }
                    
                case 1:
                    if(can[i+2])
                    {
                        if(!(qqq[i+2] ^ flip[arr[i+2]]))
                            flip[arr[i+2]] = !flip[arr[i+2]];
                        if(!(qqq[i+3] ^ flip[arr[i+3]]))
                            flip[arr[i+3]] = !flip[arr[i+3]];
                        break;
                    }
                    
                case 2:
                    if(can[i+4])
                    {
                        if(!(qqq[i+4] ^ flip[arr[i+4]]))
                            flip[arr[i+4]] = !flip[arr[i+4]];
                        if(!(qqq[i+5] ^ flip[arr[i+5]]))
                            flip[arr[i+5]] = !flip[arr[i+5]];
                        break;
                    }
                    
                    if(can[i])
                    {
                        if(!(qqq[i] ^ flip[arr[i]]))
                            flip[arr[i]] = !flip[arr[i]];
                        if(!(qqq[i+1] ^ flip[arr[i+1]]))
                            flip[arr[i+1]] = !flip[arr[i+1]];
                        break;
                    }
                    
                    if(can[i+2])
                    {
                        if(!(qqq[i+2] ^ flip[arr[i+2]]))
                            flip[arr[i+2]] = !flip[arr[i+2]];
                        if(!(qqq[i+3] ^ flip[arr[i+3]]))
                            flip[arr[i+3]] = !flip[arr[i+3]];
                        break;
                    }
                }
                
                ok = 0;
                break;
            }
            
            if(ok)
            {
                int cnt = 0;
                for(i=1; i<=26; i++)
                    if(flip[i])
                        cnt++;
                
                printf("%d", cnt);
                for(i=1; i<=26; i++)
                    if(flip[i])
                        printf(" %c", 'A' + i - 1);
                printf("\n");
                
                return 0;
            }
        }
    }
    printf("-1\n");
    return 0;
}

