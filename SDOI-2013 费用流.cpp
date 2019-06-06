#include<bits/stdc++.h>
using namespace std;
#define eps (1e-6)
#define cl(x) memset(x,0,sizeof(x))
#define cl1(x) memset(x,-1,sizeof(x))
#define clm(x) memset(x,0x3f3f3f3f,sizeof(x))
#define clt(x,y) memset(x,y,sizeof(x))
#define rg register

template <typename _Tp> inline void read(_Tp&x){
	char c11=getchar();x=0;bool booo=0;
	while(c11!='-'&&!isdigit(c11))c11=getchar();if(c11=='-'){c11=getchar();booo=1;}
	while(isdigit(c11)){x=x*10+c11-'0';c11=getchar();}if(booo)x=-x;return ;
}

const int N=105,M=5050;
const double inf=1000000007.000;
double l=0,r=0;
int head[N],cur[N],dis[N];
int n,m,s,t,_=0;
double ans=0,p;
struct node{int nxt,v;double cap;}a[M];
struct node1{int u,v;double cap;}edge[M];

inline void ADD(int,int,double);

inline void add(int,int,double);

void init();

void work();

bool bfs(){
	queue <int> q;
	q.push(s);
	cl1(dis);
	dis[s]=0;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(rg int i=head[x];~i;i=a[i].nxt)
			if(-1==dis[a[i].v]&&a[i].cap>eps)
				{dis[a[i].v]=dis[x]+1;q.push(a[i].v);if(a[i].v==t)break;}
	}
	return dis[t]!=-1;
}

double dfs(int x,double low){
	if(x==t||low<eps)return low;
	double res=0.0,temp;
	for(rg int&i=cur[x];~i;i=a[i].nxt)
		if(dis[a[i].v]==dis[x]+1&&a[i].cap>eps)
		if((temp=dfs(a[i].v,fmin(low-res,a[i].cap)))>0){
			a[i].cap-=temp;
			a[i^1].cap+=temp;
			res+=temp;
			if(res==low)return low;
		}
	if(!res)dis[x]=-1;
	return res;
}

double maxf(double limit){
	cl1(head);_=0;
	for(rg int i=0;i<m;++i)ADD(edge[i].u,edge[i].v,fmin(edge[i].cap,limit));
	double sum=0;
	while(bfs()){
		for(rg int i=1;i<=n;++i)cur[i]=head[i];
		sum+=dfs(s,inf);
	}
	return sum;
}

int main(){
	init();
	work();
	return 0;
}

void work(){
	ans=maxf(inf);
	while(r-l>eps){
		double mid=(r+l)/2;
		if(ans-maxf(mid)<eps)r=mid;
		else l=mid;
	}
	printf("%.0lf\n%.4lf\n",ans,(double)l*p);
	return ;
}

void init(){
	read(n);read(m);scanf("%lf",&p);s=1,t=n;
	for(rg int i=0;i<m;++i){
		read(edge[i].u);read(edge[i].v);
		scanf("%lf",&edge[i].cap);r=fmax(r,edge[i].cap);
	}
	return ;
}

inline void add(int u,int v,double cap){
	a[_].cap=cap;
	a[_].v=v;
	a[_].nxt=head[u];
	head[u]=_++;
	return ;
}

inline void ADD(int u,int v,double cap){add(u,v,cap);add(v,u,0);return ;}
