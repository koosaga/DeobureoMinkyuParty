#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

struct pnt{
	int x, y, idx;
};

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

lint ccw(pnt a, pnt b, pnt c){
	return ccw(pi(a.x, a.y), pi(b.x, b.y), pi(c.x, c.y));
}

lint dist(pnt a, pnt b){
	int dx = b.x - a.x;
	int dy = b.y - a.y;
	return 1ll * dx * dx + 1ll * dy * dy;
}

int n, m, printP[MAXN];

struct segment{
	int x, y;
	int previdx, nextidx;
	int pos;
};

vector<segment> leftSeg, rightSeg;
lint xpos, cost;

void easy_deliver(){
	cout << cost << endl;
	for(int i=1; i<=n; i++){
		printf("1 %d\n", printP[i]);
	}
	exit(0);
}

void FUCK_THIS(vector<pnt> &v){
	sort(v.begin(), v.end(), [&](const pnt &a, const pnt &b){
		return pi(a.x, a.y) < pi(b.x, b.y);
	});
	vector<pnt> w;
	for(auto &i : v){
		if(w.size() && pi(w.back().x, w.back().y) == pi(i.x, i.y)){
			continue;
		}
		w.push_back(i);
	}
	v = w;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		int k; scanf("%d",&k);
		vector<pnt> v;
		for(int j=1; j<=k; j++){
			int x, y;
			scanf("%d %d",&x,&y);
			v.push_back({x, y, j});
		}
		FUCK_THIS(v);
		sort(v.begin() + 1, v.end(), [&](const pnt &a, const pnt &b){
			auto x = ccw(v[0], a, b);
			if(x != 0) return x > 0;
			return dist(v[0], a) < dist(v[0], b);
		});
		vector<pnt> H;
		for(auto &x : v){
			while(H.size() >= 2 && ccw(H[H.size()-2], H.back(), x) <= 0){
				H.pop_back();
			}
			H.push_back(x);
		}
		vector<pi> segs;
		int miny = 1e9;
		for(int i=0; i<H.size(); i++){
			miny = min(miny, H[i].y);
			if(H[(i+1)%H.size()].x > H[i].x){
				segs.push_back({i, (i + 1)%H.size()});
			}
		}
		cost += miny;
		if(segs.empty()){
			xpos += H[0].x;
			printP[i] = H[0].idx;
		}
		else{
			bool found = 0;
			for(auto &j : segs){
				if(!found && H[j.first].y == miny){
					xpos += H[j.first].x;
					printP[i] = H[j.first].idx;
					found = 1;
				}
				if(!found){ // left
					swap(j.first, j.second);
					int dx = H[j.second].x - H[j.first].x;
					int dy = H[j.second].y - H[j.first].y;
					leftSeg.push_back({dx, dy, H[j.first].idx, H[j.second].idx, i});
				}
				else{ // right
					int dx = H[j.second].x - H[j.first].x;
					int dy = H[j.second].y - H[j.first].y;
					rightSeg.push_back({dx, dy, H[j.first].idx, H[j.second].idx, i});
				}
			}
			if(!found){
				swap(segs.back().first, segs.back().second);
				xpos += H[segs.back().second].x;
				printP[i] = H[segs.back().second].idx;
			}
		}
	}
	sort(leftSeg.begin(), leftSeg.end(), [&](const segment &a, const segment &b){
		return ccw(pi(0, 0), pi(a.x, a.y), pi(b.x, b.y)) < 0;
	});
	sort(rightSeg.begin(), rightSeg.end(), [&](const segment &a, const segment &b){
		return ccw(pi(0, 0), pi(a.x, a.y), pi(b.x, b.y)) > 0;
	});
	if(xpos <= m){
		easy_deliver();
	}
	else{
		for(auto &i : leftSeg){
			if(xpos + i.x >= m){
				xpos += i.x;
				cost += i.y;
				printP[i.pos] = i.nextidx;
				if(xpos == m) easy_deliver();
			}
			else{
				// hard deliver
				printP[i.pos] = -1;
				int cursgn = abs(xpos - m);
				int nxtsgn = abs(xpos + i.x - m);
				printf("%.20Lf\n", cost + (long double)i.y * cursgn / (cursgn + nxtsgn));
				int P = i.previdx, N = i.nextidx;
				for(int i=1; i<=n; i++){
					if(printP[i] != -1) printf("1 %d\n", printP[i]);
					else{
						printf("2 %d %d ", P, N);
						printf("%d %d\n", nxtsgn, cursgn + nxtsgn);
					}
				}
				exit(0);
			}
		}
	}
	assert(0);
	puts("WTF");
}
