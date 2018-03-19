#include<bits/stdc++.h>
using namespace std;

char buf1[252525];
char buf2[252525];
    
string gen(int d)
{
    if(d==30) return "";
    stringstream s; s << d; 
    string g; s >> g;
    
    char generationhead[] = "if s%d #next == e%d { res%d = s%d }\n"
    "else\n"
    "{\n"
    "    bool%d = nil\n"
    "    loop {\n"
    "    if bool%d == nil {\n"
    "        s%u = m%d\n"
    "        e%u = e%d\n"
    "        ps%u = m%dp\n"
    "    }\n"
    "    else\n"
    "    {\n"
    "        s%u = s%d\n"
    "        e%u = m%d\n"
    "        ps%u = ps%d\n"
    "    }\n"
    "    m%u = s%u\n"
    "    t%u = s%u\n"
    "    \n"
    "    loop {\n"
    "        if t%u == nil { break } else { t%u = t%u #next }\n"
    "        m%up = m%u\n"
    "        m%u = m%u #next\n"
    "        if t%u == nil { break } else { t%u = t%u #next }\n"
    "    }\n";
    string Innerloop = gen(d+1);
    char generationtail[] = 
    "if ps%u == nil { } else { ps%u #next = res%u }\n"
    "if bool%d == nil { bool%d = head } else { break }\n"
    "}\n"
    "\n"
    "tmp%d = m%d\n"
    "if m%d #value < s%d #value {\n"
    "    res%d = m%d\n"
    "    m%d = m%d #next\n"
    "}\n"
    "else {\n"
    "    res%d = s%d\n"
    "    s%d = s%d #next\n"
    "}\n"
    "cur%d = res%d\n"
    "loop {\n"
    "    if s%d == tmp%d {\n"
    "        if m%d == e%d { break } else\n"
    "        {     \n"
    "            cur%d #next = m%d\n"
    "            m%d = m%d #next\n"
    "        }\n"
    "    }\n"
    "    else\n"
    "    {\n"
    "        if m%d == e%d\n"
    "        {\n"
    "            cur%d #next = s%d\n"
    "            s%d = s%d #next\n"
    "        }\n"
    "        else\n"
    "        {\n"
    "            if m%d #value < s%d #value\n"
    "            {\n"
    "                cur%d #next = m%d\n"
    "                m%d = m%d #next\n"
    "            }\n"
    "            else\n"
    "            {\n"
    "                cur%d #next = s%d\n"
    "                s%d = s%d #next\n"
    "            }\n"
    "        }\n"
    "    }\n"
    "}\n"
    "cur%d #next = e%d\n"
    "}\n";
    sprintf(buf1, generationhead, d, d, d, d, d, d, d+1, d, d+1, d, d+1, d, d+1, d, d+1, d, d+1, d, d+1, d+1, d+1, d+1, d+1, d+1, d+1, d+1, d+1, d+1, d+1, d+1, d+1, d+1);
    sprintf(buf2, generationtail, d+1, d+1, d+1, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d ,d ,d ,d ,d ,d ,d ,d ,d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d ,d ,d ,d ,d ,d ,d ,d ,d, d, d);
    return string(buf1)+Innerloop + string(buf2);
}

string realprogram()
{
    string program = "s1 = head e1 = nil m1 = s1 t1 = s1 ps1 = nil\n"
    "loop {\n"
    "if t1 == nil { break } else { t1 = t1 #next }\n"
    "m1p = m1\n"
    "m1 = m1 #next\n"
    "if t1 == nil { break } else { t1 = t1 #next }\n"
    "}\n";
    
    return program + gen(1);
    
}

int main()
{
    //string meowpp; cin >> meowpp;
    //assert(meowpp=="Meow++");
    string program = "if head == nil { } else {\n" + realprogram() + " head = res1 \n }\n";
    cout << program << endl;
}
