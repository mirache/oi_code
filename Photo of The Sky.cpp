//CodeForces-1012A
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N=201000;
int a[N],n;

int main(){
	read(n);
	for(int i=1;i<=n+n;++i)read(a[i]);
	sort(a+1,a+n+n+1);
	ll ans=1ll*(a[n]-a[1])*(a[n+n]-a[n+1]);
	for(int i=2;i<=n+1;++i)
		ans=min(ans,1ll*(a[n+n]-a[1])*(a[i+n-1]-a[i]));
	printf("%lld\n",ans);
	return 0;
}
