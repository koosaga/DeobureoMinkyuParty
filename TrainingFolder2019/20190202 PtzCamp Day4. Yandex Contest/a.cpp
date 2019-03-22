#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300005;
using pi = pair<int, int>;

struct pnt{ 
	int x, y, idx;
};

int n;
pnt a[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&a[i].x,&a[i].y);
		a[i].x--;
		a[i].y--;
		a[i].idx = i;
	}
	auto xycmp = [](pnt a, pnt b){ return a.x + a.y > b.x + b.y; };
	auto xcmp = [](pnt a, pnt b){ return a.x > b.x; };
	auto ycmp = [](pnt a, pnt b){ return a.y > b.y; };

	priority_queue<pnt, vector<pnt>, decltype(xycmp)> pqxy(xycmp);
	priority_queue<pnt, vector<pnt>, decltype(xcmp)> pqx(xcmp);
	priority_queue<pnt, vector<pnt>, decltype(ycmp)> pqy(ycmp);
	for(int i=1; i<=n; i++){
		pqxy.push(a[i]);
	}
	int curx = 0, cury = 0;
	vector<int> p;
	while(p.size() < n){
		while(!pqxy.empty() && (pqxy.top().x <= curx || pqxy.top().y <= cury)){
			if(pqxy.top().x <= curx) pqy.push(pqxy.top());
			else if(pqxy.top().y <= cury) pqx.push(pqxy.top());
			pqxy.pop();
		}
		if(!pqx.empty() && pqx.top().x <= curx){
			p.push_back(pqx.top().idx);
			pqx.pop();
			continue;
		}
		if(!pqy.empty() && pqy.top().y <= cury){
			p.push_back(pqy.top().idx);
			pqy.pop();
			continue;
		}
		int xymin = 2e9;
		int xmin = 2e9;
		int ymin = 2e9;
		if(!pqxy.empty()) xymin = pqxy.top().x + pqxy.top().y - curx - cury;
		if(!pqx.empty()) xmin = pqx.top().x - curx;
		if(!pqy.empty()) ymin = pqy.top().y - cury;
		if(xymin == min({xmin, ymin, xymin})){
			curx = max(curx, pqxy.top().x);
			cury = max(cury, pqxy.top().y);
			p.push_back(pqxy.top().idx);
			pqxy.pop();
		}
		else if(xmin == min({xmin, ymin, xymin})){
			curx = max(curx, pqx.top().x);
			cury = max(cury, pqx.top().y);
			p.push_back(pqx.top().idx);
			pqx.pop();
		}
		else if(ymin == min({xmin, ymin, xymin})){
			curx = max(curx, pqy.top().x);
			cury = max(cury, pqy.top().y);
			p.push_back(pqy.top().idx);
			pqy.pop();
		}
		else assert(0);
	}
	for(int i=0; i<p.size(); i++) printf("%d ", p[i]);
}
