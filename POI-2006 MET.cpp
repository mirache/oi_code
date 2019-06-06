#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register
#define cl(x) memset(x,0,sizeof(x))
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define abs(x) ((x)>0?(x):(-(x)))

template <typename _Tp> inline _Tp read(_Tp&x){
	rg char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')c11=getchar(),ob=1;
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=1005000;
struct Edge{int v,nxt;}a[N<<1];
int head[N],tot[N],deg[N],lay[N],vis[N];
int n,k,_(0);

inline void add(int u,int v){
	a[++_].v=v,a[_].nxt=head[u],head[u]=_;++deg[u];
	a[++_].v=u,a[_].nxt=head[v],head[v]=_;++deg[v];
}

void topology(){
	queue <int> q;
	for(rg int i=1;i<=n;++i)if(deg[i]==1)vis[i]=1,++tot[lay[i]=1],q.push(i);
	while(!q.empty()){
		rg int x=q.front();q.pop();
		for(rg int i=head[x];i;i=a[i].nxt)
			if(!vis[a[i].v])
			if((--deg[a[i].v])==1)
			vis[a[i].v]=1,++tot[lay[a[i].v]=lay[x]+1],q.push(a[i].v);
	}
	return ;
}

int main(){
	read(n);read(k);
	for(rg int i=1,x,y;i<n;++i)add(read(x),read(y));
	topology();
	rg int ans(0);
	for(rg int i=1;tot[i];++i)ans+=min(k<<1,tot[i]);
	printf("%d\n",ans);
	return 0;
}
