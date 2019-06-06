//CodeForces-1003D
#include <bits/stdc++.h>
using namespace std;
#define rg register

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')ob=1,c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

int bin[31],t[31];
map <int,int> mp;
int n,m;

int main(){
	read(n),read(m);
	mp[bin[0]=1]=0;int x,d,r;
	for(rg int i=1;i<31;++i)
		mp[bin[i]=bin[i-1]<<1]=i;
	for(rg int i=1;i<=n;++i)
		++t[mp[read(x)]];
	while(m--){
		read(x);r=d=0;
		for(rg int i=30;~i;--i,d<<=1){
			if(x&bin[i])++d;
			x-=x&bin[i];
			if(d&&t[i])r+=min(d,t[i]),d-=min(d,t[i]);
			if(d<=0&&!x){d=-1;break;}
		}
		printf("%d\n",(~d)?-1:r);
	}return 0;
}
