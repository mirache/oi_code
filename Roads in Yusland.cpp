//Codeforces-671D
#include <bits/stdc++.h>
using namespace std;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N = 301000;
struct Edge{int v,w,nxt;} a[N*3];
int head[N], Head[N];
int tag[N], cov[N];
int dep[N], len[N];
int rt[N], ls[N], rs[N];
int n,m,_,tot;

long long Ans;

inline void add(int x,int y,int z,int*arr){a[++_].v = y, a[_].w = z, a[_].nxt = arr[x], arr[x] = _;}

struct node{int w, ps;}t[N];

inline void put_tag(int x,int y) {t[x].w += y, tag[x] += y;}
inline void down_tag(int x){
	int&v = tag[x];
	if(!v) return ;
	if(ls[x]) put_tag(ls[x], v);
	if(rs[x]) put_tag(rs[x], v);
	v = 0;
}

int merge(int x,int y){
	if(!x or !y) return x | y;
	down_tag(x), down_tag(y);
	if(t[x].w > t[y].w) swap(x,y);
	rs[x] = merge(rs[x], y);
	if(len[ls[x]] < len[rs[x]]) swap(ls[x], rs[x]);
	len[x] = len[rs[x]] + 1;
	return x;
}

void dfs(int x,int las){
	for(int i=head[x];i;i=a[i].nxt)
		if(a[i].v != las){
			dep[a[i].v] = dep[x] + 1;
			dfs(a[i].v,x);
			rt[x] = merge(rt[x], rt[a[i].v]);
			cov[x] += cov[a[i].v];
		}
	if(x != 1 and !cov[x]) puts("-1"), exit(0);
	for(int i=Head[x];i;i=a[i].nxt){
		t[++tot] = (node) {a[i].w, a[i].v};
		rt[x] = merge(rt[x], tot);
	}
	while(rt[x] and dep[t[rt[x]].ps] >= dep[x]) rt[x] = merge(ls[rt[x]], rs[rt[x]]);
	Ans += t[rt[x]].w, put_tag(rt[x], -t[rt[x]].w);
}

int main(){
	read(n), read(m);
	int x,y,z;
	for(int i=1;i<n;++i){
		read(x), read(y);
		add(x,y,0,head);
		add(y,x,0,head);
	}
	while(m--){
		read(x), read(y), read(z);
		++cov[x], --cov[y];
		add(x,y,z,Head);
	}
	dfs(1,0);
	printf("%lld\n",Ans);
	return 0;
}
