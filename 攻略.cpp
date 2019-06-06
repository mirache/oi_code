//bzoj-3252
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')ob=1,c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=201000;
struct Edge{int v,nxt;}a[N];
int head[N],val[N];ll f[N];
int n,k,_,top;

struct node{
	int ps;ll vl;
	inline node(){}inline node(const int&PS,const ll&VL):ps(PS),vl(VL){}
	friend inline int operator < (const node&A,const node&B) {return A.vl<B.vl;}
	friend inline int operator > (const node&A,const node&B) {return A.vl>B.vl;}
}st[N];

inline void push(node nw){
	static int x;st[x=++top]=nw;
	while(x>1&&st[x]>st[x>>1])swap(st[x],st[x>>1]),x>>=1;
}

inline void pop(){
	static int x;st[x=1]=st[top--];
	while(((x<<1)<=top&&st[x]<st[x<<1])||((x<<1|1)<=top&&st[x]<st[x<<1|1])){
		x<<=1;
		if(st[x]<st[x|1])x|=1;
		swap(st[x],st[x>>1]);
	}
}

void dfs(int x){
	for(int i=head[x];i;i=a[i].nxt){
		dfs(a[i].v);
		f[x]=max(f[x],f[a[i].v]);
	}f[x]+=val[x];
}

void init();void work();
int main(){init();work();return 0;}

void work(){
	dfs(1);ll ans(0ll);
	push(node(1,f[1]));
	while(k--&&top){
		int x=st[1].ps,tx;ans+=st[1].vl;pop();
		while(head[x]){
			for(int i=head[x];i;i=a[i].nxt)
				if(f[x]==f[a[i].v]+val[x])
					{tx=a[i].v;break;}
			for(int i=head[x];i;i=a[i].nxt)
				if(a[i].v^tx)
					push(node(a[i].v,f[a[i].v]));
			x=tx;
		}
	}printf("%lld\n",ans);
}

void init(){
	read(n),read(k);int u,v;
	for(rg int i=1;i<=n;++i)read(val[i]);
	for(rg int i=1;i<n;++i){
		read(u),read(v);
		a[++_].v=v,a[_].nxt=head[u],head[u]=_;
	}
}
