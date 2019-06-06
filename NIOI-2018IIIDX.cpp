#include<bits/stdc++.h>
using namespace std;

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')c11=getchar(),ob=1;
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=501000;
int f[N],sz[N],cnt[N],a[N],t[N<<2],lz[N<<2],Ans[N];
int n,m;double k;

inline int cmp(const int&A,const int&B){return A>B;}

inline void build(int l,int r,int x){
	if(l==r){t[x]=l;return ;}
	int mid(l+r>>1);
	build(l,mid,x<<1);
	build(mid+1,r,x<<1|1);
	t[x]=min(t[x<<1],t[x<<1|1]);
	return ;
}

inline void down(int x){
	if(lz[x]){
		lz[x<<1]+=lz[x],t[x<<1|1]+=lz[x];
		lz[x<<1|1]+=lz[x],t[x<<1]+=lz[x];
		lz[x]=0;
	}return ;
}

inline void update(int l,int r,int x,int L,int R,int vl){
	if(L<=l&&r<=R){lz[x]+=vl;t[x]+=vl;return ;}
	down(x);int mid(l+r>>1);
	if(L<=mid)update(l,mid,x<<1,L,R,vl);
	if(mid<R)update(mid+1,r,x<<1|1,L,R,vl);
	t[x]=min(t[x<<1],t[x<<1|1]);return ;
}

inline int query(int l,int r,int x,int rk){
	if(l==r)return t[x]>=rk?l:l+1;
	down(x);int mid(l+r>>1);
	if(t[x<<1|1]<rk)return query(mid+1,r,x<<1|1,rk);
	else return query(l,mid,x<<1,rk);
}

int main(){
	read(n);scanf("%lf",&k);
	for(int i=1;i<=n;++i)read(a[i]);
	sort(a+1,a+n+1,cmp);
	for(int i=n;i;--i){
		f[i]=(int)(1.0*i/k);
		++sz[i];sz[f[i]]+=sz[i];
		if(a[i]==a[i+1])cnt[i]=cnt[i+1]+1;
	}
	build(1,n,1);
	for(int i=1;i<=n;++i){
		if(f[i]!=f[i-1])update(1,n,1,Ans[f[i]],n,sz[f[i]]-1);
		int x=query(1,n,1,sz[i]);
		x+=cnt[x],++cnt[x],x-=cnt[x]-1,Ans[i]=x;
		update(1,n,1,x,n,-sz[i]);
	}
	for(int i=1;i<=n;++i)printf("%d ",a[Ans[i]]);
	putchar('\n');return 0;
}
