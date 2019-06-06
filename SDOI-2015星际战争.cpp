#include <bits/stdc++.h>
using namespace std;

const int N=150,M=20100,inf=0x3f3f3f3f;
const double eps=1e-5;
struct Edge{int v,nxt;double w;}a[M];
int head[N],cur[N],dis[N],q[N],he,ta;
int atk[N],def[N],aim[N][N];
int n,m,_,s,t,TAR;

inline void add(int u,int v,double w){
	a[_].v=v,a[_].w=w,a[_].nxt=head[u],head[u]=_++;
	a[_].v=u,a[_].w=0,a[_].nxt=head[v],head[v]=_++;
}

bool bfs(){
	for(int i=t;i;--i)dis[i]=-1;
	dis[q[he=ta=1]=s]=0;
	while(he<=ta){
		int x=q[he++];
		for(int i=head[x];~i;i=a[i].nxt)
			if(a[i].w>eps&&dis[a[i].v]==-1){
				dis[a[i].v]=dis[x]+1;
				q[++ta]=a[i].v;
				if(a[i].v==t)return true;
			}
	}return dis[t]!=-1;
}

double dfs(int x,double flw){
	if(x==t||flw<eps)return flw;
	double res=0.0,tmp;
	for(int&i=cur[x];~i;i=a[i].nxt)
		if(dis[a[i].v]==dis[x]+1&&a[i].w>eps)
		if((tmp=dfs(a[i].v,min(flw-res,a[i].w)))>eps){
			a[i].w-=tmp;
			a[i^1].w+=tmp;
			res+=tmp;
			if(fabs(res-flw)<eps)return res;
		}
	if(res<eps)dis[x]=-1;
	return res;
}

bool check(double time){
	_=0;
	for(int i=t;i;--i)head[i]=-1;
	for(int i=1;i<=m;++i)
		add(s,i,time*atk[i]);
	for(int i=1;i<=n;++i)
		add(i+m,t,def[i]);
	for(int i=1;i<=m;++i)
	for(int j=1;j<=n;++j)
		if(aim[i][j])add(i,j+m,inf);
	double Ans=0.0;
	while(bfs()){
		for(int i=t;i;--i)cur[i]=head[i];
		Ans+=dfs(s,inf);
	}return Ans+eps>TAR;
}

int main(){
	scanf("%d%d",&n,&m);s=n+m+1,t=s+1;
	for(int i=1;i<=n;++i)scanf("%d",def+i),TAR+=def[i];
	for(int i=1;i<=m;++i)scanf("%d",atk+i);
	for(int i=1;i<=m;++i)
	for(int j=1;j<=n;++j)
		scanf("%d",&aim[i][j]);
	double L=0,R=0x3f3f3f3f,mid,res=R;
	while(L+eps<R){
		mid=0.5*(L+R);
		if(check(mid))R=res=mid;
		else L=mid;
	}
	printf("%lf\n",res);
	return 0;
}
