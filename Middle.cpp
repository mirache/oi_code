#include<algorithm>
#include<cstdio>
#include<cctype>
using namespace std;
typedef long long ll;
#define rg register
#define cl(x) memset(x,0,sizeof(x))

template <typename _Tp> inline _Tp read(_Tp&x){
	rg char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')c11=getchar(),ob=1;
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=21000,L=1000000;
struct lst{int l,r,lx,rx,s;}seg[L];
int a[N],id[N],rt[N];
int n,m,tot;

inline int cmp(const int&cp1,const int&cp2){return a[cp1]<a[cp2];}

inline void up(int x){
	seg[x].s=seg[seg[x].l].s+seg[seg[x].r].s;
	seg[x].lx=max(seg[seg[x].l].lx,seg[seg[x].l].s+seg[seg[x].r].lx);
	seg[x].rx=max(seg[seg[x].r].rx,seg[seg[x].r].s+seg[seg[x].l].rx);
	return ;
}

inline void build(int&x,int l,int r){
	x=++tot;
	if(l==r){
		seg[x].lx=seg[x].rx=seg[x].s=1;
		return ;
	}
	int mid=(l+r)>>1;
	build(seg[x].l,l,mid);
	build(seg[x].r,mid+1,r);
	up(x);return ;
}

inline void update(int las,int&x,int l,int r,int pos){
	seg[x=++tot]=seg[las];
	if(l==r){
		seg[x].lx=seg[x].rx=seg[x].s=-1;
		return ;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)update(seg[las].l,seg[x].l,l,mid,pos);
	else update(seg[las].r,seg[x].r,mid+1,r,pos);
	up(x);return ;
}

inline int qs(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R)return seg[x].s;
	int mid=(l+r)>>1,res(0);
	if(L<=mid)res+=qs(seg[x].l,l,mid,L,R);
	if(mid<R)res+=qs(seg[x].r,mid+1,r,L,R);
	return res;
}

inline int ql(int x,int l,int r,int L,int R){
	if(l==L&&r==R)return seg[x].lx;
	int mid=(l+r)>>1;
	if(R<=mid)return ql(seg[x].l,l,mid,L,R);
	if(mid<L)return ql(seg[x].r,mid+1,r,L,R);
	return max(ql(seg[x].l,l,mid,L,mid),qs(seg[x].l,l,mid,L,mid)+ql(seg[x].r,mid+1,r,mid+1,R));
}

inline int qr(int x,int l,int r,int L,int R){
	if(l==L&&R==r)return seg[x].rx;
	int mid=(l+r)>>1;
	if(R<=mid)return qr(seg[x].l,l,mid,L,R);
	if(mid<L)return qr(seg[x].r,mid+1,r,L,R);
	return max(qr(seg[x].r,mid+1,r,mid+1,R),qs(seg[x].r,mid+1,r,mid+1,R)+qr(seg[x].l,l,mid,L,mid));
}

inline int check(int k,int*q){
	int res(0);
	if(q[2]+1<q[3])res+=qs(rt[k],1,n,q[2]+1,q[3]-1);
	res+=ql(rt[k],1,n,q[3],q[4]);
	res+=qr(rt[k],1,n,q[1],q[2]);
	return res>=0;
}

int main(){
	read(n);
	for(rg int i=1;i<=n;++i)read(a[i]),id[i]=i;
	sort(id+1,id+n+1,cmp);
	build(rt[1],1,n);
	for(rg int i=2;i<=n;++i)update(rt[i-1],rt[i],1,n,id[i-1]);
	read(m);
	int q[5],lastans(0);
	while(m--){
		for(rg int i=1;i<5;++i)read(q[i]),q[i]=((ll)q[i]+lastans)%n+1;
		sort(q+1,q+5);
		rg int l=1,r=n+1,mid;
		while(l+1<r){
			mid=(l+r)>>1;
			if(check(mid,q))l=mid;
			else r=mid;
		}
		printf("%d\n",lastans=a[id[l]]);
	}
	return 0;
}
