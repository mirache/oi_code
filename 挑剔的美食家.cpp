#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register
#define inf 0x3f3f3f3f
#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))
#define abs(x) ((x)>0?(x):(-(x)))
#define oo 0x7fffffff

#define blood(x) (ch[f[x]][1]==x)

template <typename _Tp> inline void read(_Tp&x){char c11=getchar();x=0;bool booo=0;
	while(c11!='-'&&!isdigit(c11))c11=getchar();if(c11=='-'){booo=1;c11=getchar();}
	while(isdigit(c11)){x=x*10+c11-'0';c11=getchar();}if(booo)x=-x;return ;
}

const int N=105000;
int f[N],ch[N][2];ll data[N],tot[N];
struct node{ll cost,fresh;}cow[N],grass[N];
int sz=0,root=0,n,m;

inline bool cow_comp(const node&aa,const node&bb){
	if(aa.fresh==bb.fresh)return aa.cost>bb.cost;
	return aa.fresh>bb.fresh;
}

inline bool my_comp(const node&aa,const node&bb){
	if(aa.fresh==bb.fresh)return aa.cost<bb.cost;
	return aa.fresh>bb.fresh;
}

void init();

inline void rotate(int x){
	int fa=f[x],grand=f[f[x]],le=blood(x);
	f[x]=grand;
	if(grand)ch[grand][blood(fa)]=x;
	ch[fa][le]=ch[x][le^1];
	if(ch[fa][le])f[ch[fa][le]]=fa;
	f[fa]=x;
	ch[x][le^1]=fa;
	return ;
}

void splay(int x,int target){
	for(int fa;(fa=f[x])!=target;rotate(x))
	if(f[f[x]]!=target)rotate(blood(x)==blood(f[x])?f[x]:x);
	if(!target)root=x;return ;
}

int front(){int now=root;now=ch[now][0];while(ch[now][1])now=ch[now][1];return now;}

int back(){int now=root;now=ch[now][1];while(ch[now][0])now=ch[now][0];return now;}

int find(ll x){
	int now=root;
	while(1){
		if(data[now]==x){
			if(tot[now]>1){--tot[now];return data[now];}
			splay(now,0);int fr=front(),ba=back();
			splay(fr,0);splay(ba,fr);
			ch[ba][0]=0;
			return data[now];
		}
		if(ch[now][x>data[now]])
			now=ch[now][x>data[now]];
		else break;
	}
	//if(now<3)return -1;
	if(data[now]>=x){
		if(tot[now]>1){--tot[now];return data[now];}
		splay(now,0);int fr=front(),ba=back();
		splay(fr,0);splay(ba,fr);
		ch[ba][0]=0;
		return data[now];
	}
	else{
		splay(now,0);
		now=back();if(now==-1||now<3)return -1;
			if(tot[now]>1){--tot[now];return data[now];}
			splay(now,0);int fr=front(),ba=back();
			splay(fr,0);splay(ba,fr);
			ch[ba][0]=0;
			return data[now];
	}
}

void ins(ll x){
	if(!root){root=++sz;data[sz]=x;tot[sz]=1;f[sz]=ch[sz][0]=ch[sz][1]=0;return ;}
	int now=root;
	while(1){
		if(data[now]==x){++tot[now];return ;}
		if(ch[now][x>data[now]])
			now=ch[now][x>data[now]];
		else break;
	}
	ch[now][x>data[now]]=++sz;
	data[sz]=x;
	f[sz]=now;tot[sz]=1;
	splay(sz,0);
	return ;
}

void work(){
	int p=1;ll ans=0;
	ins(-oo);ins(+oo);
	for(rg int i=1;i<=n;++i){
		while(grass[p].fresh>=cow[i].fresh&&p<=m){ins(grass[p].cost);++p;}
		int t=find(cow[i].cost);
		if(t==-1){puts("-1");return ;}
		ans+=t;
	}
	printf("%lld\n",ans);
	return ;
}

int main(){
	freopen("gourmet.in","r",stdin);
	freopen("gourmet.out","w",stdout);
	init();
	work();
	return 0;
}

void init(){
	read(n);read(m);
	for(rg int i=1;i<=n;++i){read(cow[i].cost);read(cow[i].fresh);}
	for(rg int i=1;i<=m;++i){read(grass[i].cost);read(grass[i].fresh);}
	sort(cow+1,cow+n+1,cow_comp);
	sort(grass+1,grass+m+1,my_comp);
	return ;
}
