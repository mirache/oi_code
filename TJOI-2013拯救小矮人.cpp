#include <bits/stdc++.h>

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

inline void cmax(int&A,int B){A=A>B?A:B;}

const int N=2050;
int f[N],n,H;

struct node{
	int a,b;
	inline void in(){read(a),read(b),f[0]+=a;}
	friend inline bool operator < (const node&A,const node&B) {return A.a+A.b<B.a+B.b;}
}p[N];

int main(){
	read(n);
	for(int i=1;i<=n;++i)
		p[i].in(),f[i]=-1;
	read(H);
	std::sort(p+1,p+n+1);
	for(int i=1;i<=n;++i)
		for(int j=i;j;--j)
		if(f[j-1]+p[i].b>=H)
			cmax(f[j],f[j-1]-p[i].a);
	for(int i=n;~i;--i)if(~f[i])
		{printf("%d\n",i);return 0;}
}
