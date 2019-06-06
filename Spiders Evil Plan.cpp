//Codeforces-526G
#include <bits/stdc++.h>
using namespace std;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N = 101000;
struct Edge{int v,w,nxt;}a[N+N];
int head[N],dep[N],len[N],son[N],fa[N];
int anc[17][N], sm[N], top[N], rk[N];
int n,Q,_,tot,rt,D;

inline void ad(){
	static int x,y,z; read(x), read(y), read(z);
	a[++_].v = y, a[_].w = z, a[_].nxt = head[x], head[x] = _;
	a[++_].v = x, a[_].w = z, a[_].nxt = head[y], head[y] = _;
}

struct leaf{
	int id, v;
	friend inline bool operator < (const leaf&A,const leaf&B) {return A.v > B.v;}
}l[N];

void dfs(int x,int las,int dis){
	if(dis > D) D = dis, rt = x;
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v != las)
			dfs(a[i].v, x, dis + a[i].w);
}

void dfs1(int x){
	len[x] = dep[x];
	anc[0][x] = fa[x];
	for(int i=1;i<=16;++i)
		anc[i][x] = anc[i-1][anc[i-1][x]];
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v != fa[x]) {
			fa[a[i].v] = x;
			dep[a[i].v] = dep[x] + a[i].w;
			dfs1(a[i].v);
			if(len[a[i].v] > len[son[x]])
				son[x] = a[i].v;
		}
	if(son[x]) len[x] = len[son[x]];
}

void dfs2(int x,int Top){
	top[x] = Top;
	if(son[x]) dfs2(son[x],Top);
	else l[++tot] = (leaf) {x, dep[x] - dep[fa[top[x]]]};
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v != fa[x] and a[i].v != son[x])
			dfs2(a[i].v, a[i].v);
}

int solve(int x,int y){
	y <<= 1;
	if(tot <= y-1) return sm[tot];
	if(rk[top[x]] <= y-1) return sm[y-1];
	int t = x;
	for(int i=16;~i;--i)
		if(rk[top[anc[i][t]]] > y-1)
			t = anc[i][t];
	t = fa[t];
	int ans = sm[y-1];
	ans += len[x] - dep[t];
	ans -= min(min(len[t] - dep[t], sm[y-1] - sm[y-2]), dep[t]);
	return ans;
}

int main(){
	read(n), read(Q);
	for(int i=1;i<n;++i) ad();
	
	dfs(1,0,0);
	dfs1(rt), dfs2(rt,rt);
	sort(l+1,l+tot+1);
	for(int i=1;i<=tot;++i){
		rk[top[l[i].id]] = i;
		sm[i] = sm[i-1] + l[i].v;
	}
	
	int x,y,ans = 0;
	while(Q--){
		read(x), x = (x + ans - 1)%n + 1;
		read(y), y = (y + ans - 1)%n + 1;
		printf("%d\n",ans = solve(x,y));
	}
	return 0;
}
