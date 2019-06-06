//lg-5157
#include <bits/stdc++.h>

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N=100103;
struct Edge{int v,nxt;}a[N*3];
int head[N],Head[N],fa[N],tag[N];
int lim[N],deg[N],in[N],out[N];
int n,m,_,dfc;

inline void add(int x,int y,int*arr){a[++_].v=y,a[_].nxt=arr[x],arr[x]=_;}

inline bool check(int x,int y){return in[x]<=in[y]&&out[y]<=out[x];}
void dfs(int x,int las){
	in[x]=++dfc,fa[x]=las;
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=fa[x])dfs(a[i].v,x);
	out[x]=dfc;
}

void tag_down(int x){
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v!=fa[x]){
			tag[a[i].v]+=tag[x];
			tag_down(a[i].v);
		}
}

bool impossible(){
	static int q[N],he=1,ta=0,x;
	static bool vis[N];
	for(int i=1;i<=n;++i)
		if(!lim[i]&&deg[i]<2)
			vis[q[++ta]=i]=true;
		else vis[i]=false;
	while(he<=ta){
		x=q[he++];
		for(int i=head[x];i;i=a[i].nxt)
			if(!vis[a[i].v]){
				--deg[a[i].v];
				if(!lim[a[i].v]&&deg[a[i].v]<2)
					vis[q[++ta]=a[i].v]=true;
			}
		for(int i=Head[x];i;i=a[i].nxt)
			if(!vis[a[i].v]){
				--lim[a[i].v];
				if(!lim[a[i].v]&&deg[a[i].v]<2)
					vis[q[++ta]=a[i].v]=true;
			}
	}
	for(int i=1;i<=n;++i)
		if(!vis[i])return true;
	return false;
}

int main(){
	read(n),read(m);
	int x,y;
	for(int i=1;i<n;++i){
		read(x),read(y);++deg[x],++deg[y];
		add(x,y,head);add(y,x,head);
	}
	dfs(1,1);
	while(m--){
		read(x),read(y);
		++lim[y],add(x,y,Head);
		if(check(x,y)){
			++tag[1];
			for(int i=head[x];i;i=a[i].nxt)
				if(a[i].v!=fa[x] and check(a[i].v,y))
					{--tag[a[i].v];break;}
		}else ++tag[x];
	}
	tag_down(1);
	
	if(impossible())
		while(n--)puts("0");
	else 
		for(int i=1;i<=n;++i)
			puts(tag[i]?"0":"1");
	return 0;
}
