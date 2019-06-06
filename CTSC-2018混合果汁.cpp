#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')ob=1,c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=101000;
int rt[N],n,nn,m,tot=0;

struct node{
	int d,p,l;
	inline void in(){read(d),read(p),read(l);return ;}
	friend inline int operator < (const node&A,const node&B) {return A.d<B.d;}
}p[N];

struct lst{int l,r;ll w,s;}seg[N*22];

inline void update(int l,int r,int&x,int ps,int s,ll w){
	seg[++tot]=seg[x],x=tot;seg[x].s+=s,seg[x].w+=w;
	if(l==r)return ;int mid(l+r>>1);
	if(ps<=mid)update(l,mid,seg[x].l,ps,s,w);
	else update(mid+1,r,seg[x].r,ps,s,w);
	return ;
}

inline ll query(int l,int r,int x,ll li){
	if(l==r)return li*l;int mid(l+r>>1);
	if(li<=seg[seg[x].l].s)return query(l,mid,seg[x].l,li);
	return seg[seg[x].l].w+query(mid+1,r,seg[x].r,li-seg[seg[x].l].s);
}

inline void work(){
	ll gi,li;read(gi),read(li);
	int l(0),r(nn),mid,res(0);
	while(l<=r){
		mid=l+r>>1;
		if(li<=seg[rt[mid]].s&&query(0,nn,rt[mid],li)<=gi)l=(res=mid)+1;
		else r=mid-1;
	}printf("%d\n",p[res].d);
	return ;
}

int main(){
	read(n),read(m);p[0].d=-1;nn=100000;
	for(rg int i=1;i<=n;++i)p[i].in();
	sort(p+1,p+n+1);
	for(rg int i=n;i;--i)update(0,nn,rt[i]=rt[i+1],p[i].p,p[i].l,1ll*p[i].p*p[i].l);
	rt[0]=rt[1];while(m--)work();return 0;
}
