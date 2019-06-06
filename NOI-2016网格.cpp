//bzoj-4651
#include <bits/stdc++.h>
typedef long long ll;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

int n, m, c;

struct Hash {
	static const int T = 14233333;
	struct Edge {ll fr; int v,nxt;} a[4001000];
	int head[T], st[T], _;
	inline void clear() {
		for(int i=1;i<=st[0];++i)
			head[st[i]] = 0;
		st[0] = _ = 0;
	}
	inline void ins(int x, int y, int i) {
		ll ky = (ll)x * m + y; x = ky % T;
		a[++_].fr = ky, a[_].v = i, a[_].nxt = head[x];
		if(!head[x]) st[++st[0]] = x;
		head[x] = _;
	}
	inline void ers(int x, int y) {
		ll ky = (ll)x * m + y; x = ky % T;
		int ls = 0;
		for(int i=head[x];i;i=a[i].nxt) {
			if(a[i].fr == ky) {
				if(ls) a[ls].nxt = a[i].nxt;
				else head[x] = a[i].nxt;
				return ;
			}
			ls = i;
		}
	}
	inline int f(int x,int y) {
		if(!x or !y or x == n + 1 or y == m + 1) return -1;
		ll ky = (ll)x * m + y; x = ky % T;
		for(int i=head[x];i;i=a[i].nxt)
			if(a[i].fr == ky)
				return a[i].v;
		return 0;
	}
}F,G;

const int _x[] = {-1,-1,-1,0,0,1,1,1};
const int _y[] = {-1,0,1,-1,1,-1,0,1};
const int N = 101000;
int X[N], Y[N];

inline int ant(int x,int y) {
	int up = F.f(x-1,y), dn = F.f(x+1,y);
	int le = F.f(x,y-1), re = F.f(x,y+1);
	int res = 0;
		if(up and re) ++res;
		if(up and le) ++res;
		if(dn and le) ++res;
		if(dn and re) ++res;
	return res;
}

inline int calc(int x,int y) {
	if((!x or x == n+1) and (!y or y == m+1)) return 0;
	
	if(!F.f(x, y)) return ant(x, y);
	int up = F.f(x-1,y); // ↑
	int dn = F.f(x+1,y); // ↓
	int le = F.f(x,y-1); // ←
	int re = F.f(x,y+1); // →
	int nw = F.f(x-1,y-1); // ↖
	int ne = F.f(x-1,y+1); // ↗
	int sw = F.f(x+1,y-1); // ↙
	int se = F.f(x+1,y+1); // ↘
	int res = 0;
		if(!ne and !up and !re) --res;
		if(!nw and !up and !le) --res;
		if(!sw and !dn and !le) --res;
		if(!se and !dn and !re) --res;
	return res;
}

int us[N];
int sk[N], vs[N], bor[N];

bool solve(int x, int y) {
	if(F.f(x, y)) return false;
	int res = 0;
	for(int d=0;d<8;++d)
		res += calc(x+_x[d], y+_y[d]);
	res += calc(x, y);
	F.ins(x, y, -1);
	for(int d=0;d<8;++d)
		res -= calc(x+_x[d], y+_y[d]);
	res -= calc(x, y);
	F.ers(x, y);
	
	sk[0] = 0;
	bool lne = false;
	if(x == 1 or y == 1 or x == n or y == m) lne = true;
	for(int d=0,t;d<8;++d) {
		t = vs[F.f(x+_x[d], y+_y[d])];
		if(t <= 0) continue;
		if(bor[t]) {lne = true; continue;}
		if(!us[t]) us[t] = 1, sk[++sk[0]] = t;
	}
	if(lne) res += sk[0] * 4;
	else res += (sk[0] - 1) * 4;
	for(int i=1;i<=sk[0];++i)
		us[sk[i]] = 0;
	
	return res;
}

int Tar, Now;

inline void dot(int x,int y) {
	if(!G.f(x, y)) Now += calc(x, y), G.ins(x, y, -1);
}

int work() {
	static int q[N], he, ta;
	for(int i=1;i<=c;++i) vs[i] = bor[i] = 0;
	if((ll)n * m - 1 <= c) return -1;
	
	Now = 0, Tar = 4;
	
	for(int i=1;i<=c;++i)
		if(!vs[i]) {
			vs[q[he = ta = 1] = i] = i, Tar -= 4;
			sk[0] = 0;
			int x, y, t; bool lne = false;
			while(he <= ta) {
				sk[++sk[0]] = q[he], x = X[q[he]], y = Y[q[he]], ++he;
				if(x == 1 or y == 1 or x == n or y == m) lne = true;
				for(int d=0;d<8;++d) {
					t = F.f(x+_x[d], y+_y[d]);
					if(t > 0) if(!vs[t]) vs[q[++ta] = t] = i;
				}
			}
			if(lne) {
				for(int i=1;i<=sk[0];++i)
					bor[sk[i]] = 1;
				Tar += 4;
			}
		}
	for(int i=1;i<=c;++i) {
		int x = X[i], y = Y[i];
		dot(x, y);
		for(int d=0;d<8;++d)
			dot(x+_x[d],y+_y[d]);
	}
	
	dot(1, 1), dot(n, 1);
	dot(1, m), dot(n, m);
	
	if(Now != Tar) return 0;
	if((ll)n * m - 2 <= c) return -1;
	
	if(n == 1 or m == 1) return 1;
	
	for(int i=1;i<=c;++i) {
		int x = X[i], y = Y[i];
		for(int d=0;d<8;++d)
			if(solve(x+_x[d], y+_y[d]))
				return 1;
	}
	
	return 2;
}

int main() {
	int T; read(T);
	while(T--) {
		read(n), read(m), read(c);
		F.clear(), G.clear();
		for(int i=1;i<=c;++i) {
			read(X[i]), read(Y[i]);
			F.ins(X[i], Y[i], i);
		}
		printf("%d\n",work());
	}
	return 0;
}
