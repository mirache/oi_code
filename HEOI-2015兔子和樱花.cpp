#include <bits/stdc++.h>
using namespace std;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N=2001000;

struct node{
	int c,s;
	friend inline bool operator < (const node&A,const node&B)
		{return A.c+A.s<B.c+B.s;}
}p[N];

struct Edge{int v,nxt;}a[N];
int head[N],c[N],s[N],fa[N];
int n,m,_,ans;

void dfs(int x){
	for(int i=head[x];i;i=a[i].nxt)
		dfs(a[i].v);
	int tp=0;
	for(int i=head[x];i;i=a[i].nxt){
		++tp;
		p[tp].c=c[a[i].v];
		p[tp].s=s[a[i].v];
	}
	if(!tp)return ;
	sort(p+1,p+tp+1);
	for(int i=1;i<=tp&&c[x]+s[x]+p[i].c+p[i].s-1<=m;++i){
		c[x]+=p[i].c;
		s[x]+=p[i].s-1;
		++ans;
	}
}

int main(){
	read(n),read(m);
	for(int i=0;i<n;++i)read(c[i]);
	for(int i=0,x;i<n;++i){
		read(s[i]);
		for(int j=s[i];j;--j){
			read(x);fa[x]=i;
			a[++_].v=x,a[_].nxt=head[i],head[i]=_;
		}
	}
	for(int i=0;i<n;++i)
		if(!fa[i]){dfs(i);break;}
	printf("%d\n",ans);
	return 0;
}
