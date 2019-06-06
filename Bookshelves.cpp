//Codeforces-981D
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename _tp> inline void read(_tp&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N = 53;
int f[N][N],n,k;
ll a[N];

bool chk(ll S){
	for(int i=0;i<=n;++i)
	for(int j=0;j<=k;++j) f[i][j] = 0;
	f[0][0] = 1;
	for(int i=1;i<=n;++i)
	for(int j=1;j<=k;++j){
		ll s = a[i];
		for(int l=i-1;~l;--l){
			if(f[l][j-1] and ((s & S) == S)) {f[i][j] = 1; break;}
			s += a[l];
		}
	}
	return f[n][k];
}

int main(){
	read(n), read(k);
	for(int i=1;i<=n;++i) read(a[i]);
	ll S = 0;
	for(int i=57;~i;--i){
		S ^= 1ll<<i;
		if(!chk(S)) S ^= 1ll<<i;
	}
	printf("%lld\n",S);
	return 0;
}
