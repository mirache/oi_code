#include<bits/stdc++.h>
using namespace std;
#define rg register

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')ob=1,c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=501000;
struct Edge{int v,nxt;}a[N<<1];
int head[N],f[N],g[N],stk[N];
int n,_;

template <typename _Tp> inline _Tp tmax(const _Tp A,const _Tp B){return A>B?A:B;}

inline void add(int u,int v){a[++_].v=v,a[_].nxt=head[u],head[u]=_;return ;}

inline int cmp(const int&A,const int&B){return f[A]-g[A]>f[B]-g[B];}

inline void dfs(int x,int fa){
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=fa)
			dfs(a[i].v,x);
	int top=0;
	for(rg int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=fa){
			g[a[i].v]+=2;
			f[a[i].v]=tmax(g[a[i].v],f[a[i].v]+1);
			stk[++top]=a[i].v;
		}
	sort(stk+1,stk+top+1,cmp);
	for(rg int i=1;i<=top;++i){
		f[x]=tmax(f[x],g[x]+f[stk[i]]);
		g[x]+=g[stk[i]];
	}return ;
}

int main(){
	read(n);
	for(rg int i=1;i<=n;++i)read(f[i]);int vas=f[1];
	for(rg int i=1,x,y;i<n;++i)read(x),read(y),add(x,y),add(y,x);
	dfs(1,0);printf("%d\n",tmax(f[1],g[1]+vas));return 0;
}
