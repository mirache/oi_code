#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ldb;

template <typename _tp> inline void read(_tp&x){
	char c11=getchar(),ob=0;x=0;
	while(c11!='-'&&!isdigit(c11))c11=getchar();if(c11=='-')ob=1,c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();if(ob)x=-x;
}

const int N = 500009;
ll w[N],sz[N],ans;
int n,fa[N];

namespace Hp {
	struct node {
		ldb w;int id;
		friend inline bool operator < (const node&A,const node&B) {return A.w!=B.w?A.w<B.w:A.id<B.id;}
		friend inline bool operator > (const node&A,const node&B) {return A.w!=B.w?A.w>B.w:A.id>B.id;}
		friend inline bool operator == (const node&A,const node&B){return A.w==B.w and A.id==B.id;}
	};
	struct Heap {
		node h[N];int top;
		inline void push(node x) {
			h[++top] = x;int pp = top;
			while(pp > 1 and h[pp] < h[pp>>1])
				swap(h[pp], h[pp>>1]), pp >>= 1;
		}
		inline void pop() {
			h[1] = h[top--];int pp = 1;
			while(((pp<<1) <= top and h[pp<<1] < h[pp]) or ((pp<<1|1) <= top and h[pp<<1|1] < h[pp])){
				pp <<= 1;
				if(h[pp] > h[pp|1]) pp |= 1;
				swap(h[pp], h[pp>>1]);
			}
		}
	}INS,DEL;
	
	inline void maintain(){
		while(DEL.top and INS.h[1] == DEL.h[1])
			INS.pop(), DEL.pop();
	}
	inline void push(int id){INS.push((node){(ldb)w[id]/sz[id],id});maintain();}
	inline void erase(int id){DEL.push((node){(ldb)w[id]/sz[id],id});maintain();}
	inline int top(){return INS.h[1].id;}
	inline void pop(){INS.pop();maintain();}
}

namespace UNF{
	int d[N];
	inline void reset(){for(int i=0;i<=n;++i)d[i] = i;}
	inline int find(int x){return d[x]==x?x:d[x]=find(d[x]);}
	inline bool merge(int x,int y){
		x = find(x), y = find(y);
		if(x == y) return false;
		d[x] = y; return true;
	}
}

int main(){
	read(n);
	UNF::reset();
	for(int i=1;i<=n;++i){
		read(fa[i]);
		if(!UNF::merge(i,fa[i]))
			{puts("-1");return 0;}
	}
	UNF::reset();
	for(int i=1;i<=n;++i){
		read(w[i]),ans+=w[i];
		sz[i]=1,Hp::push(i);
	}
	for(int i=1,x,y;i<=n;++i){
		x = Hp::top();
		Hp::pop();
		y = UNF::find(fa[x]);
		UNF::merge(x,y);
		ans += (ll)w[x] * sz[y];
		if(y) Hp::erase(y);
		sz[y] += sz[x], w[y] += w[x];
		if(y) Hp::push(y);
	}
	printf("%lld\n",ans);
	return 0;
}
