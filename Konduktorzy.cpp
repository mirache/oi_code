//bzoj-3735
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')ob=1,c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

template <typename _Tp> inline _Tp max(_Tp&x,_Tp&y){return x>y?x:y;}
template <typename _Tp> inline _Tp min(_Tp&x,_Tp&y){return x<y?x:y;}

const int N=101000;
ll a[N],ans[N];
ll m,n,nn,ps,R,top;

struct node{
	ll first;int second;
	node(){}
	node(const ll&X,const int&Y):first(X),second(Y){}
	friend int operator < (const node&A,const node&B) {return A.first==B.first?A.second<B.second:A.first<B.first;}
	friend int operator > (const node&A,const node&B) {return A.first==B.first?A.second>B.second:A.first>B.first;}
}h[N];

inline void push(node x){
	h[++top]=x;int pp=top;
	while(pp^1&&h[pp]<h[pp>>1])swap(h[pp],h[pp>>1]),pp>>=1;
	return ;
}

inline void pop(){
	h[1]=h[top--];int pp=1;
	while(((pp<<1)<=top&&h[pp]>h[pp<<1])||((pp<<1|1)<=top&&h[pp]>h[pp<<1|1])){
		pp<<=1;
		if(h[pp]>h[pp|1])pp|=1;
		swap(h[pp],h[pp>>1]);
	}return ;
}

inline int check(ll x){
	ll t=m;
	for(rg int i=1;i<=n;++i){
		t-=x/a[i];
		if(t<0)return 0;
	}
	return 1; 
}

void file();void init();void work();
int main(){file();init();work();return 0;}

void file(){}

void work(){
	while(nn<m){
		node x=h[1];pop();
		ans[x.second]=++nn;
		x.first+=a[x.second];
		push(x);
	}
	for(rg int i=1;i<=n;++i)
		printf("%lld ",ans[i]);
	putchar('\n');return ;
}

void init(){
	read(m);read(n);
	ll l,r=0ll,mid;
	for(rg int i=1;i<=n;++i)r=max(r,read(a[i]));
	l=r+1,r*=m;
	while(l<=r)
		if(check(mid=(l+r>>1)))l=(ps=mid)+1;
		else r=mid-1;
	R=ps;
	for(rg int i=1;i<=n;++i)R=min(R,max((ps/a[i]-1)*a[i],0ll));
	for(rg int i=1;i<=n;++i)nn+=R/a[i],push(node(R/a[i]*a[i],i));
	return ;
}
