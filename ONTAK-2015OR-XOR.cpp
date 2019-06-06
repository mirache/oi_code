//bzoj-4245
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')ob=1,c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=501000;
typedef bitset<N> bit;
ll a[N];int n,m;
bit c;

int yep(ll bs){
	int t=0;
	bit nw;nw.reset();
	for(rg int i=1;i<=n;++i){
		if(a[i]&bs)++t;
		if(!(t&1))nw.set(i);
	}
	if(t&1)return 0;
	nw&=c;
	if(nw.count()<m)return 0;
	c&=nw;return 1;
}

int main(){
	read(n),read(m);c.set();
	for(rg int i=1;i<=n;++i)read(a[i]);
	ll ans(0ll);
	for(rg int i=59;~i;--i)
		if(!yep(1ll<<i))ans|=(1ll<<i);
	printf("%lld\n",ans);
}
