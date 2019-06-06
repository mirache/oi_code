//AtCoder-agc002C
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')ob=1,c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=101000;
int a[N],ps,n;
ll L,len;

int main(){
	read(n),read(L);read(a[1]);
	for(int i=2;i<=n;++i){
		read(a[i]);
		if(a[i-1]+a[i]>=L)ps=i;
	}
	if(!ps)puts("Impossible");
	else {
		puts("Possible");
		--ps;
		for(int i=1;i<ps;++i)
			printf("%d\n",i);
		for(int i=n-1;i>=ps;--i)
			printf("%d\n",i);
	}return 0;
}
