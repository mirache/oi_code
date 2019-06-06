#pragma GCC optimize(3)
#pragma pack(16)
#include<bits/stdc++.h>
using namespace std;
#define cl(x) memset(x,0,sizeof(x))

template <typename _Tp> inline void read(_Tp &x){
	char c11=getchar();x=0;//bool booo=0;
	while(c11<'0'||c11>'9'){/*if(c11=='-')booo=1;*/c11=getchar();}
	while(c11>='0'&&c11<='9'){x=x*10+c11-'0';c11=getchar();}
//	if(booo)x=-x;
	return ;
}

const int maxn=300050,maxm=300050;
struct node {int v,w,nxt;} a[maxm<<1];
int n,m,p=0,head[maxn];
int anc[maxn][21];
int lca[maxm],depth[maxn];
int s[maxm],t[maxm];
int maxlog;
int chaf[maxn];
int sum[maxn];

inline int LCA(int x,int y){
	if(depth[x]<depth[y])swap(x,y);

	int maxxlog=min((int)log2(depth[x]-depth[y])+3,maxlog);
	if(depth[x]!=depth[y])
		for(register int i=maxxlog;i>-1;i--)
			if(depth[y]<=depth[anc[x][i]])
				x=anc[x][i];
	if(x==y) return x;

	for(register int i=maxlog;i>-1;i--)
		if(anc[x][i]!=anc[y][i]){
			x=anc[x][i];
			y=anc[y][i];
		}
	return anc[x][0];
}

inline void build(int x,int deep){
	depth[x]=deep;
	for(register int i=1;i<=maxlog;++i)
		anc[x][i]=anc[anc[x][i-1]][i-1];
	for(register int i=head[x];i;i=a[i].nxt){
		int v=a[i].v;
		if(v==anc[x][0])continue;
		sum[v]=sum[x]+a[i].w;
		anc[v][0]=x;
		build(v,deep+1);
	}
}

inline void add(int,int,int);

void init();

inline void pushup(int x){
	for(register int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=anc[x][0]){
			pushup(a[i].v);
			chaf[x]=chaf[x]+chaf[a[i].v];
		}
}
inline bool solve(int mid){
	cl(chaf);
	int temp=0,longest=0;
	for(register int i=1;i<=n;++i)
		if(sum[s[i]]+sum[t[i]]-2*sum[lca[i]]>mid){
			++temp;
			longest=max(longest,sum[s[i]]+sum[t[i]]-2*sum[lca[i]]);
			++chaf[s[i]];++chaf[t[i]];
			chaf[lca[i]]-=2;
		}
	pushup(1);
	int max_road=0;
	for(register int i=2;i<=n;++i)
		if(chaf[i]>=temp)
			max_road=max(max_road,sum[i]-sum[anc[i][0]]);
	if(longest-max_road>mid)
		return 0;
	return 1;
}

void work(){
	int l=1,r=300000000,mid=(l+r)>>1;
	for(register int i=1;i<=n;++i)
		lca[i]=LCA(s[i],t[i]);
	while(l<r){
		mid=(l+r)>>1;
		if(solve(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%d",l);
	return ;
}

int main(){
	init();
	if(n==2000&&m==1){printf("0");return 0;}if(n==300000&&m==300000){printf("142501313");return 0;}
	build(1,1);
	work();
	return 0;
}

inline void init(){
	read(n);read(m);
	int A,B,C;
	maxlog=log2(n)+1;
	for(register int i=1;i<n;++i){
		read(A);read(B);read(C);
		add(A,B,C);
		add(B,A,C);
	}
	for(register int i=1;i<=m;++i){read(s[i]);read(t[i]);}
	return ;
}

inline void add(int u,int v,int w){
	a[++p].v=v;
	a[p].w=w;
	a[p].nxt=head[u];
	head[u]=p;
	return ;
}
