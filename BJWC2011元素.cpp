#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register

template <typename _Tp> inline _Tp read(_Tp&x){
	rg char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')c11=getchar(),ob=1;
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=1010,M=62;
int n;
ll a[M+3];

struct Thing{
	ll id,v;
	inline bool operator < (const Thing&bb) const {return v>bb.v;}
}t[N];

int main(){
	read(n);
	for(rg int i=1;i<=n;++i)read(t[i].id),read(t[i].v);
	sort(t+1,t+n+1);
	ll ans(0);
	for(rg int i=1;i<=n;++i){
		ll x=t[i].id;
		for(rg int j=M;~j;--j)
			if(((x>>j)&1)&&a[j])
			if(!(x^=a[j]))break;
		if(!x)continue;
		x=t[i].id;ans+=t[i].v;
		for(rg int j=M;~j;--j)
			if((x>>j)&1)
				if(a[j])x^=a[j];
				else {a[j]=x;break;}
	}
	printf("%lld\n",ans);
	return 0;
}
