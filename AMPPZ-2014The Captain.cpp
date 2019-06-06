//bzoj-4152
#include <bits/stdc++.h>
using namespace std;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N=401000,inf=0x3f3f3f3f;
struct pnt{int x,y,id;}p[N];
struct Edge{int v,nxt,w;}a[N<<1];
struct node{
	int x,v;
	inline node(){}
	inline node(const int&X,const int&V):x(X),v(V){}
}h[N<<1];

int dis[N],head[N];
int top,n,_;

inline bool cpx(const pnt&A,const pnt&B) {return A.x<B.x;}
inline bool cpy(const pnt&A,const pnt&B) {return A.y<B.y;}

inline void add(int x,int y,int z){
	a[++_].v=y,a[_].w=z,a[_].nxt=head[x],head[x]=_;
	a[++_].v=x,a[_].w=z,a[_].nxt=head[y],head[y]=_;
}

inline void push(node nw){
	h[++top]=nw;
	int pp=top;
	while(pp>1&&h[pp].v<h[pp>>1].v)
		swap(h[pp],h[pp>>1]),pp>>=1;
}

inline void pop(){
	int pp=1;
	h[1]=h[top--];
	while(((pp<<1)<=top&&h[pp].v>h[pp<<1].v)||((pp<<1|1)<=top&&h[pp].v>h[pp<<1|1].v)){
		pp<<=1;
		if(h[pp].v>h[pp|1].v)pp|=1;
		swap(h[pp],h[pp>>1]);
	}
}

int main(){
	read(n);
	for(int i=1;i<=n;++i)
		read(p[i].x),read(p[i].y),p[i].id=i;
	sort(p+1,p+n+1,cpx);
	for(int i=1;i<n;++i)
		add(p[i].id,p[i+1].id,p[i+1].x-p[i].x);
	sort(p+1,p+n+1,cpy);
	for(int i=1;i<n;++i)
		add(p[i].id,p[i+1].id,p[i+1].y-p[i].y);
	
	for(int i=1;i<=n;++i)dis[i]=inf;
	h[top=1]=node(1,0),dis[1]=0;
	node nw;
	while(top){
		nw=h[1];pop();
		if(nw.x==n)break;
		for(int i=head[nw.x];i;i=a[i].nxt)
			if(dis[a[i].v]>dis[nw.x]+a[i].w){
				dis[a[i].v]=dis[nw.x]+a[i].w;
				push(node(a[i].v,dis[a[i].v]));
			}
	}
	printf("%d\n",dis[n]);
	return 0;
}
