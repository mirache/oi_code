//bzoj-4331
#include <bits/stdc++.h>
using namespace std;

template <typename _tp> inline void read(_tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11!='-'&&!isdigit(c11))c11=getchar();if(c11=='-')ob=1,c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;
}

inline void cmax(int&A,const int&B) {if(A < B) A = B;}
inline void cmin(int&A,const int&B) {if(A > B) A = B;}

const int N = 501000, M = 2001000;
struct Edge{int v,nxt;}a[M];
int head[N],id[N];
int n,m,_;

inline void add(int x,int y){a[++_].v=y,a[_].nxt=head[x],head[x]=_;}

struct EDGE{
	int l,r,w;
	friend inline bool operator < (const EDGE&A,const EDGE&B) {return A.w<B.w;}
}e[M];

namespace Bridge{
	int dfn[N],low[N],vs[N],bri[M],dfc;
	
	void Find_Con(int x,int las){
		dfn[x] = low[x] = ++dfc;
		for(int i=head[x];i;i=a[i].nxt)
			if(!dfn[a[i].v]){
				Find_Con(a[i].v,x);
				cmin(low[x], low[a[i].v]);
				if(low[x] < low[a[i].v]) bri[i] = bri[i^1] = true;
			}else if(a[i].v!=las) cmin(low[x], dfn[a[i].v]);
	}

	void Get_Con(int x,int Id){
		id[x] = Id, vs[x] = 1;
		for(int i=head[x];i;i=a[i].nxt)
			if(!vs[a[i].v] and !bri[i])
				Get_Con(a[i].v,Id);
	}

	void work(){
		for(int i=1;i<=n;++i)
			if(!dfn[i]) Find_Con(i,i);
		
		int nn = 0;
		for(int i=1;i<=n;++i)
			if(!vs[i]) Get_Con(i,++nn);
		n = nn;
	}
}

namespace Tree{
	int sz[N],son[N],top[N],fa[N],dfn[N],dep[N],dfc;
	
	void dfs1(int x){
		sz[x] = 1;
		for(int i=head[x];i;i=a[i].nxt)
			if(a[i].v != fa[x]){
				fa[a[i].v] = x;
				dep[a[i].v] = dep[x] + 1;
				dfs1(a[i].v);
				sz[x] += sz[a[i].v];
				if(sz[a[i].v] > sz[son[x]])
					son[x] = a[i].v;
			}
	}
	
	void dfs2(int x,int Top){
		top[x] = Top, dfn[x] = ++dfc;
		if(son[x]) dfs2(son[x], Top);
		for(int i=head[x];i;i=a[i].nxt)
			if(a[i].v != fa[x] and a[i].v != son[x])
				dfs2(a[i].v, a[i].v);
	}
	
	bool clamp(int x,int y,int z){
		y = dfn[y];
		while(top[x] != top[z]){
			if(dep[top[x]] < dep[top[z]]) swap(x,z);
			if(dfn[top[x]] <= y and y <= dfn[x]) return true;
			x = fa[top[x]];
		}
		if(dep[x] > dep[z]) swap(x,z);
		if(dfn[x] <= y and y <= dfn[z]) return true;
		return false;
	}
	
	void init(){dfs1(1),dfs2(1,1);}
}

void input(){
	read(n), read(m), _ = 1;
	for(int i=1,x,y,z;i<=m;++i) {
		read(x), e[i].l = x;
		read(y), e[i].r = y;
		add(x,y), add(y,x);
		read(z), e[i].w = z;
	}
}

void ReBuild(){
	int nn = 0; _ = 0;
	for(int i=1;i<=n;++i) head[i] = 0;
	
	for(int i=1;i<=m;++i)
		if(id[e[i].l] != id[e[i].r]){
			e[i].l = id[e[i].l];
			e[i].r = id[e[i].r];
			e[++nn] = e[i];
			add(e[i].l,e[i].r);
			add(e[i].r,e[i].l);
		}
	m = nn;
}

bool ins(int&x,int&y,int z){
	if(Tree::clamp(x,z,y)) return true;
	if(Tree::clamp(x,y,z)) {y = z; return true;}
	if(Tree::clamp(y,x,z)) {x = z; return true;}
	return false;
}

int Work(){
	sort(e+1,e+m+1);
	Tree::init();
	int x = e[1].l, y = e[1].r;
	for(int i=2;i<=m;++i){
		if(!ins(x,y,e[i].l)) return e[i].w;
		if(!ins(x,y,e[i].r)) return e[i].w;
	}
	return -1;
}

int main(){
	input();
	Bridge::work();
	ReBuild();
	printf("%d\n",Work());
	return 0;
}
