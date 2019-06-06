//bzoj-4198
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

template <typename _tp> inline void read(_tp&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N = 101000;
ll a[N],ans;
int n,k;

struct node {
	ll v; int h;
	friend inline bool operator < (const node&A,const node&B)
		{return A.v != B.v ? A.v > B.v : A.h > B.h;}
}hp[N];

int top;
inline void push(ll v, int h) {
	hp[++top] = (node) {v, h};
	push_heap(hp+1,hp+top+1);
}

inline void pop() {pop_heap(hp+1,hp+top+1), --top;}

int main() {
	read(n), read(k);
	for(int i=1;i<=n;++i) read(a[i]);
	if((n-1) % (k-1)) n += k - 1 - (n-1) % (k-1);
	for(int i=1;i<=n;++i) push(a[i], 0);
	
	node nw;
	
	ll sm; int mh;
	while(top > 1) {
		sm = mh = 0;
		for(int i=1;i<=k;++i) {
			nw = hp[1]; pop();
			sm += nw.v, mh = max(mh, nw.h);
		}
		ans += sm;
		push(sm, mh+1);
	}
	
	printf("%lld\n%d\n",ans,hp[1].h);
	return 0;
}
