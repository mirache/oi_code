#include<bits/stdc++.h>
using namespace std;
#define cl(x) memset(x,0,sizeof(x))
#define check(x,y) (father(x)==father(y))
#define inf 202020202

int n,m,s,t;
template <typename __> inline void read(__ &x){
	x=0;char c11=getchar();bool booo=0;
	while(c11<'0'||c11>'9'){if(c11=='-')booo=1;c11=getchar();}
	while(c11>='0'&&c11<='9'){x=x*10+c11-'0';c11=getchar();}
	if(booo)x=-x;
	return ;
}

const int maxn=505,maxm=5005;
int dad[maxn];
struct node{int u,v,w;}a[maxm];
void init();

inline bool my_comp(const node &aa,const node &bb){return aa.w<bb.w;}

inline int father(int x){if(!dad[x])return x;dad[x]=father(dad[x]);return dad[x];}

inline int gcd(int aaaaa,int bbbbb){return bbbbb?gcd(bbbbb,aaaaa%bbbbb):aaaaa;}

void work(){
	float minn=inf;
	int lala,haha;
	sort(a+1,a+m+1,my_comp);
	for(int i=1;i<=n;i++){
		cl(dad);
		int p=0;
		for(int j=i;j<=n;j++){
			int u=a[j].u,v=a[j].v;
			if(!check(u,v))
				dad[father(u)]=v;
			if(check(s,t)){
				p=j;
				break;
			}
		}
		if(!p)break;
		if((float)a[p].w/a[i].w<minn){
			lala=a[p].w;haha=a[i].w;minn=(float)a[p].w/a[i].w;
		}
	}
	if(minn==inf){printf("IMPOSSIBLE");return ;}
	if(!(lala%haha)){printf("%d",lala/haha);return ;}
	printf("%d/%d",lala/gcd(lala,haha),haha/gcd(lala,haha));
	return ;
}

int main(){
	init();
	work();
	return 0;
}

void init(){
	read(n);read(m);
	for(int i=1;i<=m;i++){read(a[i].u);read(a[i].v);read(a[i].w);}
	read(s);read(t);
}
