#include<bits/stdc++.h>
using namespace std;
#define rg register
#define cl(x) memset(x,0,sizeof(x))
#define max(x,y) ((x)>(y)?(x):(y))
#define cl1(x) memset(x,-1,sizeof(x))
typedef long long ll;

template <typename _Tp> inline void read(_Tp &x){
	char c11=getchar();x=0;while(c11<'0'||c11>'9')c11=getchar();
	while(c11>='0'&&c11<='9'){x=x*10+c11-'0';c11=getchar();}
}

const int maxn=505000;

int n,s;

ll maxx=0;

ll ans=0;

ll cha[maxn],minn[maxn],depth[maxn];

struct node{int v,nxt;ll w;}a[maxn];
int head[maxn],p=0;

void init();

inline void add(int,int,ll);

void pre(int x,ll deep,int las){
	depth[x]=deep;maxx=max(maxx,depth[x]);
	for(rg int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=las)
			pre(a[i].v,deep+a[i].w,x);
}

void prepare(int x,ll deep,int las){
	minn[x]=cha[x];
	for(rg int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=las){
			prepare(a[i].v,deep+a[i].w,x);
			minn[x]=min(minn[x],minn[a[i].v]);
		}
}

void dfs(int x,ll now,int las){
	ans+=minn[x]-now;
	for(rg int i=head[x];i;i=a[i].nxt)if(a[i].v!=las)
		dfs(a[i].v,minn[x],x);
}

void work(){
	pre(s,0,0);
	for(rg int i=1;i<=n;++i)cha[i]=maxx-depth[i];
	prepare(s,0,0);
	dfs(s,0,0);
	printf("%lld\n",ans);
	return ;
}

int main(){
	init();
	work();
	return 0;
}

void init(){
	read(n);read(s);
	int A,B;ll C;
	for(rg int i=1;i<n;++i){
		read(A);read(B);read(C);
		add(A,B,C);add(B,A,C);
	}
}

inline void add(int u,int v,ll w){
	a[++p].v=v;
	a[p].w=w;
	a[p].nxt=head[u];
	head[u]=p;
}
