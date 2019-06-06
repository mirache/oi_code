//bzoj-5499
#include <bits/stdc++.h>
using namespace std;

inline void read(int&x){
	char c11=getchar();x=0;while(!isdigit(c11))c11=getchar();
	while(isdigit(c11))x=x*10+c11-'0',c11=getchar();
}

const int N = 201000;
struct Edge {int v,nxt;} a[N];
int head[N], v[N], stk[N];
int n, _;

inline void add(int x,int y) {a[++_].v = y, a[_].nxt = head[x], head[x] = _;}

int T = 0;

struct Heap {
	vector <int> vec; int sz;
	inline Heap() {sz = 0;}
	
	inline int top() {return vec[0];}
	inline void clear() {vec.clear(), sz = 0;}
	
	inline void push(int x) {
		vec.push_back(x); ++sz; ++ T;
		push_heap(vec.begin(), vec.end());
	}
	inline void pop() {
		pop_heap(vec.begin(), vec.end());
		vec.pop_back(); --sz; -- T;
	}
}h[N];

void merge(Heap&x, Heap&y) {
	if(x.sz < y.sz) swap(x.vec, y.vec), swap(x.sz, y.sz);
	int qwq, pwp;
	stk[0] = 0;
	while(y.sz) {
		pwp = y.top(); y.pop();
		qwq = x.top(); x.pop();
		stk[++stk[0]] = max(pwp, qwq);
	}
	for(int i=1;i<=stk[0];++i)
		x.push(stk[i]);
}

void dfs(int x) {
	for(int i=head[x];i;i=a[i].nxt) {
		dfs(a[i].v);
		merge(h[x], h[a[i].v]);
	}
	h[x].push(v[x]);
}

int main() {
	read(n);
	for(int i=1;i<=n;++i) read(v[i]);
	for(int i=2,x;i<=n;++i) read(x), add(x, i);
	dfs(1);
	long long ans = 0ll;
	for(int i=h[1].sz-1;~i;--i)
		ans += h[1].vec[i];
	printf("%lld\n",ans);
	return 0;
}
