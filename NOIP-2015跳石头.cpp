#include<bits/stdc++.h>
using namespace std;

template <typename _Tp> inline void read(_Tp &x){
	char c11=getchar();x=0;
	while(c11<'0'||c11>'9')c11=getchar();
	while(c11>='0'&&c11<='9'){x=x*10+c11-'0';c11=getchar();}
	return ;
}

const int maxn=50050;
int L,n,m;
int s[maxn];

void init();

inline bool check(int limit){
	int temp=0;
	int i=0,j;
	while(i<=n){
		j=i+1;
		while(s[j]-s[i]<limit&&j<n+2)j++;
		temp+=j-i-1;
		i=j;
	}
	return temp<=m;
}

void work(){
	if(n==0){printf("%d\n",L);return ;}
	int l=0,r=L;
	while(l+1<r){
		int mid=(l+r)>>1;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%d\n",l);
	return ;
}

int main(){
	init();
	work();
	return 0;
}

void init(){
	read(L);read(n);read(m);s[0]=0;s[n+1]=L;
	for(int i=1;i<=n;i++)read(s[i]);
}
