//bzoj-5321
#include <bits/stdc++.h>
using namespace std;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N = 201000;
int s[N],T,n,m,a,k;

struct node{
	int l,r;
	inline void in(){read(l),read(r);}
	friend inline bool operator > (const node&A,const node&B) {return A.r > B.r;}
	friend inline bool operator < (const node&A,const node&B) {return A.r < B.r;}
}e[N];

inline bool cmpl(const node&A,const node&B) {return A.l != B.l ? A.l < B.l : A.r < B.r;}

namespace BIT{
	int d[N];
	#define lb(x) (x&(-x))
	inline void reset() {for(int i=0;i<=n;++i) d[i] = 0;}
	inline void add(int x,int y){for(;x<=n;x+=lb(x)) d[x] += y;}
	inline void upd(int l,int r,int x){add(l,x),add(r+1,-x);}
	inline int qy(int x){int r = 0; for(;x;x-=lb(x)) r += d[x]; return r;}
}

namespace H{
	node h[N]; int tp;
	inline void clear() {tp = 0;}
	inline void push(node&x) {h[++tp] = x, push_heap(h+1,h+tp+1);}
	inline void pop() {pop_heap(h+1,h+tp+1), --tp;}
}

bool chk(int L){
	BIT::reset();
	H::clear();
	int kk = k;
	for(int i=1,j=1;i<=n;++i){
		while(j <= m and e[j].l == i)
			H::push(e[j++]);
		int t = BIT::qy(i) + s[i];
		while(t < L) {
			if(!H::tp) return false;
			if(!(kk--)) return false;
			node nw = H::h[1];
			if(H::h[1].r < i) return false;
			H::pop();
			BIT::upd(nw.l,nw.r,a), t += a;
		}
	}
	return true;
}

int main(){
	read(T);
	while(T--) {
		read(n), read(m), read(k), read(a);
		int l = 1e8, r = 0, res = 0, mid;
		for(int i=1;i<=n;++i) {
			read(s[i]);
			l = min(l, s[i]);
			r = max(r, s[i]);
		}
		r += a * k;
		for(int i=1;i<=m;++i) e[i].in();
		sort(e+1,e+m+1,cmpl);
		while(l <= r) {
			mid = l + r >> 1;
			if(chk(mid)) l = (res = mid) + 1;
			else r = mid - 1;
		}
		printf("%d\n",res);
	}
	return 0;
}
