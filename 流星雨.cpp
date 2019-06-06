//yzoj-10030
#include <bits/stdc++.h>
using namespace std;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N=101000;
struct Edge{int v,w,nxt;}a[N<<2];
int head[N],Head[N],d[N],dep[N],fa[N];
bool done[N],vs[N];int n,m,_;

inline int find(int x){return d[x]?d[x]=find(d[x]):x;}

struct node{
	int id,lca;
	friend inline bool operator < (const node&A,const node&B) {return dep[A.lca]>dep[B.lca];}
}o[N];

void tarjan(int x){
	vs[x]=1;
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=fa[x]){
			dep[a[i].v]=dep[x]+1;
			fa[a[i].v]=x;
			tarjan(a[i].v);
			d[a[i].v]=x;
		}
	for(int i=Head[x];i;i=a[i].nxt)
		if(vs[a[i].v])
			o[a[i].w].lca=find(a[i].v);
}

void dfs(int x){
	if(vs[x])return ;
	vs[x]=1;
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=fa[x])
			dfs(a[i].v);
	for(int i=Head[x];i;i=a[i].nxt)
		done[a[i].w]=1;
}

void init();void work();
int main(){init();work();return 0;}

void work(){
	tarjan(1);
	memset(vs,0,sizeof vs);
	sort(o+1,o+m+1);
	int ans=0;
	for(int i=1;i<=m;++i)
		if(!done[o[i].id]){
			++ans;
			dfs(o[i].lca);
		}
	printf("%d\n",ans);
}

void init(){
	read(n),read(m);int x,y;
	for(int i=1;i<n;++i){
		read(x),read(y);
		a[++_].v=y,a[_].nxt=head[x],head[x]=_;
		a[++_].v=x,a[_].nxt=head[y],head[y]=_;
	}
	for(int i=1;i<=m;++i){
		read(x),read(y);o[i].id=i;
		a[++_].v=y,a[_].w=i,a[_].nxt=Head[x],Head[x]=_;
		a[++_].v=x,a[_].w=i,a[_].nxt=Head[y],Head[y]=_;
	}
}
