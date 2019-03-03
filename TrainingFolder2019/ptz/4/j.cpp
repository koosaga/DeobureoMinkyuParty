#include <bits/stdc++.h>
using namespace std;

int qcnt = 0;
int query(char c){
	qcnt++;
	cout << c << endl;
	int x; cin >> x; return x;
}

void conj(string s){
	query('+');
	if(query('-')){
		cout << "! ugly" << endl;
		exit(0);
	}
	else{
		cout << "! " + s << endl;
		exit(0);
	}
}

int main(){

	int t1 = 7;
	int t2 = 56;
	int t3 = 388;
	int t4 = 1000;

	for(int j=0; j< t1 ; j++){
		int c = query('-');
		if(c == 1) conj("good");
	}
	for(int j=0; j< 3*t1 ; j++){
		int c = query('+');
		if(c == 1) conj("bad");
	}
	for(int j=0; j< t2-t1 ; j++){
		int c = query('+');
		if(c == 1) conj("bad");
	}
	for(int j=0; j< 3*t1 + 3*t2 ; j++){
		int c = query('-');
		if(c == 1) conj("good");
	}
	for(int j=0; j< t3 - t2 ; j++){
		int c = query('-');
		if(c == 1) conj("good");
	}
	for(int j=0; j< 6*t1 + 3*t2 + 3*t3 ; j++){
		int c = query('+');
		if(c == 1) conj("bad");
	}
	for(int j=0; j< t4-t3 ; j++){
		int c = query('+');
		if(c == 1) conj("bad");
	}
	for(int j=0; j< 12*t1 + 6*t2 + 3*t3 + 3*t4 ; j++){
		int c = query('-');
		if(c == 1) conj("good");
	}

	cout << "! ugly" << endl;
	return 0;
}
