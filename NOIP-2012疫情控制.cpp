#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')ob=1,c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const ll inf = 5e13;
const int N=50100;
struct Edge{int v,nxt;ll w;}a[N<<1];
ll ned[N],f[N],D[N],dis[N],mx;
int head[N],is[N],fa[N],n,m,_;

inline ll cmp(ll A,ll B){return A>B;}

inline void ad(){
	static int u,v;static ll w;read(u),read(v),read(w);
	a[++_].v=v,a[_].w=w,a[_].nxt=head[u],head[u]=_;
	a[++_].v=u,a[_].w=w,a[_].nxt=head[v],head[v]=_;
}

void pdf(int x,int las){
	f[x]=inf;fa[x]=las;
	for(int i=head[x];i;i=a[i].nxt)if(a[i].v^las)
		{dis[a[i].v]=dis[x]+a[i].w;pdf(a[i].v,x);}
}

int dfs(int x,ll lim){
	f[x]=inf;
	if(is[x])
		if(dis[x]>lim)f[x]=0ll;
		else {
			for(rg int i=is[x];i;--i)D[++D[0]]=dis[x];
			mx=max(mx,dis[x]);
		}
	int res(1);
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v^fa[x]){
			if(!dfs(a[i].v,lim))res=0;
			f[x]=min(f[x],f[a[i].v]+a[i].w);
		}
	if(f[x]<=lim&&f[x]+dis[x]>lim)return 1;
	return res?a[head[x]].nxt:0;
}

int solve(ll lim){
	int tp=0;D[0]=0;
	for(rg int i=is[1];i;--i)D[++D[0]]=0ll;
	for(rg int i=head[1],j;i;i=a[i].nxt,mx=0ll)
		if(!dfs(a[i].v,lim))
			if( mx and 0 <= lim-mx and lim-mx < a[i].w+a[i].w ){
				for(j=D[0];D[j]^mx;--j);
				for(;j^D[0];++j)D[j]=D[j+1];--D[0];
			}else ned[++tp]=a[i].w;
	sort(ned+1,ned+tp+1);sort(D+1,D+D[0]+1,cmp);
	for(rg int i=1,j=1;i<=tp;++i){
		while(lim-D[j]<ned[i]&&j<=D[0])++j;
		if(j>D[0])return 0;++j;
	}return 1;
}

void init();void work();
int main(){init();work();return 0;}

void work(){
	pdf(1,1);ll l=0,r=inf,mid,res=inf;
	while(l<=r)
		if(solve(mid=l+r>>1))r=(res=mid)-1;
		else l=mid+1;
	printf("%lld\n",res==inf?-1:res);
}

void init(){
	read(n);for(rg int i=1;i<n;++i)ad();
	read(m);for(rg int i=1,x;i<=m;++i)++is[read(x)];
}
