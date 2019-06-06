//bzoj-1758
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename _tp> inline void read(_tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11!='-'&&!isdigit(c11))c11=getchar();if(c11=='-')c11=getchar(),ob=1;
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;
}

inline void cmax(double&A,double B){A=A>B?A:B;}

const int N=201003;
struct Edge{int v,nxt,w;}a[N+N];
int head[N],son[N],len[N],fa[N],sw[N];
double Minus[N],Plus[N],sg[N<<2];
int id[N],dfc;
int n,_;
double qwq,ans;

inline void ad(){
	static int u,v,w;read(u),read(v),read(w);
	a[++_].v=v,a[_].w=w,a[_].nxt=head[u],head[u]=_;
	a[++_].v=u,a[_].w=w,a[_].nxt=head[v],head[v]=_;
}

void get_son(int x){
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=fa[x]){
			fa[a[i].v]=x;
			get_son(a[i].v);
			if(len[a[i].v]>len[son[x]])
				son[x]=a[i].v,sw[x]=a[i].w;
		}
	len[x]=len[son[x]]+1;
}

void set_son(int x){
	id[x]=++dfc;
	if(son[x])set_son(son[x]);
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=fa[x] and a[i].v!=son[x])
			set_son(a[i].v);
}

void reset(int l,int r,int x){
	sg[x]=-1e10;
	if(l==r)return ;
	int mid(l+r>>1);
	reset(l,mid,x<<1);
	reset(mid+1,r,x<<1|1);
}

double query(int l,int r,int x,int L,int R){
	if(L<=l and r<=R)return sg[x];
	int mid(l+r>>1);double mx=-1e10;
	if(L<=mid)mx=query(l,mid,x<<1,L,R);
	if(mid<R)cmax(mx,query(mid+1,r,x<<1|1,L,R));
	return mx;
}

void update(int l,int r,int x,int p){
	if(l==r){sg[x]=Minus[l];return ;}
	int mid(l+r>>1);
	if(p<=mid)update(l,mid,x<<1,p);
	else update(mid+1,r,x<<1|1,p);
	sg[x]=max(sg[x<<1],sg[x<<1|1]);
}

int UL,UR;

void dfs(int x){
	int t=id[x];
	Plus[t]=Minus[t]=0.0;
	if(son[x]){
		dfs(son[x]);
		Plus[t]+=Plus[id[son[x]]]+sw[x]-qwq;
		Minus[t]=-Plus[t];
	}
	update(1,n,1,t);
	for(int i=head[x],v,tt;i;i=a[i].nxt){
		v=a[i].v;
		if(v==fa[x] or v==son[x])continue;
		dfs(v);tt=id[v];
		for(int j=max(1,UL-len[x]);j<=len[v]+1;++j){
			double kv= Plus[t] + query(1,n,1,t+max(1,UL-j),t+min(len[x],UR-j));
			cmax(ans,kv + a[i].w-qwq+Plus[tt]+Minus[tt+j-1]);
		}
		for(int j=1;j<=len[v]+1;++j){
			double kv= a[i].w-qwq + Plus[tt]+Minus[tt+j-1] -Plus[t];
			if(Minus[t+j]<kv){
				Minus[t+j]=kv;
				update(1,n,1,t+j);
			}
		}
	}
	if(len[x]>=UL)
		cmax(ans,Plus[t]+query(1,n,1,t+UL,t+min(UR,len[x])));
}

bool check(double x){
	reset(1,n,1);qwq=x;
	ans=-1e10;dfs(1);
	return ans>=0.0;
}

int main(){
	read(n),read(UL),read(UR);
	for(int i=1;i<n;++i)ad();
	len[0]=-1;get_son(1);set_son(1);
	double l=0,r=2e6,mid,eps=1e-5;
	while(l+eps<r){
		mid=0.5*(l+r);
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%.3lf\n",l);
	return 0;
}