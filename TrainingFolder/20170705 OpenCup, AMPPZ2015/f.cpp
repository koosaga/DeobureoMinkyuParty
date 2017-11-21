#include <bits/stdc++.h>
using namespace std;

string s;
stack<char> stk;
char str[1000005];

bool match(char s, char t){
	if(s == '(' && t == ')') return true;
	if(s == '[' && t == ']') return true;
	if(s == '{' && t == '}') return true;
	return false;
}

bool closer(char c){
	if(c == '}' || c == ')' || c == ']') return true;
	return false;
}

int main(){
	scanf("%s", str);
	s = str;
	int should_append = count(s.begin(), s.end(), '{') - count(s.begin(), s.end(), '}');
	if(should_append < 0){
		puts("NIE");
		return 0;
	}
	for(int i=0; i<should_append; i++){
		s.push_back(')');
		s.push_back('}');
	}
	reverse(s.begin(), s.end());
	for(auto &i : s){
		if(closer(i)) stk.push(i);
		else{
			if(stk.empty() || !match(i, stk.top())){
				puts("NIE");
				return 0;
			}
			stk.pop();
		}
	}
	if(stk.size() != should_append){
		puts("NIE");
		return 0;
	}
	while(!stk.empty()){
		if(stk.top()!= ')'){
			puts("NIE");
			return 0;
		}
		s.push_back('(');
		stk.pop();
	}
	reverse(s.begin(), s.end());
	puts(s.c_str());
}
