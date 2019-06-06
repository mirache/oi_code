#include<bits/stdc++.h>
using namespace std;
#define cl(x) memset(x,0,sizeof(x))
#define cl1(x) memset(x,-1,sizeof(x))
#define clm(x) memset(x,0x3f3f3f3f,sizeof(x))
#define rg register

template <typename _Tp> inline void read(_Tp &x){char c11=getchar();x=0;
	while(c11<'0'||c11>'9')c11=getchar();while(c11>='0'&&c11<='9'){x=x*10+c11-'0';c11=getchar();}
	return ;
}

const int maxn=3e5,maxm=6e5;
int w[maxn];
struct node	{int v,nxt;} a[maxm],a1[maxm],a2[maxm],a3[maxm];
int head[maxn],head1[maxn],head2[maxn],head3[maxn];
int p=0,p1=0,p2=0,p3=0;
int shang[maxm<<1],xia[maxm<<1];
int ans[maxn],cnt[maxn];
int n,m;
int anc[maxn][23],depth[maxn];

inline void add(int,int);
inline void add1(int u,int v){a1[++p1].v=v;a1[p1].nxt=head1[u];head1[u]=p1;}
inline void add2(int u,int v){a2[++p2].v=v;a2[p2].nxt=head2[u];head2[u]=p2;}
inline void add3(int u,int v){a3[++p3].v=v;a3[p3].nxt=head3[u];head3[u]=p3;}

void init();

int LCA(int,int);

void lca_dfs(int,int);

void pre();

void dfs(int x,int las){
   int xia_=xia[depth[x]+w[x]],shang_=shang[depth[x]-w[x]+maxn];
   xia[depth[x]]+=cnt[x];
   
   for(rg int i=head1[x];i;i=a1[i].nxt)++shang[a1[i].v+maxn];
   
   for(rg int i=head[x];i;i=a[i].nxt)if(a[i].v!=las)dfs(a[i].v,x);
   
   ans[x]=xia[depth[x]+w[x]]+shang[depth[x]-w[x]+maxn]-xia_-shang_;
   
   for(rg int i=head2[x];i;i=a2[i].nxt){--xia[a2[i].v];if(a2[i].v==depth[x]+w[x])--ans[x];}
   
   for(rg int i=head3[x];i;i=a3[i].nxt)--shang[a3[i].v+maxn];
}

void print(){for(rg int i=1;i<=n;++i)printf("%d ",ans[i]);printf("\n");}

int main(){
	init();
	pre();
	dfs(1,0);
	print();
	return 0;
}

void pre(){
	lca_dfs(1,0);
	for(rg int j=1;j<=20;j++)for(rg int i=1;i<=n;i++)anc[i][j]=anc[anc[i][j-1]][j-1];
	int u,v;
	for(rg int i=1;i<=m;++i){
		read(u);read(v);
		int lca=LCA(u,v),len=depth[u]+depth[v]-(depth[lca]<<1),over=depth[v]-len;
		++cnt[u];
		add1(v,over);add2(lca,depth[u]);add3(lca,over);
	}
}

int LCA(int x,int y){
	if(x==y)return x;
	if(depth[x]<depth[y])swap(x,y);
	for(rg int i=22;i>-1;--i)if(depth[anc[x][i]]>=depth[y])x=anc[x][i];
	if(x==y)return x;
	for(rg int i=22;i>-1;--i)if(anc[x][i]!=anc[y][i])x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}

void lca_dfs(int x,int y){
    int i;
    depth[x]=depth[y]+1,anc[x][0]=y;
    for(rg int i=head[x];i;i=a[i].nxt)if(a[i].v!=y)lca_dfs(a[i].v,x);
}

void init(){
	read(n);read(m);
	cl(head);cl(head1);cl(head2);cl(head3);
	cl(cnt);cl(xia);cl(shang);cl(ans);
	int A,B;
	for(rg int i=1;i<n;++i){
		read(A);read(B);
		add(A,B);add(B,A);
	}
	for(rg int i=1;i<=n;++i)read(w[i]);
}

inline void add(int u,int v){
	a[++p].v=v;
	a[p].nxt=head[u];
	head[u]=p;
}
