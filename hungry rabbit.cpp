//bzoj-3661
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N=890;
char s[N][N];
int alive[N];
int ans[N][N],f[N][N];
int n,m,K,L;

struct nodeU{
	int vl,id;
	friend inline bool operator < (const nodeU&A,const nodeU&B){return A.vl<B.vl;}
}u[N];
struct nodeV{
	int vl,id;
	friend inline bool operator < (const nodeV&A,const nodeV&B){return A.vl>B.vl;}
}v[N];

int main(){
	freopen("hungry.in","r",stdin);
	freopen("hungry.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&K,&L);
	for(int i=1;i<=n;++i)scanf("%s",s[i]+1);
	for(int i=1;i<=n;++i)
	for(int j=m;~j;--j)
		if(s[i][j]=='0')f[i][j]=0;
		else f[i][j]=f[i][j+1]+1;
	for(int i=1;i<=n;++i)v[i].vl=f[i][0],v[i].id=i;
	sort(v+1,v+n+1);
	for(int i=1;i<=K;++i)alive[v[i].id]=true;
	for(int j=1;j<=m;++j){
		int t1=0,t2=0;
		for(int i=1;i<=n;++i)
			if(alive[i])
				++t1,u[t1].vl=f[i][j],u[t1].id=i;
			else 
				++t2,v[t2].vl=f[i][j],v[t2].id=i;
		sort(u+1,u+t1+1);
		sort(v+1,v+t2+1);
		int l=L,p1=1,p2=1;
		while(l--){
			if(p1>t1)break;
			if(p2>t2)break;
			if(u[p1].vl>v[p2].vl)break;
			alive[u[p1].id]=false;
			alive[v[p2].id]=true;
			++p1,++p2;
		}
		int tt=0;
		for(int i=1;i<=n;++i)
			if(alive[i])
				if(s[i][j]=='0')
					{puts("-1");return 0;}
				else ans[j][++tt]=i;
	}
	for(int i=1;i<=m;++i,putchar('\n'))
	for(int j=1;j<=K;++j)
		printf("%d ",ans[i][j]);
	return 0;
}
