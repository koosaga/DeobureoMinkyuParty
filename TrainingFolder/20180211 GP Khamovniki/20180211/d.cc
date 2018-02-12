#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 400005;
int B;

int arr[MAXN], n, b;
vector<int> byval[MAXN];
int buf_back[500 + 5];
int buf_value[500 + 5];
int c[MAXN], d[MAXN];

void insert(int c, int d, int idx){
	if(!n && !b){
		buf_back[0] = 0;
		buf_value[0] = idx;
		b++;
		return;
	}
	int clas = n;
	int ovps = 0;
	int LAST_IN_ARRAY = n+1;
	int last_valid = b;
	int last_valid_overpasses = 0;
	bool broken = 0;
	for(int i=b-1; i>=0; i--){
		if(ovps + clas - buf_back[i] > d){	
			LAST_IN_ARRAY = buf_back[i] + (ovps + clas - buf_back[i] - d) + 1;
			if(LAST_IN_ARRAY > 1 && arr[LAST_IN_ARRAY - 1] == c){
				LAST_IN_ARRAY--;
			}
			broken = 1;
			break;
		}
		ovps += clas - buf_back[i];
		clas = buf_back[i];
		if(::c[buf_value[i]] == c){
			last_valid = i;
			last_valid_overpasses = ovps;
		}
		ovps++;
		if(ovps > d){
			LAST_IN_ARRAY = buf_back[i] + 1;
			broken = 1;
			break;
		}
	}
	if(!broken){
		LAST_IN_ARRAY = ovps + clas - d + 1;
		LAST_IN_ARRAY = max(LAST_IN_ARRAY, 1);
		if(LAST_IN_ARRAY > 1 && arr[LAST_IN_ARRAY - 1] == c){
			LAST_IN_ARRAY--;
		}
	}
	auto l = lower_bound(byval[c].begin(), byval[c].end(), LAST_IN_ARRAY);
	int fucking_disgusting_problem = (l == byval[c].end() ? (n + 1) : *l);
	int last_array_overpasses = (n - fucking_disgusting_problem) + 1;
	for(int i=0; i<b; i++){
		if(buf_back[i] >= fucking_disgusting_problem) last_array_overpasses++;
	}
	if(last_array_overpasses > last_valid_overpasses){
		int nxtp = b;
		int fucking_waste_of_time = fucking_disgusting_problem;
		if(last_array_overpasses == d || ::c[arr[fucking_waste_of_time-1]] != c ){
			for(int i=b-1; i>=0; i--){
				if(buf_back[i] >= fucking_waste_of_time) nxtp = i;
			}
			for(int i=b; i>nxtp; i--){
				buf_value[i] = buf_value[i-1];
				buf_back[i] = buf_back[i-1];
			}
			b++;
			buf_value[nxtp] = idx;
			buf_back[nxtp] = fucking_waste_of_time;
		}
		else{
			for(int i=b-1; i>=0; i--){
				if(buf_back[i] >= fucking_waste_of_time) nxtp = i;
			}
			for(int i=b; i>nxtp; i--){
				buf_value[i] = buf_value[i-1];
				buf_back[i] = buf_back[i-1];
			}
			b++;
			buf_value[nxtp] = idx;
			buf_back[nxtp] = fucking_waste_of_time - 1;
		}
	}

	else{
		if(last_valid_overpasses == d) last_valid++;
		for(int i=b; i>last_valid; i--){
			buf_value[i] = buf_value[i-1];
			buf_back[i] = buf_back[i-1];
		}
		b++;
		buf_value[last_valid] = idx;
		buf_back[last_valid] = LAST_IN_ARRAY - 1;
	}
}

void build_structure(){
	for(int i=1; i<=400000; i++) byval[i].clear();
	for(int i=1; i<=n; i++) byval[c[arr[i]]].push_back(i);
}

int buf[MAXN];

void make_array(){
	int p = 0;
	int ptr = 0;
	while(ptr < b && buf_back[ptr] == 0){
		buf[++p] = buf_value[ptr];
		ptr++;
	}
	for(int i=1; i<=n; i++){
		buf[++p] = arr[i];
		while(ptr < b && buf_back[ptr] == i){
			buf[++p] = buf_value[ptr];
			ptr++;
		}
	}
	memcpy(arr, buf, sizeof(int) * (p + 1));
	n = p;
	b = 0;
}


int main(){
	cin >> B;
	int n;
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&c[i],&d[i]);
		if(i % B == 0){
			make_array();
			build_structure();
		}
		insert(c[i], d[i], i);
	}
	make_array();
	for(int i=1; i<=n; i++) printf("%d ", arr[i]);
}
