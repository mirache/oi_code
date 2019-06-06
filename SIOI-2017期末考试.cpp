#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
#define rg register

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')c11=getchar(),ob=1;
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=101000;
ll t[N],b[N],A,B,C;
int n,m,mxl=0;
ll p,pp,ra,rb,rt;

void file();void init();void work();
int main(){file();init();work();return 0;}
void file(){return ;freopen("1.in","r",stdin);}

void init(){
	read(A);read(B);read(C);
	read(n);read(m);
	for(rg int i=1;i<=n;++i)read(t[i]);
	for(rg int i=1;i<=m;++i)read(b[i]),mxl=max((ll)mxl,b[i]),rb+=b[i];
	sort(t+1,t+n+1);sort(b+1,b+m+1);
	return ;
}

void work(){
	ll Ans=0x3f3f3f3f3f3f3f3f;
	for(rg int g=1;g<=mxl;++g){
		ra+=p,rb-=m-p,rt+=pp;
		while(b[p+1]<=g&&p<m)++p;
		while(t[pp+1]<=g&&pp<n)++pp;
		ll tch,tsu;
		if(A<=B)tch=ra<rb?ra*A+(rb-ra)*B:tch=rb*A;
		else tch=rb*B;
		tsu=rt*C;
		Ans=min(Ans,tsu+tch);
	}printf("%llu\n",Ans);
	return ;
}
