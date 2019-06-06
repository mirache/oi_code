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
struct EDGE{int v,w,nxt;}a[N];
int head[N],f[N],g[N],h[N],tmp[N],top;
int n,m,p,k,ans,cnt,_;

inline void add(int u,int v,int w){a[++_].v=v,a[_].w=w,a[_].nxt=head[u],head[u]=_;}

void init();void work();void print();
int main(){init();work();print();return 0;}

void print(){
	for(rg int i=1;i<=n;++i){
		int b=upper_bound(f+1,f+n+1,k-g[i])-f-1;
		ans=max(ans,b-i+1);
		if(f[i]==0&&0==g[i])++cnt;
	}printf("%d\n",ans-cnt);
	return ;
}

void work(){
	for(rg int x=2;x<=n;++x){
		int t=0;
		for(rg int i=head[x];i;i=a[i].nxt)
			if(a[i].v<x)tmp[++t]=a[i].w;
		if(t){
			sort(tmp+1,tmp+t+1);
			int b=lower_bound(tmp+1,tmp+t+1,h[top])-tmp;
			if(b<=t&&tmp[b]>=h[top])h[++top]=tmp[b];
			for(rg int i=b-1;i;--i){
				b=upper_bound(h+1,h+top+1,tmp[i])-h;
				h[b]=tmp[i];
			}
		}f[x]=x-1-top;
	}h[top=0]=0;
	for(rg int x=n-1;x;--x){
		int t=0;
		for(rg int i=head[x];i;i=a[i].nxt)
			if(a[i].v>x)tmp[++t]=a[i].w;
		if(t){
			sort(tmp+1,tmp+t+1);
			int b=lower_bound(tmp+1,tmp+t+1,h[top])-tmp;
			if(b<=t&&tmp[b]>=h[top])h[++top]=tmp[b];
			for(rg int i=b-1;i;--i){
				b=upper_bound(h+1,h+top+1,tmp[i])-h;
				h[b]=tmp[i];
			}
		}g[x]=n-x-top;
	}return ;
}

void init(){
	read(n);read(m);read(p);read(k);
	int x,y,z;
	for(rg int i=1;i<=p;++i){
		read(x);read(y);read(z);y=m-y+1;
		if(!z)add(x,x+1,y);
		else add(x+1,x,y);
	}return ;
}
