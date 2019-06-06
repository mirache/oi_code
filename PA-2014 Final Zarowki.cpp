//bzoj-3728
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register

template <typename _Tp> inline _Tp read(_Tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')ob=1,c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=501000;
int a[N],b[N];ll h[N],H[N];
int n,k,top,Top;
ll ans;

inline void Push(ll x){
	H[++Top]=x;int pp=Top;
	while(pp^1&&H[pp]<H[pp>>1])swap(H[pp],H[pp>>1]),pp>>=1;
	return ;
}

inline void Pop(){
	H[1]=H[Top--];int pp=1;
	while(((pp<<1)<=Top&&H[pp]>H[pp<<1])||((pp<<1|1)<=Top&&H[pp]>H[pp<<1|1])){
		pp<<=1;
		if(H[pp]>H[pp|1])pp|=1;
		swap(H[pp],H[pp>>1]);
	}return ;
}

inline void push(ll x){
	h[++top]=x;int pp=top;
	while(pp^1&&h[pp]>h[pp>>1])swap(h[pp],h[pp>>1]),pp>>=1;
	return ;
}

inline void pop(){
	h[1]=h[top--];int pp=1;
	while(((pp<<1)<=top&&h[pp]<h[pp<<1])||((pp<<1|1)<=top&&h[pp]<h[pp<<1|1])){
		pp<<=1;
		if(h[pp]<h[pp|1])pp|=1;
		swap(h[pp],h[pp>>1]);
	}return ;
}

int main(){
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	read(n);read(k);
	for(rg int i=1;i<=n;++i)read(a[i]);sort(a+1,a+n+1);
	for(rg int i=1;i<=n;++i)read(b[i]);sort(b+1,b+n+1);
	int he=n;
	for(rg int i=n;i;--i){
		while(he&&a[he]>=b[i])Push(a[he--]);
		if(!Top)--k,ans+=b[i];
		else {
			int x=H[1];Pop();
			ans+=x;push(x-b[i]);
		}
	}
	if(k<0){puts("NIE");return 0;}
	while(k--)ans-=h[1],pop();
	printf("%lld\n",ans);return 0;
}
