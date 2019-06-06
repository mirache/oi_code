//ZeroJudge-c182
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')ob=1,c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=301000;
int a[N],n,ans;

int main(){
	read(n);
	for(rg int i=1;i<=n;++i)read(a[i]);
	for(rg int i=1;i<=n;++i)if(a[i]){
		++ans;
		for(rg int j=i;j<=n;j+=i)a[j]^=1;
	}printf("%d\n",ans);return 0;
}
