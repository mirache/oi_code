//51nod-1737
#include <bits/stdc++.h>
typedef long long ll;

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();return x;
}

const int N=101000;
struct Edge{int v,nxt,w;}a[N+N];
int head[N],sz[N],n,_;ll ans;

inline void ad(){
	static int u,v,w;read(u),read(v),read(w);
	a[++_].v=v,a[_].w=w,a[_].nxt=head[u],head[u]=_;
	a[++_].v=u,a[_].w=w,a[_].nxt=head[v],head[v]=_;
}

void dfs(int x,int las){
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=las){
			dfs(a[i].v,x);sz[x]+=sz[a[i].v];
			ans+=1ll*std::min(sz[a[i].v],n-sz[a[i].v])*a[i].w;
		}
}

int main(){
	read(n);sz[n]=1;
	for(int i=1;i<n;++i)ad(),sz[i]=1;
	dfs(1,0);printf("%lld\n",ans);
	return 0;
}
