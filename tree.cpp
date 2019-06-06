//bzoj-2654
#include <bits/stdc++.h>
using namespace std;
#define rg register

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();return x;
}

const int N=50100,M=101000;
int d[N],n,m,k,ans;
inline int find(int x){return d[x]?d[x]=find(d[x]):x;}

struct node{
	int l,r,v,k;
	inline void in(){read(l),read(r),read(v),read(k),++l,++r;}
	friend inline int operator < (const node&A,const node&B) {return A.v^B.v?A.v<B.v:A.k<B.k;}
}e[M],ee[M];

int calc(int t){
	for(rg int i=m;i;--i){
		ee[i]=e[i];
		if(!e[i].k)ee[i].v+=t;
	}for(rg int i=n;i;--i)d[i]=0;
	sort(ee+1,ee+m+1);int res(0);ans=0;
	for(rg int i=1,p1,p2,j=n-1;i<=m&&j;++i,--j){
		while((p1=find(ee[i].l))==(p2=find(ee[i].r))&&i<=m)++i;
		d[p1]=p2;ans+=ee[i].v,res+=(!ee[i].k);
	}return res;
}

int main(){
	read(n),read(m),read(k);
	for(rg int i=m;i;--i)e[i].in();
	int l=-100,r=100,mid,res;
	while(l<=r)
		if(calc(mid=l+r>>1)<k)r=mid-1;
		else res=ans-mid*k,l=mid+1;
	printf("%d\n",res);return 0;
}
