//bzoj-2753
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N = 101000, M = 1001000;
struct Edge {int v,w,nxt;} a[M+M];
int head[N], vs[N], h[N];
int n,m,_;

struct edge {
	int l,r,w;
	friend inline bool operator < (const edge&A,const edge&B)
		{return h[A.r] != h[B.r] ? h[A.r] > h[B.r] : A.w < B.w;}
}e[M];

void snowy();void loves();void boshi();
int main(){boshi();loves();snowy();return 0;}

int d[N];
int find(int x) {return d[x] ? d[x] = find(d[x]) : x;}

void snowy() {
	int tot = 0;
	for(int x=1;x<=n;++x)
	for(int i=head[x];i;i=a[i].nxt){
		if(h[x] == h[a[i].v] and x > a[i].v) continue;
		if(!vs[x] or !vs[a[i].v]) continue;
		e[++tot] = (edge) {x, a[i].v, a[i].w};
	}
	sort(e+1,e+tot+1);
	ll ans = 0ll;
	for(int i=1,con=n-1,p1,p2;i<=tot and con;++i) {
		if((p1 = find(e[i].l)) == (p2 = find(e[i].r))) continue;
		d[p1] = p2, ans += e[i].w;
	}
	printf("%lld\n",ans);
}

int q[N], he, ta;

void loves() {
	vs[q[he = ta = 1] = 1] = 1;
	int x, cnt = 0;
	while(he <= ta) {
		x = q[he++];
		for(int i=head[x];i;i=a[i].nxt)
			if(!vs[a[i].v])
				vs[q[++ta] = a[i].v] = 1;
	}
	for(int i=1;i<=n;++i) if(vs[i]) ++cnt;
	printf("%d ",cnt);
}

void boshi() {
	read(n), read(m);
	for(int i=1;i<=n;++i) read(h[i]);
	for(int i=1,x,y,z;i<=m;++i) {
		read(x), read(y), read(z);
		if(h[x] < h[y]) swap(x, y);
		a[++_].v = y, a[_].w = z, a[_].nxt = head[x], head[x] = _;
		if(h[x] > h[y]) continue;
		swap(x, y);
		a[++_].v = y, a[_].w = z, a[_].nxt = head[x], head[x] = _;
	}
}
