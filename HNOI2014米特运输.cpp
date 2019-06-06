#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define rg register
#define cl(x) memset(x,0,sizeof(x))
#define cl1(x) memset(x,-1,sizeof(x))
#define eps (1e-10)

template <typename _Tp> inline _Tp read(_Tp&x){
	rg char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')c11=getchar(),ob=1;
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=500500;
struct Edge{int v,nxt;}a[N<<1];
int head[N],tot[N],n,_(0);
double f[N],g[N],d[N];

inline void add(int u,int v){a[++_].v=v,a[_].nxt=head[u],head[u]=_;}

inline void dfs(int x,int fa){
	for(rg int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=fa)
			f[a[i].v]=f[x]+log(tot[x]),
			dfs(a[i].v,x);
	return ;
}

int main(){
	read(n);
	for(rg int i=1;i<=n;++i)read(d[i]);
	cl1(tot);tot[1]=0;
	for(rg int i=1,x,y;i<n;++i)
		read(x),read(y),add(x,y),add(y,x),++tot[x],++tot[y];
	f[1]=log(1);
	dfs(1,0);
	for(rg int i=1;i<=n;++i)
		g[i]=f[i]+log(d[i]);
	sort(g+1,g+n+1);
	int cnt(1),ans(0);
	for(rg int i=2;i<=n;++i)
		if(g[i]-g[i-1]<eps)++cnt;
		else ans=max(ans,cnt),cnt=1;
	ans=max(ans,cnt);
	printf("%d\n",n-ans);
	return 0;
}
