//bzoj-3716/4251
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename _tp> inline void read(_tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11!='-'&&!isdigit(c11))c11=getchar();if(c11=='-')ob=1,c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;
}

const int N = 201000;
int n,m; ll ans;

struct opt{
	ll x,y,v;
	friend inline bool operator < (const opt&A,const opt&B)
		{return A.x != B.x ? A.x < B.x : A.y > B.y;}
}sth[N], grd[N];

struct node{
	ll x,y,v;
	friend inline bool operator < (const node&A,const node&B)
		{return A.y != B.y ? A.y < B.y : A.x < B.x;}
};

set <node> c;
set <node>::iterator itr;

void input(); void work();

int main(){
	input();
	work();
	return 0;
}

void work(){
	node nw, t; ll mi;
	for(int i=n,j=m;i or j;)
		if(sth[i].x >= grd[j].x){
			nw = (node) {sth[i].x, sth[i].y, sth[i].v};
			c.insert(nw); --i;
		}else {
			nw = (node) {2e9, grd[j].y, grd[j].v};
			while(grd[j].v and !c.empty()) {
				itr = c.upper_bound(nw);
				if(itr == c.begin()) break;
				--itr, t = *itr; c.erase(itr);
				mi = min(grd[j].v, t.v);
				grd[j].v -= mi, t.v -= mi, ans -= mi;
				if(t.v) c.insert(t);
			} --j;
		}
	printf("%lld\n",ans);
}

void input(){
	read(n), read(m);
	ll W,H,x,y,z;
	read(W), read(H);
	for(int i=1;i<=n;++i) {
		read(x), x *= H, read(y), y *= W, read(z);
		sth[i] = (opt) {x - y, x + y, z}, ans += z;
	}
	for(int i=1;i<=m;++i) {
		read(x), x *= H, read(y), y *= W, read(z);
		grd[i] = (opt) {x - y, x + y, z};
	}
	sort(sth+1,sth+n+1), sth[0].x = -6e18;
	sort(grd+1,grd+m+1), grd[0].x = -6e18;
}
