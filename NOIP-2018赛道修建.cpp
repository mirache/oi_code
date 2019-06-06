#include <bits/stdc++.h>

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();return x;
}

const int N=50100;
struct Edge{int v,w,nxt;}a[N+N];
int head[N],f[N],b[N],d[N];
bool done[N];
int n,m,lim,sm,_;

int find(int x){return d[x]?d[x]=find(d[x]):x;}

void dfs(int x,int las){
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=las)dfs(a[i].v,x);
	int t=0;
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=las){
			b[++t]=f[a[i].v]+a[i].w;
			d[t]=done[t]=false;
		}
	std::sort(b+1,b+t+1);
	while(t&&b[t]>=lim)++sm,--t;
	int l=1,r=t;f[x]=d[t+1]=0;
	while(b[l]+b[t]<lim&&l<t)++l;
	if(l<t){
		for(int i=l;i<=t;++i){
			while(l<r&&b[r-1]+b[i]>=lim)--r;
			if(done[i])continue;
			int k=find(r);
				if(k>t)continue;
			if(k==i)k=find(k+1);
				if(k>t)continue;
			done[i]=done[k]=true;
			d[i]=i+1;d[k]=k+1;
			++sm;
		}
	}
	for(int i=t;i;--i)
		if(!done[i]){f[x]=b[i];return ;}
}

int main(){
	read(n),read(m);
	for(int i=1,x,y,z;i<n;++i){
		read(x),read(y),read(z);
		a[++_].v=y,a[_].w=z,a[_].nxt=head[x],head[x]=_;
		a[++_].v=x,a[_].w=z,a[_].nxt=head[y],head[y]=_;
	}
	int l=0,r=5e8,res=0;
	while(l<=r){
		lim=l+r>>1;sm=0;dfs(1,0);
		if(sm>=m)l=(res=lim)+1;
		else r=lim-1;
	}printf("%d\n",res);
	return 0;
}
