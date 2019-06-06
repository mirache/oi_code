//AtCoder-agc004F
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N=101000;
struct Edge{int v,nxt;}a[N<<1];
int head[N],sz[N],k[N],fa[N],d[N],v[N];
int n,m,A,B,ga,gb,_,tp;ll ans;

inline int find(int x){return d[x]?d[x]=find(d[x]):x;}

void dfs(int x,int las,int sgn){
	sz[x]=sgn,fa[x]=las;
	if(x==A)ga=sgn;
	else if(x==B)gb=sgn;
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=las){
			dfs(a[i].v,x,-sgn);
			sz[x]+=sz[a[i].v];
		}
}

bool odd(){
	if(sz[1]&1)return true;
	int t=sz[1]/2;ans+=abs(t);
	for(int i=A;i;i=fa[i])sz[i]-=t;
	for(int i=B;i;i=fa[i])sz[i]-=t;
	return false;
}

bool even(){
	if(sz[1])return true;
	for(int i=A;i;i=fa[i])--k[i];
	for(int i=B;i;i=fa[i])++k[i];
	v[tp=1]=sz[1];
	for(int i=1;i<=n;++i)
		if(k[i]==1)v[++tp]=-sz[i];
		else if(k[i]==-1)v[++tp]=sz[i];
	sort(v+1,v+tp+1);
	int t=v[tp+1>>1];ans+=abs(t);
	for(int i=1;i<=n;++i)sz[i]+=k[i]*t;
	return false;
}

void init();
void print();
int main(){
	init();
	if(m<n)
		if(sz[1])puts("-1");
		else print();
	else if(ga==gb?odd():even())puts("-1");
	else print();
	return 0;
}

void print(){
	for(int i=1;i<=n;++i)
		ans+=abs(sz[i]);
	printf("%lld\n",ans);
}

void init(){
	read(n),read(m);
	int x,y;
	for(int i=0;i<m;++i){
		read(x),read(y);
		if(find(x)!=find(y)){
			d[find(x)]=find(y);
			a[++_].v=y,a[_].nxt=head[x],head[x]=_;
			a[++_].v=x,a[_].nxt=head[y],head[y]=_;
		}else A=x,B=y;
	}
	dfs(1,0,1);
}
