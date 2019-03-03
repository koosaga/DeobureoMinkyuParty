#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;


struct point{
	double x, y, z;
	point(){}
	point(double x_, double y_, double z_ = 1.0){
		x = x_, y = y_, z = z_;
	}
	point operator -(const point &p)const{
		return {x-p.x,y-p.y};
	}
	point operator +(const point &p)const{
		return {x+p.x,y+p.y};
	}
	bool operator <(const point &p)const{
		return x!=p.x?x<p.x:y<p.y;
	}
	point To2D(){
		return {x/z,y/z};
	}
};

struct Ipoint{
	long long x, y;
	Ipoint operator -(const Ipoint &p)const{
		return {x-p.x,y-p.y};
	}
	Ipoint operator +(const Ipoint &p)const{
		return {x+p.x,y+p.y};
	}
	bool operator <(const Ipoint &p)const{
		return x!=p.x?x<p.x:y<p.y;
	}
	point ToP(){
		point t = point(x,y);
		return t;
	}
}w[310], P[1010];

point Cross(point a, point b){
	return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};
}
point Seg(point a, point b){
	return {b.y-a.y, a.x-b.x, -a.x*b.y+a.y*b.x};
}
int n, st[310];

double D1[310][310], D2[310][310];


int ccw(Ipoint a, Ipoint b, Ipoint c){
	long long t = (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
	return t<0?-1:t>0?1:0;
}
double Get(point a, point b){
	return a.x*b.y-a.y*b.x;
}
point Inter(point a, point b, point c, point d){
	point s1 = Seg(a,b), s2 = Seg(c,d);
	return Cross(s1,s2).To2D();
}
void Solve(){
	int i, top = 0, cnt = 0, j ,k;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%lld%lld",&w[i].x,&w[i].y);
	}
	if(n<=2){
		puts("none");
		return;
	}
	sort(w+1,w+n+1);
	top = 0;
	for(i=1;i<=n;i++){
		while(top>1 && ccw(w[st[top-1]], w[st[top]], w[i]) >=0)top--;
		st[++top] = i;
	}
	for(i=1;i<top;i++)P[cnt++] = w[st[i]];
	top = 0;
	for(i=1;i<=n;i++){
		while(top>1 && ccw(w[st[top-1]], w[st[top]], w[i]) <=0)top--;
		st[++top] = i;
	}
	for(i=top;i>1;i--)P[cnt++] = w[st[i]];
	for(i=0;i<cnt*2;i++)P[cnt+i]=P[i];
	Ipoint OO = {0,0};

	for(i=0;i<cnt;i++)for(j=0;j<cnt;j++)D1[i][j]=1e18, D2[i][j]=1e18;

	for(i=0;i<cnt;i++){
		//printf("%lld %lld\n",P[i].x,P[i].y);
	}


	for(i=0;i<cnt;i++){
		double s = 0.0;
		s += Get(P[i].ToP(),P[i+1].ToP());
		for(j=1;j<cnt;j++){
			s += Get(P[i+j].ToP(),P[i+j+1].ToP());

			Ipoint s1 = P[i+1]-P[i], s2 = P[i+j+1]-P[i+j];
			if(ccw(OO,s1,s2)!=-1)break;
			point p = Inter(P[i].ToP(),P[i+1].ToP(),P[i+j].ToP(),P[i+j+1].ToP());
			double tt = 0.0;
			tt += Get(P[i+j+1].ToP(),p);
			tt += Get(p,P[i].ToP());

			s += tt;

			D1[i][(i+j)%cnt] = fabs(s)*0.5;
			//printf("%d %d %f\n",i,(i+j)%cnt,fabs(s)*0.5);

			s -= tt;

		}
	}
	for(i=0;i<cnt;i++)for(j=0;j<cnt;j++)for(k=0;k<cnt;k++)D2[i][j]=min(D2[i][j],D1[i][k]+D1[k][j]);
	double res = 1e18;
	for(i=0;i<cnt;i++){
		for(j=0;j<cnt;j++){
			if(i==j)continue;
			res = min(res, D2[i][j]+D2[j][i]);
		}
	}
	//printf("%.10f\n",res);
	if(res > 5e15){
		puts("none");
		return;
	}
	double ss = 0.0;
	for(i=0;i<cnt;i++){
		ss += Get(P[i].ToP(), P[i+1].ToP());
	}
	ss = fabs(ss)*0.5;
	printf("%.10f\n",ss+res);
	
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		Solve();
	}
}
