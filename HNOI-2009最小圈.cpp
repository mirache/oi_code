#include<cctype>
#include<cstdio>
using namespace std;
typedef long long ll;
#define rg register
#define cl(x) memset(x,0,sizeof(x))

template <typename _Tp> inline _Tp read(_Tp&x){
	rg char c11=getchar(),ob=0;x=0;
	while(c11^'-'&&!isdigit(c11))c11=getchar();if(c11=='-')c11=getchar(),ob=1;
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;return x;
}

const int N=3030,M=20010;const double eps=1e-10;
struct Edge{int v,nxt;double w;}a[M];
int head[N],vis[N],n,m,_;
double dis[N],mid;

inline void add(int u,int v,double w){a[++_].v=v,a[_].w=w,a[_].nxt=head[u],head[u]=_;}

inline int dfs(int x){
	vis[x]=1;
	for(rg int i=head[x];i;i=a[i].nxt)
		if(dis[a[i].v]>dis[x]+a[i].w-mid){
			dis[a[i].v]=dis[x]+a[i].w-mid;
			if(vis[a[i].v])return 1;
			if(dfs(a[i].v))return 1;
		}
	return vis[x]=0;
}

int check(){
	for(rg int i=1;i<=n;++i)vis[i]=dis[i]=0;
	for(rg int i=1;i<=n;++i)if(dfs(i))return 1;
	return 0;
}

int main(){
	read(n);read(m);
	double z;
	for(rg int i=0,x,y;i<m;++i)read(x),read(y),scanf("%lf",&z),add(x,y,z);
	double l=-10000001,r=10000001;
	while(r-l>eps){
		mid=(l+r)/2.0;
		if(check())r=mid;
		else l=mid;
	}
	printf("%.8lf\n",mid);
	return 0;
}
